#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/symboltable.h"

SymbolTable* table = NULL;

void setSymbol(char* name, int value) {
    SymbolTable* entry = (SymbolTable*)malloc(sizeof(SymbolTable));
    entry->name = name;
    entry->value = value;
    entry->next = table;
    table = entry;
}

int getSymbol(char* name) {
    SymbolTable* current = table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        } else {
            current = current->next;
        }
    }
    return -1;
}

void pushScope() {
    SymbolTable* newScope = (SymbolTable*)malloc(sizeof(SymbolTable));
    newScope->name = NULL;
    newScope->value = 0;
    newScope->next = table;
    table = newScope;
}

void popScope() {
    while (table != NULL && table->name != NULL) {
        SymbolTable* temp = table;
        table = table->next;
        free(temp);
    }
    if (table != NULL) {
        SymbolTable* temp = table;
        table = table->next;
        free(temp);
    }
}