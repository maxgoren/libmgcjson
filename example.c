    #include <mgc/json/json.h>

    int main(int argc, char* argv[]) {
        char* raw = "{ \"taco\" : \"tuesday\", \"toppings\": [ \"lettuce\", \"onions\", \"salsa\"], \"otra vez\": { \"tortilla\": \"con salsa\" } }";
        JSONnode* as_json = toJSON(raw);
        dump(as_json);
        char* as_str = JSONtoString(as_json);
        JSONnode* member = getJSONElementByName(as_json, "toppings");
        JSONnode* element = getJSONArrayElementByIndex(member, 1);
        printf("_[toppings][1]=%s\n", JSONtoString(element));
        return 0;
    }
