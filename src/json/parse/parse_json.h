#ifndef parse_json_h
#define parse_json_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include "ast.h"


typedef enum TKSymbol Symbol;

typedef struct ParseState_ {
    Token* tokens;
    Token* curr;
    int num_err;
} ParseState;

extern ParseState state;

Symbol lookahead();
void init(Token* tkns);
bool done();
void advance();
bool expect(Symbol sym);
bool match(Symbol sym);
JSON* parseJson();
JSON* parseValue();
JSON* parseObject();
JSON* parseArray();
JSON* parseKVPair();
JSON* parse(Token* tokens);

#endif