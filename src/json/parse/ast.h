#ifndef ast_h
#define ast_h
#include <stdio.h>
#include <stdlib.h>
#include "token.h"

typedef enum NodeKind {
    object,
    array,
    kvpair,
    string,
    number,
    constant
} NodeKind;

typedef struct JSONnode {
    NodeKind kind;
    Token* token;
    struct JSONnode* next;
    struct JSONnode* left;
    struct JSONnode* right;    
} JSON;


JSON* makeNode(NodeKind kind, Token* token);

#endif