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

void destroy_system(Folder* folder){
	//TODO: Implementar função de limpeza
	if (folder != NULL){
		printf("DEBUG: A destruir sistema a partir de %s... (Lógica pendente)\n", folder->name);
		free(folder);
	}
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

void ls(Folder* current){
	if(current == NULL) return;

	printf("Contents of %s:\n", current->name);

	Folder* temp = current->F_child;

	if(temp == NULL){
		printf("(empty)\n");
		return;
	}

	while(temp != NULL) {
		printf("<DIR> %s\n", temp->name);
		temp = temp->next;
	}

	//TODO: Adicionar loop pra files
}
