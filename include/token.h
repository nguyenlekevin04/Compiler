#ifndef TOKENHEADER_H
#define TOKENHEADER_H

#define COUNT 27

typedef enum{
    TOKEN_EOF,
    TOKEN_ILLEGAL,
    TOKEN_ID,
    TOKEN_DIGIT,
    TOKEN_ASSIGN,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_COMMA,
    TOKEN_EXCLAM,
    TOKEN_SEMICOLON,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_FUNC,
    TOKEN_LET,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_RETURN,
    TOKEN_TRUE,
    TOKEN_FALSE,
}Tokentype;


typedef struct {
    Tokentype Type;
    char* Lexeme;
}Token;

extern const char* tokens[];
Token createToken(Tokentype tokentype, char ch);
Token createDoubleCharToken(Tokentype tokentype, char ch1, char ch2);
void FreeToken(Token* t);

#endif