#include <stdio.h>

#include "../include/token.h"
#include "../include/lexer.h"
#include "../include/parser.h"

Token getNextToken(Lexer* l) {
    return GetToken(l);
}

Ast* Parse(Lexer* l) {
    Token tok = getNextToken(l);

    if(tok.Type != TOKEN_DIGIT) return NULL;

    Ast* leaf = malloc(sizeof(Ast));
    leaf->AstType = DIGIT;
    leaf->value = atoi(tok.Lexeme);
    leaf->left = leaf->right = NULL;
    Ast* current = leaf;

    while(1) {
        Token op = getNextToken(l);

        if(op.Type == TOKEN_EOF) break;

        if(op.Type != TOKEN_PLUS && op.Type != TOKEN_DIV && op.Type != TOKEN_MINUS && op.Type != TOKEN_MULT) return NULL;

        Ast* AstOp = malloc(sizeof(Ast));
        AstOp->AstType = (op.Type == TOKEN_PLUS) ? PLUS :
                         (op.Type == TOKEN_DIV) ? DIVIDE :
                         (op.Type == TOKEN_MINUS) ? MINUS :
                         (op.Type == TOKEN_MULT) ? MULT : INVALID;

        AstOp->left = current;

        Token dig = getNextToken(l);

        if(dig.Type != TOKEN_DIGIT) return NULL;

        Ast* AstRight = malloc(sizeof(Ast));
        AstRight->value = atoi(dig.Lexeme);
        AstRight->AstType = DIGIT;
        AstRight->left = AstRight->right = NULL;
        AstOp->right = AstRight;

        current = AstOp;
    }
    return current;
}

void FreeAst(Ast* ast) {
    if(ast) {
        free(ast);
    }
}