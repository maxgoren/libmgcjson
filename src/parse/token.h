#ifndef token_h
#define token_h
#include "lexer_matrix.h"
typedef struct Token_ {
    enum TKSymbol symbol;
    char* text;
    int length;
    struct Token_* next;
} Token;

void printTokens(Token* head);


#endif