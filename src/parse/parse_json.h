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
JSONnode* parseJson();
JSONnode* parseElement();
JSONnode* parseValue();
JSONnode* parseObject();
JSONnode* parseArray();
JSONnode* parseKVPair();
JSONnode* parseJson();
JSONnode* parse(Token* tokens);

#endif