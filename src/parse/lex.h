#ifndef lex_h
#define lex_h
#include "token.h"

Token* tokenize_input(char* input);
Token* next_token(char* input);
Token* makeLexToken(enum TKSymbol symbol, char* text, int length);

#endif