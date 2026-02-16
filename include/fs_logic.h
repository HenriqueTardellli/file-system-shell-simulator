#ifndef FS_LOGIC_H
#define FS_LOGIC_H

/*Constants to limit the size of the data*/
#define MAX_NAME 50
#define MAX_CONTENT 200


/*Structure for the text files, which are the tree leaves*/
typedef struct File{
	char name[MAX_NAME];
	char content[MAX_CONTENT];
	struct File* next;
}File;

/*Structur for folders, nodes of the tree*/

typedef struct Folder {
	char name[MAX_NAME];
	
	//Vertical hierarchical navigation 
	struct Folder* parent;
	struct Folder* F_child;		/*The first folder, or more precisely, the first element of the linked list*/

	//Horizontal navigation
	struct Folder* next;		/*Points to the nest element in the horizontal linked list*/

	//Text files
	struct File* files;		/*Points to the linked list of text files in the current folder*/
}Folder;

/*Main functions prototypes*/

Folder* create_system();

void destroy_system(Folder* folder);

void mkdir(Folder* parent, char* name);

void ls(Folder* current);

void rm(Folder* current, char* filename);

void touch(Folder* current, char* name, char* content);

Folder* cd(Folder* current, char* destination);

void burn(Folder* parent, char* folder_name);

void cat(Folder* current, char* name);

#endif
