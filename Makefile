all:
	flex lex.l
	bison -d parser.y
	gcc -c *.c
	gcc -g -o cmenos *.o -ll -lfl