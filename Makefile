CC = gcc
CFLAGS = -fPIC -Wall -Wextra -Werror -Iinclude
TARGET = calculadora_bf

LIB_SRCS = src/gerenciamento_de_memoria_bf.c src/entrada_e_saida.c src/comparacao_bf.c
APP_SRC = app/main.c
LIB_OBJ = $(LIB_SRCS:.c=.o)
APP_OBJ = $(APP_SRC:.c=.o)

STATIC_LIB = libbf.a
DYNAMIC_LIB = libbf.so

TEST_TARGET = test_runner
TEST_SRCS = tests/*.c

$(STATIC_LIB): $(LIB_OBJ)
	ar rcs $@ $^

$(DYNAMIC_LIB): $(LIB_OBJ)
	$(CC) -shared -o $@ $^

all: $(TARGET) $(DYNAMIC_LIB)

$(TARGET): $(APP_OBJ) $(STATIC_LIB)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean run test

clean:
	rm -f $(LIB_OBJ) $(APP_OBJ) $(STATIC_LIB) $(DYNAMIC_LIB) $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(STATIC_LIB)
	$(CC) $(CFLAGS) $(TEST_SRCS) $(STATIC_LIB) -o $(TEST_TARGET)
	./$(TEST_TARGET) --test