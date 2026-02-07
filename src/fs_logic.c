#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "fs_logic.h"


static Folder* create_folder(char* name, Folder* parent){
	Folder* new_folder = (Folder*)malloc(sizeof(Folder));

	if (new_folder == NULL){
		printf("Error: Failed to allocate memory.\n");
		exit(1);
	}

	//Initialize data
	strncpy(new_folder->name, name, MAX_NAME);	//Copy the data from the name argument into the memory addres
							//of the name atribute
	new_folder->parent = parent;
	
	//Initialize pointers as NULL, to avoid pointing to "garbage" data
	new_folder->F_child = NULL;
	new_folder->next = NULL;
	new_folder->files = NULL;

	return new_folder;
}

Folder* create_system(){
	return create_folder("root", NULL);		//We give as argument for the parent Null since it's the root of the system
}

static void destroy_files(File* file_list){
	File* current = file_list;
	while(current != NULL){
		File* next_file = current->next;
		free(current);
		current = next_file;
	}
}

void destroy_system(Folder* folder){
	if (folder == NULL){
		return;
	}
	
	Folder* current_child = folder->F_child;

	while(current_child != NULL){				//Recursive implementation for folder deletion, deleting it's contents in the process
		Folder* next_child = current_child->next;	//We save the child of the current folder for the recursive calling in the next iteration

		destroy_system(current_child);

		current_child = next_child;
	}

	destroy_files(folder->files);

	printf("DEBUG: Deleting folder '%s'\n", folder->name); 
    	free(folder);
}

void mkdir(Folder* parent, char* name){
	if(parent == NULL){
		printf("Error: Current directory is NULL.\n");
		return;
	}

	//Checks for duplicated names
	Folder* temp = parent->F_child;

	while(temp != NULL){
		if(strcmp(temp->name, name) == 0){
			printf("Error: Folder '%s' already exists.\n", name);
			return;
		}
		temp = temp->next;
	}
	
	//Create folder
	Folder* new_folder = create_folder(name, parent);
	
	//Insert in linked list
	if(parent->F_child == NULL){			//Checks if it's the first sub-folder of parent
		parent->F_child = new_folder;
	}else{						//If there are others sub-folders inserts in the linked list
		Folder* i = parent->F_child;
		while(i->next != NULL){
			i = i->next;
		}
		i->next = new_folder;
	}

	printf("Folder '%s' created.\n", name);
}


void ls(Folder* current) {
    if (current == NULL) return;
    printf("Contents of /.../%s:\n", current->name);

    
    Folder* subIdx = current->F_child;
    while (subIdx != NULL) {
        printf("[DIR]  %s\n", subIdx->name);
        subIdx = subIdx->next;
    }

    
    File* fileIdx = current->files;
    while (fileIdx != NULL) {
        printf("[FILE] %s\n", fileIdx->name);
        fileIdx = fileIdx->next;
    }
    
    if (current->F_child == NULL && current->files == NULL) {
        printf("(empty)\n");
    }
}



void rm(Folder* current, char* filename) {
    if (current == NULL || current->files == NULL) {
        printf("Error: No files to remove.\n");
        return;
    }

    File* temp = current->files;
    File* prev = NULL;

    // Case 1: The file we are removing is the head of the file linked list
    if (strcmp(temp->name, filename) == 0) {
        // We make the second element the new head
        current->files = temp->next; 
        
        printf("File '%s' removed.\n", filename);
        free(temp); // Free the memory of the deleted node
        return;
    }

    // Case 2: Search through the list
    while (temp != NULL && strcmp(temp->name, filename) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // if temp == NULL the file with the given doesn't exist
    if (temp == NULL) {
        printf("Error: File '%s' not found.\n", filename);
        return;
    }

    // In case the file does exist
    // 'prev' will start poiting to 'temp' next node skiping 'temp' leaving it out of the list since no node is pointing to it
    prev->next = temp->next;
    
    printf("File '%s' removed.\n", filename);
    free(temp);
}

// fs_logic.c

//Private function 
static File* create_file_node(char* name, char* content) {
    File* new_file = (File*) malloc(sizeof(File));
    if (new_file == NULL) {
        printf("Error: Memory allocation failed for file.\n");
        exit(1);
    }
    strncpy(new_file->name, name, MAX_NAME);
    strncpy(new_file->content, content, MAX_CONTENT);
    new_file->next = NULL;
    return new_file;
}

//Public function
void touch(Folder* current, char* name, char* content) {
    if (current == NULL) return;

    
    File* temp = current->files;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Error: File '%s' already exists.\n", name);
            return;
        }
        temp = temp->next;
    }

    // Create node
    File* new_file = create_file_node(name, content);

    
    if (current->files == NULL) {
        current->files = new_file;
    } else {
        File* iterator = current->files;
        while (iterator->next != NULL) {
            iterator = iterator->next;
        }
        iterator->next = new_file;
    }
    printf("File '%s' created.\n", name);
}
