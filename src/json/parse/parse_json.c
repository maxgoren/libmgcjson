#include "parse_json.h"
#include "ast.h"

JSON* makeNode(NodeKind kind, Token* token) {
    JSON* node = malloc(sizeof(struct JSONnode));
    node->kind = kind;
    node->token = token;
    node->next = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ParseState state;

Symbol lookahead() {
    return state.curr == NULL ? TK_EOI:state.curr->symbol;
}

void init(Token* tkns) {
    state.tokens = tkns;
    state.curr = state.tokens;
}

bool done() {
    return state.curr == NULL;
}

void advance() {
    if (!done())
        state.curr = state.curr->next;
}

bool expect(Symbol sym) {
    return sym == lookahead();
}

bool match(Symbol sym) {
    if (expect(sym)) {
        advance();
        return true;
    }
    printf("Mismatched token: %s\n",tokenStr[lookahead()]);
    return false;
}

JSON* parseObject() {
    JSON* node = NULL;
    if (expect(TK_LCURLY)) {
        node = makeNode(object, state.curr);
        match(TK_LCURLY);
        node->left = parseKVPair();
        JSON* tail = node->left;
        while (!done() && expect(TK_COMMA) && !expect(TK_RCURLY)) {
            match(TK_COMMA);
            JSON* t = parseKVPair();
            if (tail == NULL) {
                node->left = tail = t;
            } else {
                tail->next = t;
                tail = t;
            }
        }
        if (expect(TK_RCURLY)) {
            match(TK_RCURLY);
        } else {
            printf("Error: expected closing \'}\' for object.\n");
        }
    }
    return node;
}

JSON* parseArray() {
    JSON* node = NULL;
    if (expect(TK_LSQB)) {
        node = makeNode(array, state.curr);
        match(TK_LSQB);
        node->left = parseValue();
        JSON* tail = node->left;
        while (!done() && expect(TK_COMMA) && !expect(TK_RSQB)) {
            match(TK_COMMA);
            JSON* t = parseValue();
            if (tail == NULL) {
                node->left = tail = t;
            } else {
                tail->next = t;
                tail = t;
            }
        }
        if (expect(TK_RSQB)) {
            match(TK_RSQB);
        } else {
            printf("Error: expected missing ']' to close array.\n");
        }
    }
    return node;
}

JSON* parseKVPair() {
    JSON* kvp = NULL;
    Token* key;
    Token* value;
    if (expect(TK_STRING)) {
        key = state.curr;
        match(TK_STRING);
        if (expect(TK_COLON)) {
            kvp = makeNode(kvpair, state.curr);
            kvp->left = makeNode(string, key);
            match(TK_COLON);
            kvp->right = parseValue();
            if (kvp->right == NULL) {
                printf("Well shit.\n");
            }
        } else {
            printf("Invalid JSON: expected ':'\n");
        }
    } else {
        printf("Invalid JSON: expect string as key\n");
    }
    return kvp;
}

JSON* parseValue() {
    JSON* node = NULL;
    switch (lookahead()) {
        case TK_LCURLY:
            node = parseObject();
            break;
        case TK_LSQB:
            node = parseArray();
            break;
        case TK_NUM:
            node = makeNode(number, state.curr);
            match(TK_NUM);
            break;
        case TK_STRING:
            node = makeNode(string, state.curr);
            match(TK_STRING);
            break;
        case TK_TRUE:
        case TK_FALSE:
        case TK_NULL: 
            node = makeNode(constant, state.curr);
            match(lookahead());
            break;
        default:
            printf("No match on %s", tokenStr[lookahead()]);
            break;
    }
    return node;
}

JSON* parseElement() {
    return parseValue();
}
JSON* parseJson() {
    return parseElement();
}

JSON* parse(Token* tokens) {
    init(tokens);
    JSON* node = parseJson();
    return node;
}
