#include <stdio.h>
#include <stdlib.h>

#include "../include/token.h"
#include "../include/lexer.h"
#include "../include/parser.h"

Ast* parseFactor(Lexer* l) {
    Token t1 = GetToken(l);

    if (t1.Type == TOKEN_DIGIT) {
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = DIGIT;
        node->data.digit.value = atoi(t1.Lexeme);
        return node;
    } else if (t1.Type == TOKEN_ID) {
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = VAR;
        node->data.var.name = t1.Lexeme;
        return node;
    } else {
        printf("Error: Expected a digit or identifier, but got %s\n", t1.Lexeme);
        return NULL;
    }
}

Ast* parseComparison(Lexer* l) {
    Ast* left = parseExpression(l);

    Token t1 = peekToken(l);
    if (t1.Type == TOKEN_EQ) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.op = EQ;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else if(t1.Type == TOKEN_NEQ) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.op = NE;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else if(t1.Type == TOKEN_LT) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.op = LT;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else if(t1.Type == TOKEN_GT) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.op = GT;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else if(t1.Type == TOKEN_LE) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.op = LE;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else if(t1.Type == TOKEN_GE) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.op = GE;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else {
        return left;
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
            node->data.assign.name = t1.Lexeme;
            node->data.assign.left = parseComparison(l);
            return node;
        } else if (t2.Type == TOKEN_PLUS || t2.Type == TOKEN_MINUS || t2.Type == TOKEN_MULT || t2.Type == TOKEN_DIV) {
            Ast* node = parseComparison(l);
            return node;
        } else if(t2.Type == TOKEN_PLUSEQ || t2.Type == TOKEN_MINUSEQ || t2.Type == TOKEN_MULTEQ || t2.Type == TOKEN_DIVEQ) {
            GetToken(l);
            GetToken(l);
            Ast* node = (Ast*)malloc(sizeof(Ast));
            node->AstType = BINOP;
            if (t2.Type == TOKEN_PLUSEQ) {
                node->data.binop.op = PLUSEQ;
            } else if (t2.Type == TOKEN_MINUSEQ) {
                node->data.binop.op = MINUSEQ;
            } else if (t2.Type == TOKEN_MULTEQ) {
                node->data.binop.op = MULTEQ;
            } else if (t2.Type == TOKEN_DIVEQ) {
                node->data.binop.op = DIVEQ;
            }
            node->data.binop.left = (Ast*)malloc(sizeof(Ast));
            node->data.binop.left->AstType = VAR;
            node->data.binop.left->data.var.name = t1.Lexeme;
            node->data.binop.right = parseComparison(l);
            return node;
        }else {
            printf("Error: Unexpected token after identifier: %s\n", t2.Lexeme);
            return NULL;
        }
    } else if (t1.Type == TOKEN_IF) {
        return parseIf(l);
    } else if (t1.Type == TOKEN_WHILE) {
        return parseWhile(l);
    } else {
        Ast* node = parseComparison(l);
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
        node->AstType = BINOP;
        node->data.binop.left = left;
        node->data.binop.right = parseTerm(l);
        node->data.binop.op = MULT;
        return node;
    } else if (t1.Type == TOKEN_DIV) {
        GetToken(l);
        Ast *node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.left = left;
        node->data.binop.right = parseTerm(l);
        node->data.binop.op = DIVIDE;
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
        node->AstType = BINOP;
        node->data.binop.op = PLUS;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else if (t1.Type == TOKEN_MINUS) {
        GetToken(l);
        Ast* node = (Ast*)malloc(sizeof(Ast));
        node->AstType = BINOP;
        node->data.binop.op = MINUS;
        node->data.binop.left = left;
        node->data.binop.right = parseExpression(l);
        return node;
    } else {
        return left;
    }
}

Ast* parseBlock(Lexer* l) {
    Token t1 = GetToken(l);

    if (t1.Type != TOKEN_LBRACE) {
        printf("Error: Expected '{' at the beginning of a block, but got %s\n", t1.Lexeme);
        return NULL;
    }
    
    Ast* head = parseStatement(l);
    Ast* current = head;
    while (peekToken(l).Type != TOKEN_RBRACE) {
        Ast* next = parseStatement(l);
        if (next == NULL) {
            printf("Error: Failed to parse statement in block\n");
            return NULL;
        }
        current->next = next;
        current = next;
    }
    GetToken(l);
    return head;
}

Ast* parseIf(Lexer* l) {
    Token t1 = GetToken(l);
    if (t1.Type != TOKEN_IF) {
        printf("Error: Expected 'if' keyword, but got %s\n", t1.Lexeme);
        return NULL;
    }

    Token t2 = GetToken(l);
    if (t2.Type != TOKEN_LPAREN) {
        printf("Error: Expected '(' after 'if', but got %s\n", t2.Lexeme);
        return NULL;
    }

    Ast* condition = parseComparison(l);
    Token t3 = GetToken(l); 
    if (t3.Type != TOKEN_RPAREN) {
        printf("Error: Expected ')' after condition, but got %s\n", t3.Lexeme);
        return NULL;
    }

    Ast* thenBranch = parseBlock(l);
    Ast* elseBranch = NULL;
    Token t4 = peekToken(l);
    if (t4.Type == TOKEN_ELSE) {
        GetToken(l);
        elseBranch = parseBlock(l);
    }

    Ast* ifNode = (Ast*)malloc(sizeof(Ast));
    ifNode->AstType = IF;
    ifNode->data.ifStmt.condition = condition;
    ifNode->data.ifStmt.thenBranch = thenBranch;
    ifNode->data.ifStmt.elseBranch = elseBranch;

    return ifNode;
}

Ast* parseWhile(Lexer* l) {
        Token t1 = GetToken(l);
    if (t1.Type != TOKEN_WHILE) {
        printf("Error: Expected 'while' keyword, but got %s\n", t1.Lexeme);
        return NULL;
    }

    Token t2 = GetToken(l);
    if (t2.Type != TOKEN_LPAREN) {
        printf("Error: Expected '(' after 'while', but got %s\n", t2.Lexeme);
        return NULL;
    }

    Ast* condition = parseComparison(l);
    Token t3 = GetToken(l); 
    if (t3.Type != TOKEN_RPAREN) {
        printf("Error: Expected ')' after condition, but got %s\n", t3.Lexeme);
        return NULL;
    }

    Ast* thenBranch = parseBlock(l);

    Ast* whileNode = (Ast*)malloc(sizeof(Ast));
    whileNode->AstType = WHILE;
    whileNode->data.whileStmt.condition = condition;
    whileNode->data.whileStmt.body = thenBranch;

    return whileNode;
}

void printAst(Ast* node) {
    if (node == NULL) {
        return;
    }
    if (node->AstType == ASSIGN) {
        printf("%s = ", node->data.assign.name);
        printAst(node->data.assign.left);
        return;
    }   

    switch (node->AstType) {
        case DIGIT:
            printf("%d ", node->data.digit.value);
            break;
        case BINOP:
            printAst(node->data.binop.left);
            switch (node->data.binop.op) {
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
                case EQ:
                    printf("== ");
                    break;
                case NE:
                    printf("!= ");
                    break;
                case LT:
                    printf("< ");
                    break;
                case GT:
                    printf("> ");   
                    break;
                case LE:
                    printf("<= ");
                    break;
                case GE:
                    printf(">= ");
                    break;
                case PLUSEQ:
                    printf("+= ");
                    break;
                case MINUSEQ:
                    printf("-= ");
                    break;
                case MULTEQ:
                    printf("*= ");
                    break;
                case DIVEQ:
                    printf("/= ");
                    break;
            }
            printAst(node->data.binop.right);
            break;
        case VAR:
            printf("%s ", node->data.var.name);
            break;
        case ASSIGN:
            printf("%s = ", node->data.assign.name);
            break;
        case IF:
            printf("if (");
            printAst(node->data.ifStmt.condition);
            printf(") { ");
            printAst(node->data.ifStmt.thenBranch);
            printf("} ");

            if (node->data.ifStmt.elseBranch != NULL) {
                printf("else { ");
                printAst(node->data.ifStmt.elseBranch);
                printf("} ");
            }
            break;
        case WHILE:
            printf("while (");
            printAst(node->data.whileStmt.condition);
            printf(") { ");
            printAst(node->data.whileStmt.body);
            printf("} ");
            break;
        default:
            printf("Invalid AST node type\n");
    }

    if (node->next != NULL) {
        printAst(node->next);
    }
}