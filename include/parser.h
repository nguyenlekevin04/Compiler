#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"

/**
 * @brief Represents an abstract syntax tree (AST) node.
 */
typedef struct Ast {
    enum {DIGIT, BINOP, ASSIGN, IF, WHILE, VAR, INVALID} AstType;
    union {
        struct {int value;} digit;
        struct {struct Ast* left; struct Ast* right; enum {PLUS, MINUS, MULT, DIVIDE, EQ, NE, LT, GT, LE, GE, PLUSEQ, MINUSEQ, MULTEQ, DIVEQ} op;} binop;
        struct {char* name; struct Ast* left;} assign;
        struct {char* name;} var;
        struct {struct Ast* condition; struct Ast* thenBranch; struct Ast* elseBranch;} ifStmt;
        struct {struct Ast* condition; struct Ast* body;} whileStmt;
    }data;
    struct Ast* next;
} Ast;

/**
 * @brief Parses a factor from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseFactor(Lexer* l);
/**
 * @brief Parses a term from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseTerm(Lexer* l);
/**
 * @brief Parses an expression from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseExpression(Lexer* l);
/**
 * @brief Parses a comparison from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseComparison(Lexer* l);
/**
 * @brief Parses a block of statements from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseBlock(Lexer* l);
/**
 * @brief Parses an if statement from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseIf(Lexer* l);
/**
 * @brief Parses a while statement from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseWhile(Lexer* l);
/**
 * @brief Parses an assignment statement from the lexer.
 * @param l Pointer to the lexer.
 * @param t1 The token representing the variable being assigned to.
 * @return A pointer to the parsed AST node.
 */
Ast* parseAssign(Lexer* l, Token t1);
/**
 * @brief Parses a statement from the lexer.
 * @param l Pointer to the lexer.
 * @return A pointer to the parsed AST node.
 */
Ast* parseStatement(Lexer* l);
/**
 * @brief Prints the abstract syntax tree.
 * @param node Pointer to the AST node to print.
 */
void printAst(Ast* node);

#endif