#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"

Token* makeLexToken(enum TKSymbol symbol, char* text, int length) {
    Token* tk = (Token*)malloc(sizeof(Token));
    tk->length = length;
    tk->text = (char*)malloc(sizeof(char)*(length+1));
    for (int i = 0; i < length; i++) {
        tk->text[i] = text[i];
    }
    tk->text[length] = '\0';
    tk->symbol = symbol;
    return tk;
}

Token* next_token(char* input) {
    int state = 1;
    int last_match = 0;
    int match_len = 0;
    bool in_quote = false;
    for (char* p = input; *p; *p++) {
        state = matrix[state][*p];
        if (state > 0 && accept[state] > -1) {
            last_match = state;
            match_len = (p-input)+1;
        }
        if (*p == '"' && *p-1 != '\\') {
            if (!in_quote) in_quote = true;
            else {
                in_quote = false;
                *p++;
                break;
            }
        }
        if (state < 1) {
            break;
        }
    }
    if (last_match == 0) {
        return NULL;
    }
    return makeLexToken(accept[last_match], input, match_len);
}


Token* tokenize_input(char* input) {
    Token head; Token* list = &head;
    for (int i = 0; i < strlen(input);) {
        while (input[i] == ' ' || input[i] == '\t' || input[i] == '\r' || input[i] == '\n') i++;
        Token* next = next_token(input+i);
        if (next != NULL) {
            i += next->length;
            list->next = next;
	    list = next;
        } else {
            i++;
        }
    }
    return head.next;
}

void printTokens(Token* head) {
	for (Token* it = head; it != NULL; it = it->next) 
		printf("<%s, %s>\n", tokenStr[it->symbol], it->text);
}