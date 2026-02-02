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
