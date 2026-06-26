#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"
/**
 * @brief Evaluates the given AST node.
 * @param node Pointer to the AST node to evaluate.
 * @return The result of the evaluation as an integer.
 */
int evaluate(Ast* node);

#endif