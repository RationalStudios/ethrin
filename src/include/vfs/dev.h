#ifndef DEV_H
#define DEV_H
#include <stdint.h>
#include <vfs/vfs.h>
struct vfs_device
{
    //The name of the device
    const char *device_name;
    //Folder node list associated with device
    struct vfs_folder_node *folder_list;
    //List of all locked files
    struct vfs_file_node **locked_files;
    //Number of all file nodes
    uint16_t *num_file_nodes;
    //Next device
    struct vfs_device *next;
    //Previous device
    struct vfs_device *prev;
    //Create folder function
    struct vfs_folder_node *(*create_folder)(const char *folder_path, uint16_t *process_permissions, struct vfs_device *device);
    //Create file function
    struct vfs_file_node *(*create_file)(const char *path, uint16_t *process_permissions, struct vfs_device *device);
    //Find folder node function
    struct vfs_folder_node *(*find_folder_node)(const char *path, struct vfs_device * device);
    //Find file node function
    struct vfs_file_node *(*find_file_node)(const char *path, struct vfs_device * device);
    //Check if folder exists
    bool (*does_folder_exist)(const char *path, struct vfs_device *device);
    //Check if file exists
    bool (*does_file_exist)(const char *path, struct vfs_device *device);
};

//Linked list of all devices
extern struct vfs_device *devices;
//Creates a device
struct vfs_device *create_device(const char *device_name);
#endif