libjson:
	gcc -c -fPIC src/json/json.c -o json.o
	gcc -c -fPIC src/json/parse/lex.c -o lex.o
	gcc -c -fPIC src/json/parse/lexer_matrix.c -o matrix.o
	gcc -c -fPIC src/json/parse/parse_json.c -o parse.o
	gcc -shared -o libmgcjson.so json.o lex.o matrix.o parse.o

install:
	mv libmgcjson.so /usr/local/lib
	#mkdir /usr/include/mgc
	#mkdir /usr/include/mgc/json
	#mkdir /usr/include/mgc/json/parse
	cp src/json/json.h /usr/include/mgc/json/json.h
	cp src/json/parse/lexer_matrix.h /usr/include/mgc/json/parse/lexer_matrix.h
	cp src/json/parse/ast.h /usr/include/mgc/json/parse/ast.h
	cp src/json/parse/token.h /usr/include/mgc/json/parse/token.h
	
clean:
	rm *.o