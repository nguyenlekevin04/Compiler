#include <stdio.h>
#include <stdlib.h>

#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

#define PROMPT ">> "

void go(){
    char string[50];
    while(1) {
        printf(PROMPT);
        if (fgets(string, sizeof(string), stdin) == NULL) {
            return;
        }
        Lexer* l = New(string);

        Ast* ast = parseStatement(l);
        if (ast == NULL) {
            printf("Error: parseStatement returned NULL\n");
            continue;
        }
        printf("AST: ");
        printAst(ast);

        int result = evaluate(ast);
        printf("\nResult: %d\n", result);
    }
}

void lexerTest(char* input) {
    Lexer* l = New(input);
    Token tok;

    do {
        tok = GetToken(l);
        printf("Token: %s\n", tok.Lexeme);
        FreeToken(&tok);
    } while(tok.Type != TOKEN_EOF);

    FreeLexer(l);
}
