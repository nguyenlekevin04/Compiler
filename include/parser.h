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