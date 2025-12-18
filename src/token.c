#include <stdio.h>
#include <stdlib.h>

#include "../include/token.h"

    const char* tokens[COUNT] = {
        [TOKEN_FUNC]      = "func",
        [TOKEN_LET]       = "let",
        [TOKEN_IF]        = "if",
        [TOKEN_ELSE]      = "else",
        [TOKEN_RETURN]    = "return",
        [TOKEN_TRUE]      = "true",
        [TOKEN_FALSE]     = "false"
    };

Token createToken(Tokentype tokentype, char ch){
    Token t;
    t.Type = tokentype;
    
    t.Lexeme = malloc(2 * sizeof(char));
    t.Lexeme[0] = ch;
    t.Lexeme[1] = '\0';

    return t;
}

Token createDoubleCharToken(Tokentype tokentype, char ch1, char ch2) {
    Token t;
    t.Type = tokentype;
    
    t.Lexeme = malloc(3 * sizeof(char));
    t.Lexeme[0] = ch1;
    t.Lexeme[1] = ch2;
    t.Lexeme[2] = '\0';

    return t;
}

void FreeToken(Token* t) {
    if (t) {
        free(t->Lexeme);
    }
}