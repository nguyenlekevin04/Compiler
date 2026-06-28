CC = gcc
SRC = src/lexer.c src/parser.c src/token.c src/main.c src/interpreter.c src/console.c src/symboltable.c
OUT = compiler

all:
	$(CC) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)