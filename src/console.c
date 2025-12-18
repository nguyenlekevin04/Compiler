#include <stdio.h>
#include <stdlib.h>

#include "../include/lexer.h"

#define PROMPT ">> "

void go(){
    char string[50];
        while(1) {
            printf(PROMPT);
            if (fgets(string, sizeof(string), stdin) == NULL) {
                return;
            }
            Lexer* l = New(string);
            printf("%s",string);

            Token tok = GetToken(l);
             do {                
                if (tok.Type == TOKEN_EOF) {
                    break;
                }
                printf("Type: %u, Lexeme: %s \n", tok.Type, tok.Lexeme);
                tok = GetToken(l);

            } while(1);
        }
}
