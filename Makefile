# Makefile para Compilador C-

all:
	flex lex.l
	bison -d parser.y
	gcc -c *.c
	gcc -g -o cmenos *.o -ll -lfl

# Remove apenas arquivos de compilação (mantém saídas)
clean:
	@echo "Removendo arquivos de compilação..."
	-rm -f *.o
	-rm -f cmenos
	-rm -f lex.yy.c
	-rm -f parser.tab.c
	-rm -f parser.tab.h
	@echo "Limpeza concluída! (saídas preservadas)"

# Limpeza completa incluindo saídas
clean-all:
	@echo "Removendo todos os arquivos gerados..."
	-rm -f *.o
	-rm -f cmenos
	-rm -f lex.yy.c
	-rm -f parser.tab.c
	-rm -f parser.tab.h
	-rm -f saidas/*.txt
	@echo "Limpeza completa concluída!"

# Recompila tudo
rebuild: clean all

.PHONY: all clean clean-all rebuild