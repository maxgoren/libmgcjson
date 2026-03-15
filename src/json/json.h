#ifndef json_h
#define json_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/ast.h"

/* convert string to JSON */
JSON* toJSON(char* raw);

/* convert string to JSON */
char* JSONtoString(JSON* json);

/* pretty print JSON object */
void dump(JSON* ast);

/* retrieve an object member by key */
JSON* getJSONElementByName(JSON* ast, char* key);

/* retrieve item from array by index*/
JSON* getJSONArrayElementByIndex(JSON* ast, int index);

void free_JSON(JSON* ast);

#endif