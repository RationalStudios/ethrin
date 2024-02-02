#include <vfs/vfs.h>
//Gets the position of the last path separator before node name
size_t get_final_separator_position(const char *path)
{
    //The position of the last path separator
    size_t last_position = 0;
    //Loop until the path character at index is terminator
    for(size_t idx = 0; path[idx] != '\0'; idx++)
    {
        //Check if path at idx is the path separator
        if(path[idx] == PATH_SEPARATOR[0])
            //Set the last position to index idx
            last_position = idx;
    }
    //Return the last position
    return last_position;
}

//Gets the parent directory of a node's path
char *get_node_parent(const char *path)
{
    //Position of last separator ('/')
    size_t last_sep_pos = get_final_separator_position(path);
    //Check if last separator position is 0
    if(last_sep_pos == 0)
        //Set last separator to 1
        last_sep_pos = 1;
    //Results, in this case the parent directory
    char *results = (char *) malloc(sizeof(char *));
    //Loop until index is equal to last_sep_pos
    for(size_t idx = 0; idx < last_sep_pos; idx++)
    {
        //Set results character at idx to path at idx
        results[idx] = path[idx];
    }
    //Return the results
    return results;
}

//Gets the name of a node using the node's path
char *get_node_name(const char *path)
{
    //Get the position of the last separator, excluding the separator
    size_t last_sep_pos = get_final_separator_position(path) + 1;
    //The results to be appended and returned
    char *results = (char *) malloc(sizeof(char *));
    //Loop until index idx is equal to the amount of characters in path
    for(size_t results_idx = 0, idx = last_sep_pos; idx < strlen(path); idx++)
    {
        //Set results character at results_idx to path at idx
        results[results_idx] = path[idx];
        //Update the results_idx variable
        results_idx++;
    }
    //We now have the node name
    return results;
}

//Returns if str1 and str match
bool str_matches(const char* str1, const char *str2)
{
    //Returns if str1 and str2 match
    return strcmp(str1, str2) == 0;
}

//Extracts folder node given the path
struct vfs_folder_node *find_folder_node(const char *path, struct vfs_device *device)
{
    //Check if path is root
    if(path == PATH_SEPARATOR)
        //Return the folder list
        return device->folder_list;
    //Create a mock folder list
    struct vfs_folder_node *mock_folder_list = device->folder_list;
    //Loop until next folder instance is null
    while(mock_folder_list->next != NULL)
    {
        //Set mock folder list to next instance
        mock_folder_list = mock_folder_list->next;
        //Check if paths match
        if(str_matches(mock_folder_list->folder_path, path))
            //Return the mock list
            return mock_folder_list;
    }
    //There's no folder node
    return NULL;
}

//Is folder at path available?
bool does_folder_exist(const char* path, struct vfs_device *device)
{
    //Find the folder node and check if it is not null
    return find_folder_node(path, device) != NULL;
}

//Finds the node of a file with the given path
struct vfs_file_node *find_file_node(const char* path, struct vfs_device *device)
{
    //Get the file parent
    char *parent = get_node_parent(path);
    //Check if the parent directory exists
    if(does_folder_exist(parent, device))
    {
        //Find the parent node
        struct vfs_folder_node *parent_node = find_folder_node(parent, device);
        //Mock of parent node's files linked list
        struct vfs_file_node *files = parent_node->files;
        //Loop until the next instance of files is null
        while(files->next != NULL)
        {
            //Go to the next file
            files = files->next;
            //Compare file path to path
            if(str_matches(path, files->file_path))
                //Return the current file
                return files;
        }
    }

    //No file was found
    return NULL;
}

//Finds file by checking if file handle is valid
struct vfs_file_node *find_file_node(uint16_t file_handle, struct vfs_device *device)
{
    //Check if file handle is valid
    if(&file_handle < device->num_file_nodes && device->locked_files[file_handle] != NULL)
        //Return the locked file at the given handle
        return device->locked_files[file_handle];
    //Locked file was not found
    return NULL;
}

//For checking if file with given path exists
bool does_file_exist(const char *path, struct vfs_device *device)
{
    //Find the file node and check if it is not null
    return find_file_node(path, device) != NULL;
}

//Creates a folder with the given path
struct vfs_folder_node *create_folder(const char *path, uint16_t *proc_permissions, struct vfs_device *device)
{
    //Create a folder node
    struct vfs_folder_node *folder = (struct vfs_folder_node *) malloc(sizeof(struct vfs_folder_node));
    //Create a folder if it does not exist
    if(!does_folder_exist(path, device))
    {
        //Set the folder's name
        folder->folder_name = get_node_name(path);
        //Set the folder's path
        folder->folder_path = path;
        //Set folder permissions
        folder->folder_permissions = proc_permissions;
        //Set the files
        folder->files = NULL;
        //And the file node count
        folder->file_node_count = 0;
        //Is the folder path root?
        if(path == PATH_SEPARATOR)
        {
            //Set folder to folder_list
            device->folder_list->prev = folder;
        }
        else
        {
            //Next folder_list instance is folder
            device->folder_list->next = folder;
            //Previous folder instance is folder_list
            folder->prev = device->folder_list;
            //Folder list is now folder
            device->folder_list = folder;
        }
    }
    //Loop to reset folder list to root
    while(device->folder_list->prev != NULL)
    {
        //Set folder list to previous instance
        device->folder_list = device->folder_list->prev;
    }
    //Return the folder node
    return folder;
}

//Creates a file with the given path
struct vfs_file_node *create_file(const char *path, uint16_t *proc_permissions, struct vfs_device *device)
{
    //Get the file parent path
    char *parent = get_node_parent(path);
    //Get the file name
    char *name = get_node_name(path);
    //Check if the parent folder exists
    if(does_folder_exist(parent, device))
    {
        //Create a file node
        struct vfs_file_node *file = (struct vfs_file_node*) malloc(sizeof(struct vfs_file_node));
        //Get the parent node
        struct vfs_folder_node *parent_node = find_folder_node(parent, device);
        //Set the file node's path
        file->file_path = path;
        //Set file permissions
        file->file_permissions = proc_permissions;
        //Set the file node's name
        file->name = name;
        //Set the file node's parent node
        file->parent = parent_node;
        //Check if parent node's files element does not exist
        if(parent_node->files == NULL)
            //Initiate the files linked list
            parent_node->files = (struct vfs_file_node*) malloc(sizeof(struct vfs_file_node));
        //Set file handle by left shifting of parent node's file node count and permissions
        file->file_handle = device->num_file_nodes;
        //The file is not locked
        file->locked = false;
        //Update the file node count in parent node
        parent_node->file_node_count;
        //Set next element in files to file
        parent_node->files->next = file;
        //Set previous element to file list
        file->prev = parent_node->files;
        //Set files to file
        parent_node->files = file;
        //Update node count
        device->num_file_nodes++;
        //Return list to original state with new file
        while(parent_node->files->prev != NULL)
        {

            //Set the files to the previous
            parent_node->files = parent_node->files->prev;
        }
        //Return the file
        return file;
    }
    //And since no file was created, return null
    return NULL;
}

