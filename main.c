#include "globals.h"
#include "scan.h"

FILE *source_file;
TokenType tok;
no *raiz_trie = NULL; // raiz global da trie

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Less arguments than expected\n");
    exit(1);
  }
  if (argc > 2)
  {
    printf("More arguments than expected\n");
    exit(1);
  }

  raiz_trie = cria_no();
  insere(raiz_trie, "else", ELSE);
  insere(raiz_trie, "if", IF);
  insere(raiz_trie, "void", VOID);
  insere(raiz_trie, "while", WHILE);
  insere(raiz_trie, "int", INT);
  insere(raiz_trie, "return", RETURN);

  char *file_name = argv[1];
  source_file = fopen(file_name, "r");

  if (source_file == NULL)
  {
    printf("File not found\n");
    exit(1);
  }

  while ((tok = getToken()) != ENDFILE && tok != ERROR)
  {
  }

  destroyTrie(raiz_trie);
  return 0;
}
