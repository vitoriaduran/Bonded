# Compilador
CC = gcc

# Flags de compilação (Inclui o caminho para headers)
CFLAGS = -Wall -Iinclude -Iraylib/src

# Bibliotecas necessárias (Raylib + dependências do Linux)
# CORREÇÃO: Adiciona a flag -L para indicar onde a biblioteca (libraylib.a) está.
LIBS = -Lraylib/src -lraylib -lm -lpthread -ldl -lGL -lX11

# Diretórios
SRC = src
BIN = bonded

# Lista todos os arquivos .c da pasta src
SRCS = $(wildcard $(SRC)/*.c)

# Cria os arquivos .o correspondentes
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(BIN)

# Como compilar o executável
# Agora, a variável LIBS inclui o caminho (-Lraylib/src)
$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LIBS)

# Para rodar o programa
run: $(BIN)
	./$(BIN)

# Para limpar arquivos compilados
clean:
	rm -f $(SRC)/*.o $(BIN)

