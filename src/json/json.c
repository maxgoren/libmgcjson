#include "json.h"
#include "parse/lex.h"
#include "parse/parse_json.h"

JSON* toJSON(char* raw) {
    return parse(tokenize_input(raw));
}

char* JSONtoString(JSON* json) {
    if (json != NULL) {
        char* lhs = JSONtoString(json->left);
        char* rhs = JSONtoString(json->right);
        lhs = (lhs) ? lhs:" ";
        rhs = (rhs) ? rhs:" ";
        char* buff = malloc(sizeof(char)*(strlen(lhs)+strlen(rhs)+json->token->length+1024));
        switch (json->kind) {
            case object: {
                sprintf(buff, "{ %s }", lhs);
                free(lhs);
            } break;
            case kvpair: {
                if (json->next != NULL) {
                    char* nhs = JSONtoString(json->next);
                    sprintf(buff, "%s: %s, %s", lhs, rhs, nhs);
                    free(lhs);
                    free(rhs);
                    free(nhs);
                } else {
                    sprintf(buff, "%s: %s", lhs, rhs);
                    free(lhs);
                    free(rhs);
                }
            } break;
            case array: {
                sprintf(buff, "[ ");
                if (json->left) {
                    JSON* tmp = json->left;
                    while (tmp) {
                        char* element = JSONtoString(tmp);
                        if (tmp->next != NULL) {
                            sprintf(buff, "%s%s, ", buff, element);
                        } else {
                            sprintf(buff, "%s%s", buff, element);
                        }
                        if (element != NULL) free(element);
                        tmp = tmp->next;
                    }
                }
                sprintf(buff, "%s ]", buff);
            } break;
            case number:
            case string:
            case constant: {
                sprintf(buff, "%s", json->token->text);
            }break;
            default:
                printf("Parse Error: %d:%s\n", json->kind, json->token->text);
        }
        return buff;
    }
    return NULL;
}

JSON* getJSONElementByName(JSON* ast, char* key) {
    if (ast ==  NULL)
        return NULL;
    if (ast->kind != object) {
        printf("Error: Not A JSON object...\n");
        return NULL;
    }
    JSON* members = ast->left;
    for (JSON* iter = members; iter != NULL; iter = iter->next) {
        if (iter->kind == kvpair) {
            char* t = iter->left->token->text+1;
            bool match = true;
            for (int i = 0; key[i]; i++) {
                if (key[i] != t[i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return iter->right;
            }
        }
    }
    printf("No such key '%s' in object\n", key);
    return NULL;
}

JSON* getJSONArrayElementByIndex(JSON* ast, int index) {
    if (ast ==  NULL)
        return NULL;
    if (ast->kind != array) {
        printf("Error: Not A JSON array...\n");
        return NULL;
    }
    JSON* members = ast->left;
    int i = 0;
    for (JSON* iter = members; iter != NULL; iter = iter->next) {
        if (i == index)
            return iter;
        i++;
    }
    return NULL;
}

/*

    For pretty printing JSON, called by printJSON();

*/
bool in_arr = false;
void __preorderJSON(JSON* ast, int d) {
    if (ast != NULL) {
        switch (ast->kind) {
            case object: {
                for (int i = 0; i < d; i++) printf(" ");
                printf("{\n");
                __preorderJSON(ast->left, d+1);
                printf("\n");
                for (int i = 0; i < d; i++) printf(" ");
                printf("}\n");
            } break;
            case array: {
                for (int i = 0; i < d; i++) printf(" ");
                printf("[");
                in_arr = true;
                __preorderJSON(ast->left, d+1);
                in_arr = false;
                for (int i = 0; i < d; i++) printf(" ");
                printf("]");
            } break;
            case kvpair: {
                __preorderJSON(ast->left,d);
                for (int i = 0; i < d; i++) printf(" ");
                printf(":");
                if (ast->right->kind == object)
                    __preorderJSON(ast->right, d+2);
                else __preorderJSON(ast->right, d);
            } break;
            case string:
            case number:
            case constant: {
                for (int i = 0; i < d; i++) printf(" ");
                printf("%s ", ast->token->text);
            } break;
            default:
                break;
        }
        if (ast->next != NULL)
            printf(",%s", in_arr ? "":"\n");
        __preorderJSON(ast->next, d);
    }
}

void printJSON(JSON* node) {
    __preorderJSON(node, 1);
    printf("\n");
}

void free_JSON(JSON* node) {
    if (node != NULL) {
        free_JSON(node->next);
        free_JSON(node->left);
        free_JSON(node->right);
        free(node->token);
        free(node);
    }
}