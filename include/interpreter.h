#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

/**
 * @brief Evaluates a binary operation AST node.
 * @param node Pointer to the binary operation AST node.
 * @return The result of the binary operation as an integer.
 */
int evaluateBinop(Ast* node);
/**
 * @brief Evaluates a function definition AST node.
 * @param node Pointer to the function definition AST node.
 * @return The result of the function definition as an integer.
 */
int evaluateDef(Ast* node);
/**
 * @brief Evaluates a function call AST node.
 * @param node Pointer to the function call AST node.
 * @return The result of the function call as an integer.
 */
int evaluateCallFunc(Ast* node);
/**
 * @brief Evaluates the given AST node.
 * @param node Pointer to the AST node to evaluate.
 * @return The result of the evaluation as an integer.
 */
int evaluate(Ast* node);

#endif