#include <stdio.h>
#include <stdlib.h>

#include "../include/interpreter.h"
#include "../include/symboltable.h"

int evaluate(Ast* node) {
    int result = 0;

    switch (node->AstType) {
        case ASSIGN:
            result = evaluate(node->left);
            set(node->name, result);
            break;
        case VAR:
            result = get(node->name);
            if (result == -1) {
                printf("Error: Variable '%s' not found\n", node->name);
                exit(1);
            }
            break;
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