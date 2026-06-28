#include <string.h>
#include <stdlib.h>

#include "../include/token.h"
#include "../include/lexer.h"

void readChar(Lexer* l){
    if (l->readPosition >= strlen(l->input)) {
        l->ch = 0;
        l->position = l->readPosition;
        return;
    } else {
        l->ch = l->input[l->readPosition];
    }
    l->position = l->readPosition;
    l->readPosition += 1;
}

int isLetter(char c) {
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

char* readId(Lexer* l) {
    int pos = l->position;

    while(isLetter(l->ch)) {
        readChar(l);
    }
    int length = l->position - pos;
    char* word = malloc(length + 1);

    for(int i = 0; i < length; i++) {
        word[i] = l->input[pos+i];
    }
    word[length] = '\0';

    return word;
}

Tokentype DetermineTokentype(char* id) {
    for (int i = 0; i < COUNT; i++) {
        if (tokens[i] != NULL && strcmp(tokens[i], id) == 0) return i;
    }
    return TOKEN_ID;
}

void eatWhitespace(Lexer* l) {
    for(;l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r';) {
        readChar(l);
    }
}
int isDigit(char c) {
    return '0' <= c && '9' >= c;
}

char* readNumber(Lexer* l) {
    int pos = l->position;

    while(isDigit(l->ch)) {
        readChar(l);
    }
    int length = l->position - pos;
    char* word = malloc(length + 1);

    for(int i = 0; i < length; i++) {
        word[i] = l->input[pos+i];
    }

    word[length] = '\0';

    return word;
} 

char peekChar(Lexer* l) {
    if(l->readPosition >= strlen(l->input))return 0;
    else return l->input[l->readPosition];
}

Token GetToken(Lexer* l){
    Token tok;

    eatWhitespace(l);

    switch (l->ch) {
        case '{':
            tok = createToken(TOKEN_LBRACE, l->ch);
            break;
        case '}':
            tok = createToken(TOKEN_RBRACE, l->ch);
            break;
        case '(':
            tok = createToken(TOKEN_LPAREN, l->ch);
            break;
        case ')':
            tok = createToken(TOKEN_RPAREN, l->ch);
            break;
        case '=':
            if(peekChar(l) == '=') {
                char ch = l->ch;

                readChar(l);
                tok = createDoubleCharToken(TOKEN_EQ, ch, l->ch);
                break;
            } else {
                tok = createToken(TOKEN_ASSIGN, l->ch);
                break;
            }
        case '+':
            tok = createToken(TOKEN_PLUS, l->ch);
            break;
        case ';':
            tok = createToken(TOKEN_SEMICOLON, l->ch);
            break;
        case ',':
            tok = createToken(TOKEN_COMMA, l->ch);
            break;
        case '-':
            tok = createToken(TOKEN_MINUS, l->ch);
            break;
        case '*':
            tok = createToken(TOKEN_MULT, l->ch);
            break;
        case '/':
            tok = createToken(TOKEN_DIV, l->ch);
            break;
        case '<': 
            tok = createToken(TOKEN_LT, l->ch);
            break;
        case '>': 
            tok = createToken(TOKEN_GT, l->ch);
            break;
        case '!':
            if(peekChar(l) == '=') {
                char ch = l->ch;

                readChar(l);
                tok = createDoubleCharToken(TOKEN_NEQ, ch, l->ch);
                break;
            } else {
                tok = createToken(TOKEN_EXCLAM, l->ch);
                break;
        }
        case '\0':
            tok.Lexeme = "";
            tok.Type = TOKEN_EOF;
            break;
        default:
            if (isLetter(l->ch)) {
                tok.Lexeme = readId(l);
                tok.Type = DetermineTokentype(tok.Lexeme);
                return tok;
            } else if(isDigit(l->ch)) {
                tok.Lexeme = readNumber(l);
                tok.Type = TOKEN_DIGIT;
                return tok;
            } else {
                tok = createToken(TOKEN_ILLEGAL, l->ch);
                break;
            }
    }
    readChar(l);
    return tok;
}

Lexer* New(char* input){
    Lexer* l = malloc(sizeof(Lexer));
    l->input = malloc(strlen(input) + 1);

    strcpy(l->input, input);
    readChar(l);

    return l;
}

Token peekToken(Lexer* l) {
    int currentPosition = l->position;
    int currentReadPosition = l->readPosition;
    char currentChar = l->ch;

    Token tok = GetToken(l);

    l->position = currentPosition;
    l->readPosition = currentReadPosition;
    l->ch = currentChar;

    return tok;
}

Token peekNextToken(Lexer* l) {
    int currentPosition = l->position;
    int currentReadPosition = l->readPosition;
    char currentChar = l->ch;

    GetToken(l);
    Token tok = GetToken(l);

    l->position = currentPosition;
    l->readPosition = currentReadPosition;
    l->ch = currentChar;

    return tok;
}

void FreeLexer(Lexer* l){
    if (l) {
        free(l->input);
        free(l);
    }
}