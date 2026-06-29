#ifndef functionTable_h
#define functionTable_h

/**
 * @brief Represents a function table entry.
 */
typedef struct FunctionTable {
    char* name;
    struct Ast* defNode;
    struct FunctionTable* next;
} FunctionTable;

/**
 * @brief Head of the function table linked list.
*/
extern FunctionTable* functionTable;
/**
 * @brief Sets a function in the function table.
 * @param name The name of the function.
 * @param defNode The AST node representing the function definition.
 */
void setFunction(char* name, struct Ast* defNode);
/**
 * @brief Gets the AST node of a function from the function table.
 * @param name The name of the function.
 * @return A pointer to the AST node representing the function definition, or NULL if not found.
 */
struct Ast* getFunction(char* name);

#endif