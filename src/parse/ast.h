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

typedef struct JSONnode_ {
    NodeKind kind;
    Token* token;
    struct JSONnode_* next;
    struct JSONnode_* left;
    struct JSONnode_* right;    
} JSONnode;


JSONnode* makeNode(NodeKind kind, Token* token);

#endif