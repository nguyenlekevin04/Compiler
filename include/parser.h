#include "token.h"
#include "lexer.h"

/**
 * @brief Represents an abstract syntax tree (AST) node.
 */
typedef struct Ast {
    enum {MULT, PLUS, MINUS, DIVIDE, DIGIT, INVALID} AstType;
    int value;
    struct Ast* right;
    struct Ast* left;
} Ast;

/**
 * @brief Gets the next token from the lexer.
 * @param l Pointer to the lexer.
 * @return The next token.
 */
Token getNextToken(Lexer* l);
/**
 * @brief Parses a factor from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseFactor(Lexer* l);
/**
 * @brief Parses a term from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseTerm(Lexer* l);
/**
 * @brief Parses an expression from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseExpression(Lexer* l);
/**
 * @brief Prints the abstract syntax tree.
 * @param node Pointer to the AST node to print.
 */
void printAst(Ast* node);