#include <stdio.h>
#include <stdlib.h>

#include "../include/token.h"
#include "../include/lexer.h"
#include "../include/parser.h"

Token getNextToken(Lexer* l) {
    return GetToken(l);
}

Ast* parseFactor(Lexer* l) {
    Token t1 = getNextToken(l);

    if (t1.Type == TOKEN_DIGIT) {
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = DIGIT;
        node->value = atoi(t1.Lexeme);
        node->left = NULL;
        node->right = NULL;
        return node;
    } else if (t1.Type == TOKEN_ID) {
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = VAR;
        node->name = t1.Lexeme;
        node->left = NULL;
        node->right = NULL;
        return node;
    } else {
        printf("Error: Expected a digit or identifier, but got %s\n", t1.Lexeme);
        return NULL;
    }
}

Ast* parseStatement(Lexer* l) {
    Token t1 = peekToken(l);
    if (t1.Type == TOKEN_ID) {
        Token t2 = peekNextToken(l);
        if (t2.Type == TOKEN_ASSIGN) {
            GetToken(l);
            GetToken(l);
            Ast* node = (Ast*)malloc(sizeof(Ast));
            node->AstType = ASSIGN;
            node->name = t1.Lexeme;
            node->left = parseExpression(l);
            node->right = NULL;
            return node;
        } else if (t2.Type == TOKEN_PLUS || t2.Type == TOKEN_MINUS || t2.Type == TOKEN_MULT || t2.Type == TOKEN_DIV) {
            Ast* node = parseExpression(l);
            return node;
        } else {
            printf("Error: Unexpected token after identifier: %s\n", t2.Lexeme);
            return NULL;
        }
    } else {
        Ast* node = parseExpression(l);
        return node;
    }
    printf("Error: Invalid statement\n");
    return NULL;
}

Ast* parseTerm(Lexer* l) {
    Ast* left = parseFactor(l);

    Token t1 = peekToken(l);
    if (t1.Type == TOKEN_MULT) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = MULT;
        node->left = left;
        node->right = parseTerm(l);
        return node;
    } else if (t1.Type == TOKEN_DIV) {
        GetToken(l);
        Ast *node = (Ast*)malloc(sizeof(Ast));
        node->AstType = DIVIDE;
        node->left = left;
        node->right = parseTerm(l);
        return node;
    } else {
        return left;
    }
}

Ast* parseExpression(Lexer* l) {
    Ast* left = parseTerm(l);

    Token t1 = peekToken(l);
    if (t1.Type == TOKEN_PLUS) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = PLUS;
        node->left = left;
        node->right = parseExpression(l);
        return node;
    } else if (t1.Type == TOKEN_MINUS) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = MINUS;
        node->left = left;
        node->right = parseExpression(l);
        return node;
    } else {
        return left;
    }
}

void printAst(Ast* node) {
    if (node == NULL) {
        return;
    }
    if (node->AstType == ASSIGN) {
        printf("%s = ", node->name);
        printAst(node->left);
        return;
    }   

    printAst(node->left);

    switch (node->AstType) {
        case DIGIT:
            printf("%d ", node->value);
            break;
        case PLUS:
            printf("+ ");
            break;
        case MINUS:
            printf("- ");
            break;
        case MULT:
            printf("* ");
            break;
        case DIVIDE:
            printf("/ ");
            break;
        case VAR:
            printf("%s ", node->name);
            break;
        case ASSIGN:
            printf("%s = ", node->name);
            break;
        default:
            printf("Invalid AST node type\n");
    }

    if (node->right != NULL) {
        printAst(node->right);
    }
}