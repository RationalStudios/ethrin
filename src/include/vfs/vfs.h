#ifndef VFS_H
#define VFS_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vfs/dev.h>
#define PATH_SEPARATOR "/"

struct vfs_file_node
{
    //The file name
    const char *name;
    //The entire file path
    const char *file_path;
    //The content
    const void *content;
    //Permissions this file is created with
    uint16_t *file_permissions;
    //This file's handle
    uint16_t *file_handle;
    //Next instance of file node
    struct vfs_file_node *next;
    //Previous instance of file node
    struct vfs_file_node *prev;
    //Parent node
    struct vfs_folder_node *parent;
    //Locks the file, prevents read/write
    bool locked = false;
};

struct vfs_folder_node
{
    //The name of the folder
    const char *folder_name;
    //Path of folder node
    const char *folder_path;
    //Permissions this folder is created with
    uint16_t *folder_permissions;
    //Amount of file nodes in folder node
    uint16_t *file_node_count = 0;
    //All files in this folder
    struct vfs_file_node *files;
    //Next folder node
    struct vfs_folder_node *next;
    //Previous folder node
    struct vfs_folder_node *prev;
};

//Creates a device
struct vfs_device *create_device(char *device_name);
//Compares str1 and str2
int strcmp(const char *str1, const char *str2);
//Gets the amount of values in string str
size_t strlen(const char* str);
//Gets the position of the last path separator before node name
size_t get_final_separator_position(const char *path);
//Gets the parent directory of a node's path
char *get_node_parent(const char *path);
//Gets the name of a node using the node's path
char *get_node_name(const char *path);
//Returns if str1 and str match
bool str_matches(const char* str1, const char *str2);
//Extracts folder node given the path
struct vfs_folder_node *find_folder_node(const char *path, struct vfs_device *device);
//Is folder at path available?
bool does_folder_exist(const char* path, struct vfs_device *device);
//Finds the node of a file with the given path
struct vfs_file_node *find_file_node(const char* path, struct vfs_device *device);
//Finds file by checking if file handle is valid
struct vfs_file_node *find_file_node(int file_handle, struct vfs_device *device);
//For checking if file with given path exists
bool does_file_exist(const char *path, struct vfs_device *device);
//Creates a folder with the given path
struct vfs_folder_node *create_folder(const char *path, uint16_t *proc_permissions, struct vfs_device *device);
//Creates a file with the given path
struct vfs_file_node *create_file(const char *path, uint16_t *proc_permissions, struct vfs_device *device);
#endif