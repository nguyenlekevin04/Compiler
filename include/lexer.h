#ifndef LEXER_H
#define LEXER_H

#include "token.h"

/**
 * @brief Represents a lexer that tokenizes the input string.
 */
typedef struct {
    char* input;
    int position;
    int readPosition;
    char ch;
}Lexer;

/**
 * @brief Reads the next character from the input string.
 * @param l Pointer to the lexer.
 */
void readChar(Lexer* l);
/**
 * @brief Gets the next token from the input string.
 * @param l Pointer to the lexer.
 * @return The next token.
 */
Token GetToken(Lexer* l);
/**
 * @brief Creates a new lexer instance.
 * @param input The input string to tokenize.
 * @return A pointer to the new lexer instance.
 */
Lexer* New(char* input);
/**
 * @brief Frees the memory allocated for the lexer.
 * @param l Pointer to the lexer.
 */
void FreeLexer(Lexer* l);
/**
 * @brief Peeks at the next character in the input string.
 * @param l Pointer to the lexer.
 * @return The next character.
 */
char peekChar(Lexer* l);
/**
 * @brief Peeks at the next token in the input string without consuming it.
 * @param l Pointer to the lexer.
 * @return The next token.
 */
Token peekToken(Lexer* l);
#endif