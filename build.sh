#!/bin/bash
rm -rf CMakeCache.txt CMakeFiles
export OUTPUT_DIR=`pwd`/output

#Show a list of all devices
echo "List of all devices that your instance of ethrin supports:"
#Loop through all supported devices
for device in "supported_devices"/*
do
    #Echo the name of this device
    echo $device | sed -e "s/supported_devices\///g"
done

#Ask the user to select a device
read -p "Select a device to build (i686-pc-none-elf is default): " selected_device

#Did the user select a device?
if [ -z $selected_device ]
then
    selected_device="i686-pc-none-elf"
fi
#The full device directory
full_device_directory="`pwd`/supported_devices/$selected_device"

#Move device content into src
cp -R $full_device_directory "src/$selected_device"
#Ask for the architecture the user is targeting
read -p "Which architecture are you targeting (i686 is default): " selected_arch

#Check if selected architecture is empty
if [ -z $selected_arch ]
then
    selected_arch="i686"
fi

export TARGET_BUILD=$selected_device
export TARGET_ARCH=$selected_arch
export TARGET_OUTPUT="output/$TARGET_BUILD"
mkdir -p output

objcopy -O $selected_device -B "i386" -I binary assets/font.psf font.o
cmake `pwd`/src
make

mkdir -p "$TARGET_OUTPUT/isodir/boot/grub"
cp "src/boot/grub.cfg" "$TARGET_OUTPUT/isodir/boot/grub/grub.cfg"
mv "$TARGET_OUTPUT/ethrin.bin" "$TARGET_OUTPUT/isodir/boot/ethrin.bin"
grub-mkrescue "$TARGET_OUTPUT/isodir" -o "output/$TARGET_BUILD-ethrin.iso"
rm -rf "src/$selected_device"
