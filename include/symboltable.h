#ifndef symboltable_h
#define symboltable_h

/**
 * @brief Represents a symbol table entry.
 */
typedef struct SymbolTable {
    char* name;
    int value;
    struct SymbolTable* next;
} SymbolTable;
/**
 * @brief Head of the symbol table linked list.
*/
extern SymbolTable* table;

/**
 * @brief Sets a variable in the symbol table.
 * @param name The name of the variable.
 * @param value The value of the variable.
 */
void set(char* name, int value);
/**
 * @brief Gets the value of a variable from the symbol table.
 * @param name The name of the variable.
 * @return The value of the variable, or -1 if not found.
 */
int get(char* name);

#endif