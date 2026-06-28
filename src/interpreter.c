#include <stdio.h>
#include <stdlib.h>

#include "../include/interpreter.h"
#include "../include/symboltable.h"

int evaluate(Ast* node) {
    int result = 0;

    switch (node->AstType) {
        case ASSIGN:
            result = evaluate(node->data.assign.left);
            set(node->data.assign.name, result);
            break;
        case VAR:
            result = get(node->data.var.name);
            if (result == -1) {
                printf("Error: Variable '%s' not found\n", node->data.var.name);
                exit(1);
            }
            break;
        case DIGIT:
            return node->data.digit.value;
        case BINOP:
            switch (node->data.binop.op) {
                case PLUS:
                    result = evaluate(node->data.binop.left) + evaluate(node->data.binop.right);
                    break;
                case MINUS:
                    result = evaluate(node->data.binop.left) - evaluate(node->data.binop.right);
                    break;
                case MULT:
                    result = evaluate(node->data.binop.left) * evaluate(node->data.binop.right);
                    break;
                case DIVIDE:
                    result = evaluate(node->data.binop.left) / evaluate(node->data.binop.right);
                    break;
            }
            break;
        default:
            printf("Error: Invalid AST node type\n");
            exit(1);
    }
    return result;
}