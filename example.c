    #include <mgc/json/json.h>

    int main(int argc, char* argv[]) {
        char* raw = "{ \"taco\" : \"tuesday\", \"toppings\": [ \"lettuce\", \"onions\", \"salsa\"], \"otra vez\": { \"tortilla\": \"con salsa\" } }";
        JSON* as_json = toJSON(raw);
        printJSON(as_json);
        char* as_str = JSONtoString(as_json);
        JSON* member = getJSONElementByName(as_json, "toppings");
        JSON* element = getJSONArrayElementByIndex(member, 1);
        printf("_[toppings][1]=%s\n", JSONtoString(element));
        member = getJSONElementByName(as_json, "otra vez");
        element = getJSONElementByName(member, "tortilla");
        printf("%s\n", JSONtoString(element));
        return 0;
    }
