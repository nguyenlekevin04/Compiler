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
    } else {
        printf("Error: Expected a digit, but got %s\n", t1.Lexeme);
        return NULL;
    }
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
        default:
            printf("Invalid AST node type\n");
    }

    printAst(node->right);
}

int main() {
    char input[256];
    printf("Enter an expression: ");
    fgets(input, sizeof(input), stdin);

    Lexer* lexer = New(input);
    Ast* ast = parseExpression(lexer);

    printf("Parsed AST (in-order traversal): ");
    printAst(ast);
    printf("\n");

    FreeLexer(lexer);
    return 0;
}