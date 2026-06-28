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
 * @brief Reads an identifier from the input string.
 * @param l Pointer to the lexer.
 * @return The identifier as a string.
 */
int isLetter(char c);
/**
 * @brief Reads an identifier from the input string.
 * @param l Pointer to the lexer.
 * @return The identifier as a string.
 */
char* readId(Lexer* l);
/**
 * @brief Determines the token type based on the identifier.
 * @param id The identifier string.
 * @return The corresponding token type.
 */
Tokentype DetermineTokentype(char* id);
/**
 * @brief Skips whitespace characters in the input string.
 * @param l Pointer to the lexer.
 */
void eatWhitespace(Lexer* l);
/**
* @brief Checks if the given character is a digit.
* @param c The character to check.
* @return 1 if the character is a digit, 0 otherwise.
*/
int isDigit(char c);
/**
 * @brief Reads a number from the input string.
 * @param l Pointer to the lexer.
 * @return The number as a string.
 */
char* readNumber(Lexer* l);
/**
 * @brief Peeks at the next character in the input string.
 * @param l Pointer to the lexer.
 * @return The next character.
 */
char peekChar(Lexer* l);
/**
 * @brief Checks if the given character is a letter.
 * @param c The character to check.
 * @return 1 if the character is a letter, 0 otherwise.
 */
void createCompoundToken(Lexer* l, Token* tok, Tokentype type1, Tokentype type2, char ch);
/**
 * @brief Reads an identifier from the input string.
 * @param l Pointer to the lexer.
 * @return The identifier as a string.
 */
Token createLiteralToken(Lexer* l, Token* tok);
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
 * @brief Peeks at the next token in the input string without consuming it.
 * @param l Pointer to the lexer.
 * @return The next token.
 */
Token peekToken(Lexer* l);
/**
 * @brief Peeks at the token after the next token in the input string without consuming it.
 * @param l Pointer to the lexer.
 * @return The token after the next token.
 */
Token peekNextToken(Lexer* l);
/**
 * @brief Frees the memory allocated for the lexer.
 * @param l Pointer to the lexer.
 */
void FreeLexer(Lexer* l);

#endif