#ifndef TOKEN_H
#define TOKEN_H

#define COUNT 35

/**
 * @brief Represents the different types of tokens in the language.
 */
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
    TOKEN_PLUSEQ,
    TOKEN_MINUSEQ,
    TOKEN_MULTEQ,
    TOKEN_DIVEQ,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LE,
    TOKEN_GE,
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

/**
 * @brief Represents a token with its type and lexeme.
 */
typedef struct {
    Tokentype Type;
    char* Lexeme;
}Token;

/**
 * @brief An array of string representations for each token type.
 */
extern const char* tokens[];
/**
 * @brief Creates a new token with the specified type and lexeme.
 * @param tokentype The type of the token.
 * @param ch The character representing the token.
 * @return A new token instance.
 */
Token createToken(Tokentype tokentype, char ch);
/**
 * @brief Creates a new token with the specified type and lexeme.
 * @param tokentype The type of the token.
 * @param lexeme The string representing the token.
 * @return A new token instance.
 */
Token createDoubleCharToken(Tokentype tokentype, char ch1, char ch2);
/**
 * @brief Frees the memory allocated for a token.
 * @param t Pointer to the token to be freed.
 */
void FreeToken(Token* t);

#endif