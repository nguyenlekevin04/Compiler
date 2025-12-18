#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    char* input;
    int position;
    int readPosition;
    char ch;
}Lexer;

void readChar(Lexer* l);
Token GetToken(Lexer* l);
Lexer* New(char* input);
void FreeLexer(Lexer* l);
char peekChar(Lexer* l);

#endif