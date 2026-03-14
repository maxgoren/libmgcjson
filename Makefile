libjson:
	gcc -c -fPIC src/json/json.c -o json.o
	gcc -c -fPIC src/parse/lex.c -o lex.o
	gcc -c -fPIC src/parse/lexer_matrix.c -o matrix.o
	gcc -c -fPIC src/parse/parse_json.c -o parse.o
	gcc -shared -o libmgcjson.so json.o lex.o matrix.o parse.o

install:
	mv libmgcjson.so /usr/local/lib
	mkdir /usr/include/mgc
	mkdir /usr/include/mgc/parse
	mkdir /usr/include/mgc/json
	cp src/json/json.h /usr/include/mgc/json/json.h
	cp src/parse/lexer_matrix.h /usr/include/mgc/parse/lexer_matrix.h
	cp src/parse/ast.h /usr/include/mgc/parse/ast.h
	cp src/parse/token.h /usr/include/mgc/parse/token.h
	
clean:
	rm *.o