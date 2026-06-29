#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/functionTable.h"
#include "../include/parser.h"

FunctionTable* functionTable = NULL;

void setFunction(char* name, Ast* body) {
    FunctionTable* entry = (FunctionTable*)malloc(sizeof(FunctionTable));
    entry->name = name;
    entry->defNode = body;
    entry->next = functionTable;
    functionTable = entry;
}

Ast* getFunction(char* name) {
    FunctionTable* current = functionTable;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->defNode;
        } else {
            current = current->next;
        }
    }
    return NULL;
}