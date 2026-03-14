#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mgc/json/json.h>




int main(int argc, char* argv[]) {
    char* raw = "{ \"taco\" : \"tuesday\", \"toppings\": [ \"lettuce\", \"onions\", \"salsa\"], \"otra vez\": { \"tortilla\": \"con salsa\" } }";
    JSONnode* ast = toJSON(raw);
    dump(ast);
    printf("%s\n", JSONtoString(ast));
    printf("_[taco]=%s\n", getJSONElementByName(ast, "taco")->token->text);
    printf("_[otra vez]=");
    dump(getJSONElementByName(ast, "otra vez"));
    printf("_[otra vez][jimmy]=%s\n", getJSONElementByName(getJSONElementByName(ast, "otra vez"), "jimmy")->token->text);
    JSONnode* res = getJSONElementByName(ast, "toppings");
    if (res->kind == array)
        printf("_[toppings][1]=%s\n", getJSONArrayElementByIndex(res, 1)->token->text);
    else {
        printf("Wanted %d, got %d: ", array, res->kind);
        dump(res);
    }
    return 0;
}
