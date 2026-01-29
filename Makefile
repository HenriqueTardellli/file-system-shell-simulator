# --- Variáveis de Compilação ---
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
# -Wall -Wextra: Ativa avisos (warnings) para código perigoso
# -g: Adiciona informação de debug (necessário para o Valgrind/GDB)
# -Iinclude: Diz ao compilador para procurar .h na pasta 'include'

# --- Estrutura de Pastas ---
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# --- Ficheiros ---
# Procura todos os ficheiros .c dentro de src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Cria a lista de objetos .o correspondentes (ex: src/main.c -> obj/main.o)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# Nome do executável final
EXEC = $(BIN_DIR)/vfs_shell

# --- Regras (Targets) ---

# Regra padrão (o que acontece quando escreves apenas 'make')
all: directories $(EXEC)

# Regra para criar as pastas bin e obj se não existirem
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Regra para o Linker (junta todos os .o num executável)
$(EXEC): $(OBJS)
	@echo "🔨 A linkar o executável..."
	$(CC) $(CFLAGS) $^ -o $@
	@echo "✅ Compilação terminada com sucesso! Execute: ./$(EXEC)"

# Regra para compilar cada ficheiro .c individualmente em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "⚙️  A compilar $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar o projeto (remove binários e objetos)
clean:
	@echo "🧹 A limpar ficheiros temporários..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regra para rodar o programa
run: all
	@./$(EXEC)

# Regra para verificar memória (Estilo UA - Valgrind)
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)

.PHONY: all directories clean run valgrind
