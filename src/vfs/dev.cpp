#include <vfs/dev.h>

//Linked list of all devices
struct vfs_device *devices;
//Creates a device
struct vfs_device *create_device(const char *device_name)
{
    //Create a device
    struct vfs_device *device = (struct vfs_device *) malloc(sizeof(struct vfs_device));
    //Create folder list
    device->folder_list = (struct vfs_folder_node *) malloc(sizeof(struct vfs_folder_node));
    //Create locked files list
    device->locked_files = (struct vfs_file_node **) malloc(sizeof(struct vfs_file_node**));
    //Number of nodes is 0
    device->num_file_nodes = 0;
    //Set device's create folder function
    device->create_folder = create_folder;
    //Set device's create file function
    device->create_file = create_file;
    //Set device's find folder function
    device->find_folder_node = find_folder_node;
    //Set device's find file function
    device->find_file_node = find_file_node;
    //Checks if file exists
    device->does_file_exist = does_file_exist;
    //Checks if folder exists
    device->does_folder_exist = does_folder_exist;
    //Set device's name to device name
    device->device_name = device_name;
    //Check if devices is null
    if(devices == NULL)
    {
        //Allocate space for devices
        devices = (struct vfs_device *) malloc(sizeof(struct vfs_device));
        //Previous instance of devices is device
        devices->prev = device;
    }
    else
    {
        //Next instance in device list is device
        devices->next = device;
        //Previous instance in device is device list
        device->prev = devices;
        //Set devices to device
        devices = device;
    }
    //Return the device
    return device;
}