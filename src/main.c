#include <stdio.h>
#include "fs_logic.h"
\

int main() {
    printf("--- File System ---\n");
    
    root = create_system();
    current = root; 

    // 1. Criar pastas
    mkdir(current, "home");
    mkdir(current, "etc");

    // 2. Criar ficheiros na raiz
    touch(current, "kernel.c", "int main() {}");
    touch(current, "config.cfg", "version=1.0");

    // 3. Tentar criar duplicado
    touch(current, "kernel.c", "");

    // 4. Ver tudo misturado
    printf("\n>> ls (root)\n");
    ls(current);

    // 5. Testar o RM (se já tiveres implementado a lógica que discutimos antes)
    // printf("\n>> rm kernel.c\n");
    // rm(current, "kernel.c");
    // ls(current);

    destroy_system(root);
    return 0;
}
