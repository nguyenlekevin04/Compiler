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
 * @brief Evaluates the given AST node.
 * @param node Pointer to the AST node to evaluate.
 * @return The result of the evaluation as an integer.
 */
int evaluate(Ast* node);

#endif