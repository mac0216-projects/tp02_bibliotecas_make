CC = gcc
CFLAGS = -fPIC -Wall -Wextra -Werror -Iinclude

# Define o prefixo de instalação padrão, mas permite sobrescrever via linha de comando
PREFIX ?= /usr/local

# Define o diretório onde os arquivos objeto (.o) serão armazenados
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = libs

TARGET = $(BIN_DIR)/calculadora_bf_estatica
TARGET_DYNAMIC = $(BIN_DIR)/calculadora_bf_dinamica
TEST_TARGET = $(BIN_DIR)/test_runner
STATIC_LIB = $(LIB_DIR)/libbf.a
DYNAMIC_LIB = $(LIB_DIR)/libbf.so

LIB_SRCS = src/gerenciamento_de_memoria_bf.c src/entrada_e_saida.c src/comparacao_bf.c src/bf_mensagem.c
APP_SRC = app/main.c
TEST_SRCS = tests/*.c

# Transforma os caminhos "src/arquivo.c" em "obj/arquivo.o" usando patsubst
LIB_OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(LIB_SRCS))
# Transforma os caminhos "app/arquivo.c" em "obj/arquivo.o" usando patsubst
APP_OBJ = $(patsubst app/%.c, $(OBJ_DIR)/%.o, $(APP_SRC))

all: $(TARGET) $(TARGET_DYNAMIC) $(DYNAMIC_LIB)

$(STATIC_LIB): $(LIB_OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(DYNAMIC_LIB): $(LIB_OBJ)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^

# Executável compilado com a biblioteca estática
$(TARGET): $(APP_OBJ) $(STATIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

# Executável compilado com a biblioteca dinâmica
$(TARGET_DYNAMIC): $(APP_OBJ) $(DYNAMIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(APP_OBJ) -L$(LIB_DIR) -lbf -o $@

# Regra genérica para compilar os .c da pasta src/ para a pasta obj/
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra genérica para compilar os .c da pasta app/ para a pasta obj/
$(OBJ_DIR)/%.o: app/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean run test install run_static run_dynamic

# Alvo clean remove os arquivos objetos e executaveis
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

# Alvo run roda a versão estática (comportamento padrão)
run: $(TARGET)
	./$(TARGET)

# Alvo run_dynamic roda a versão dinâmica
run_dynamic: $(TARGET_DYNAMIC)
	LD_LIBRARY_PATH=$(LIB_DIR) ./$(TARGET_DYNAMIC)

# Alvo test executa todos os testes automaticos 
test: $(STATIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) $(STATIC_LIB) -o $(TEST_TARGET)
	./$(TEST_TARGET) --test

# Alvo install copia a biblioteca compilada e os arquivos de interface (.h) para o PREFIX
install: all
	@mkdir -p "$(PREFIX)/lib"
	@mkdir -p "$(PREFIX)/include"
	cp $(STATIC_LIB) $(DYNAMIC_LIB) "$(PREFIX)/lib/"
	cp include/*.h "$(PREFIX)/include/"