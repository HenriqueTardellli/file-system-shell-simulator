#include <stdio.h>
#include "fs_logic.h"

Folder* root;
Folder* current; // O nosso 'pwd' (print working directory)

int main() {
    printf("--- File System ---\n");
    
    root = create_system();
    current = root; // Começamos na raiz

    ls(current);

    printf("\n>> mkdir home\n");
    mkdir(current, "home");
    
    printf("\n>> mkdir bin\n");
    mkdir(current, "bin");

    printf("\n>> mkdir home (again)\n");
    mkdir(current, "home");

    printf("\n>> ls\n");
    ls(current);

    // Limpeza (ainda incompleta, vai limpar só a root por enquanto)
    destroy_system(root);
    
    return 0;
}
