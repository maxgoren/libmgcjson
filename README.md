# mgcjson

This is a simple C library for serializing/deserializing data from
string to json and vice-versa.

to use, include mgc/json/json.h and compile with -lmgcjson after installing on your system.

## installation

```
    make
    sudo make install
```

## usage

```
    #include <mgc/json/json.h>

    int main(int argc, char* argv[]) {
        char* raw = "{ \"taco\" : \"tuesday\", \"toppings\": [ \"lettuce\", \"onions\", \"salsa\"], \"otra vez\": { \"tortilla\": \"con salsa\" } }";
        JSONnode* as_json = toJSON(raw);
        dump(ast);
        char* as_str = JSONtoString(as_json);
        JSONnode* member = getJSONElementByName(ast, "toppings");
        JSONnode* element = getJSONArrayElementByIndex(member, 1);
        printf("_[toppings][1]=%s\n", JSONtoString(element));
        return 0;
    }
```