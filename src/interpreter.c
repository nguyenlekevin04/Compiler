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
                case EQ:
                    result = evaluate(node->data.binop.left) == evaluate(node->data.binop.right);
                    break;
                case NE:
                    result = evaluate(node->data.binop.left) != evaluate(node->data.binop.right);
                    break;
                case LT:
                    result = evaluate(node->data.binop.left) < evaluate(node->data.binop.right);
                    break;
                case GT:
                    result = evaluate(node->data.binop.left) > evaluate(node->data.binop.right);
                    break;
                case LE:
                    result = evaluate(node->data.binop.left) <= evaluate(node->data.binop.right);
                    break;
                case GE:
                    result = evaluate(node->data.binop.left) >= evaluate(node->data.binop.right);
                    break;
                case PLUSEQ:
                    result = evaluate(node->data.binop.left) + evaluate(node->data.binop.right);
                    set(node->data.binop.left->data.var.name, result);
                    break;
                case MINUSEQ:
                    result = evaluate(node->data.binop.left) - evaluate(node->data.binop.right);
                    set(node->data.binop.left->data.var.name, result);
                    break;
                case MULTEQ:
                    result = evaluate(node->data.binop.left) * evaluate(node->data.binop.right);
                    set(node->data.binop.left->data.var.name, result);
                    break;
                case DIVEQ: 
                    result = evaluate(node->data.binop.left) / evaluate(node->data.binop.right);
                    set(node->data.binop.left->data.var.name, result);
                    break;
                default:
                    printf("Error: Invalid binary operator\n");
                    exit(1);
            }
            break;
        case IF:
            if (evaluate(node->data.ifStmt.condition)) {
                while (node->data.ifStmt.thenBranch != NULL) {
                    result = evaluate(node->data.ifStmt.thenBranch);
                    node->data.ifStmt.thenBranch = node->data.ifStmt.thenBranch->next;
                }
            }else if (node->data.ifStmt.elseBranch != NULL) {
                result = evaluate(node->data.ifStmt.elseBranch);
            }
            break;
        case WHILE:
            while (evaluate(node->data.whileStmt.condition)) {
                result = evaluate(node->data.whileStmt.body);
            }
            break;
        default:
            printf("Error: Invalid AST node type\n");
            exit(1);
    }
    return result;
}