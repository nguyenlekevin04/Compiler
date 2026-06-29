#include <stdio.h>
#include <stdlib.h>

#include "../include/interpreter.h"
#include "../include/symboltable.h"
#include "../include/functionTable.h"

int evaluateBinop(Ast* node) {
    int result = 0;
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
                setSymbol(node->data.binop.left->data.var.name, result);
                break;
            case MINUSEQ:
                result = evaluate(node->data.binop.left) - evaluate(node->data.binop.right);
                setSymbol(node->data.binop.left->data.var.name, result);
                break;
            case MULTEQ:
                result = evaluate(node->data.binop.left) * evaluate(node->data.binop.right);
                setSymbol(node->data.binop.left->data.var.name, result);
                break;
            case DIVEQ: 
                result = evaluate(node->data.binop.left) / evaluate(node->data.binop.right);
                setSymbol(node->data.binop.left->data.var.name, result);
                break;
            default:
                printf("Error: Invalid binary operator\n");
                exit(1);
        }
        return result;
}

int evaluateDef(Ast* node) {
    setFunction(node->data.def.name, node);
    return 0;
}

int evaluateCallFunc(Ast* node) {
    Ast* defNode = getFunction(node->data.callFunc.name);
    if (defNode == NULL) {
        printf("Error: Function '%s' not found\n", node->data.callFunc.name);
        exit(1);
    }

    pushScope();

    Ast* paramNode = defNode->data.def.head;
    Ast* argNode = node->data.callFunc.head;

    while (paramNode != NULL && argNode != NULL) {
        int argValue = evaluate(argNode);
        setSymbol(paramNode->data.var.name, argValue);

        paramNode = paramNode->next;
        argNode = argNode->next;
    }

    if (paramNode != NULL || argNode != NULL) {
        printf("Error: Mismatch in number of parameters and arguments for function '%s'\n", node->data.callFunc.name);
        exit(1);
    }

    int result = evaluate(defNode->data.def.body);
    
    popScope();

    return result;
}

int evaluate(Ast* node) {
    int result = 0;

    switch (node->AstType) {
        case ASSIGN:
            result = evaluate(node->data.assign.left);
            setSymbol(node->data.assign.name, result);
            break;
        case VAR:
            result = getSymbol(node->data.var.name);
            if (result == -1) {
                printf("Error: Variable '%s' not found\n", node->data.var.name);
                exit(1);
            }
            break;
        case DIGIT:
            return node->data.digit.value;
        case BINOP:
            return evaluateBinop(node);
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
                Ast* bodyNode = node->data.whileStmt.body;
                while (node->data.whileStmt.body != NULL) {
                    result = evaluate(node->data.whileStmt.body);
                    node->data.whileStmt.body = node->data.whileStmt.body->next;
                }
                node->data.whileStmt.body = bodyNode;
            }
            break;
        case DEF:
            result = evaluateDef(node);
            break;
        case CALLFUNC:
            result = evaluateCallFunc(node);
            break;
        default:
            printf("Error: Invalid AST node type\n");
            exit(1);
    }
    return result;
}