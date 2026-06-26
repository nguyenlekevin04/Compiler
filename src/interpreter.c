#include <stdio.h>
#include <stdlib.h>

#include "../include/interpreter.h"

int evaluate(Ast* node) {
    int result = 0;

    switch (node->AstType) {
        case DIGIT:
            return node->value;
        case PLUS:
            result = evaluate(node->left) + evaluate(node->right);
            break;
        case MINUS:
            result = evaluate(node->left) - evaluate(node->right);
            break;
        case MULT:
            result = evaluate(node->left) * evaluate(node->right);
            break;
        case DIVIDE:
            result = evaluate(node->left) / evaluate(node->right);
            break;
        default:
            printf("Error: Invalid AST node type\n");
            exit(1);
    }
    return result;
}