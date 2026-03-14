#ifndef json_h
#define json_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parse/ast.h"

/* convert string to JSON */
JSONnode* toJSON(char* raw);

/* convert string to JSON */
char* JSONtoString(JSONnode* json);

/* pretty print JSON object */
void dump(JSONnode* ast);

/* retrieve an object member by key */
JSONnode* getJSONElementByName(JSONnode* ast, char* key);

/* retrieve item from array by index*/
JSONnode* getJSONArrayElementByIndex(JSONnode* ast, int index);

void desroy_JSON(JSONnode* ast);

#endif