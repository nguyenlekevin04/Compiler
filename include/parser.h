#include "token.h"
#include "lexer.h"

typedef struct Ast {
    enum {MULT, PLUS, MINUS, DIVIDE, DIGIT, INVALID} AstType;
    int value;
    struct Ast* right;
    struct Ast* left;
} Ast;