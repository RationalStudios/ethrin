#include <devices/pci.h>
#include <malloc/malloc.h>
#include <system.h>
#include <vesa/vesa.h>
#include <graphics/graphics.h>
#include <sys/portio.hpp>
#include <vfs/dev.h>
#include <notify/notify.h>

extern "C" void initiate_mini_kernel(unsigned int *multiboot_struct);
extern "C" void run_device_specific_code();
void initiate_mini_kernel(unsigned int *multiboot_struct)
{
    //Initialize vesa mode
    init_vesa(multiboot_struct);
    //Initialize the GDT
    init_gdt();
    //Initialize the IDT
    init_idt();
    //Initialize all PCI devices
    initialize_pci_devices();
    //Write out a greeting!
    notify("Welcome to ethrin!");
    //Run the device specific code
    run_device_specific_code();
    //Rational Studios credit
    notify("[Rational Studios| 2024]");
}
