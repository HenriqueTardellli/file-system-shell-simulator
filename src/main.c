#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fs_logic.h"

#define MAX_CMD_BUFFER 100

Folder* root;
Folder* current; 

void print_help() {
    printf("\n--- My VFS Shell Help ---\n");
    printf("  new <name>          : Create a new folder\n");
    printf("  write <name> <txt>  : Create a file with content\n");
    printf("  read <name>         : Read file content\n");          // <--- NOVO
    printf("  list                : List directory contents\n");
    printf("  goto <name>         : Change directory (use '..' to go up)\n");
    printf("  del <name>          : Delete a file\n");
    printf("  burn <name>         : Recursively delete a folder\n");
    printf("  exit                : Exit the simulator\n");
    printf("-------------------------\n");
}

int main() {
    char input[MAX_CMD_BUFFER];
    char *command, *arg1, *arg2;

    // 1. System initialization
    root = create_system();
    current = root;

    // Clear screen
    printf("\033[H\033[J"); 
    
    printf("Welcome to My VFS Shell v1.0\n");
    printf("Type 'help' to see available commands.\n");

    // 2. Main command loop
    while (1) {
        printf("\n[%s] $ ", current->name);

        if (fgets(input, MAX_CMD_BUFFER, stdin) == NULL) {
            break; 
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) continue;
        
        // Tokenization
        command = strtok(input, " "); 
        arg1 = strtok(NULL, " ");     
        arg2 = strtok(NULL, ""); 

        if (command == NULL) continue;

        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell. Goodbye!\n");
            break; 
        } 
        else if (strcmp(command, "help") == 0) {
            print_help();
        }
        else if (strcmp(command, "list") == 0) {
            ls(current);
        }
        else if (strcmp(command, "new") == 0) {
            if (arg1) mkdir(current, arg1);
            else printf("Error: Usage: new <name>\n");
        }
        else if (strcmp(command, "goto") == 0) {
            if (arg1) {
                Folder* target = cd(current, arg1);
                if (target != NULL) current = target;
            } 
            else printf("Error: Usage: goto <name>\n");
        }
        else if (strcmp(command, "write") == 0) {
            if (arg1) {
                touch(current, arg1, arg2 ? arg2 : "");
            } 
            else printf("Error: Usage: write <name> <content>\n");
        }
        else if (strcmp(command, "read") == 0) {  // <--- NOVO BLOCO
            if (arg1) cat(current, arg1);
            else printf("Error: Usage: read <filename>\n");
        }
        else if (strcmp(command, "del") == 0) {
            if (arg1) rm(current, arg1);
            else printf("Error: Usage: del <name>\n");
        }
        else if (strcmp(command, "burn") == 0) {
            if (arg1) {
                if (strcmp(arg1, "..") == 0 || strcmp(arg1, ".") == 0) {
                    printf("Error: Cannot burn system paths.\n");
                } else {
                    burn(current, arg1);
                }
            }
            else printf("Error: Usage: burn <folder_name>\n");
        }
        else {
            printf("Unknown command: '%s'. Type 'help'.\n", command);
        }
    }

    destroy_system(root);
    return 0;
}
