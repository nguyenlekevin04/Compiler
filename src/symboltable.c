#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/symboltable.h"

SymbolTable* table = NULL;

void set(char* name, int value) {
    SymbolTable* entry = (SymbolTable*)malloc(sizeof(SymbolTable));
    entry->name = name;
    entry->value = value;
    entry->next = table;
    table = entry;
}

int get(char* name) {
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