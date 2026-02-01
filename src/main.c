#include <stdio.h> 
#include "fs_logic.h"

Folder* root;		//Pointer to the root of the system
Folder* cur;		//Pointer to the current directory the user is on

int main(){
	printf("----- Initializing file system -----");

	root = create_system();
	cur = root;			//Start off by poiting to the root
	
	if (root != NULL){
		printf("System was built successfully");
		printf("Current directory: %s\n", cur->name);
	}

	// TODO Add loops for the menu
	
	destroy_system(root);

	return 0;
}
