#include "globals.h"
#include "scan.h"
#include "util.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "symtab.h"
#include "semantic.h"
#include "intermediario.h"
#include "assembler.h"
#include "pilha.h"
#include "binario.h"

//FILE * source_file;

unsigned char error = 0;
//TokenType tok;
//no *raiz_trie = NULL; // raiz global da trie quando não for usar o flex

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
/*
  raiz_trie = cria_no();
  insere(raiz_trie, "else", ELSE);
  insere(raiz_trie, "if", IF);
  insere(raiz_trie, "void", VOID);
  insere(raiz_trie, "while", WHILE);
  insere(raiz_trie, "int", INT);
  insere(raiz_trie, "return", RETURN);

  char *file_name = argv[1];
  source_file = fopen(file_name, "r");
*/
  source_file = fopen(argv[1],"r");
  if (source_file == NULL)
  {
    printf("File not found\n");
    exit(0);
  }

  TreeNode *raiz = NULL;
  printf("ANALISE SINTATICA\n");
  raiz = parse();
  if(raiz != NULL){
    printTreeR(raiz);
    buildSymtab(raiz);
    Quad * firstInst = NULL;
    firstInst = gerarIntermediario(raiz);
    NoInstrucao * assembly = NULL;
    assembly = geraAssembly(firstInst);
    geraBinario(assembly);
  }else{
    printf("Erro de sintaxe\n");
  
  }

  // problema no teste.txt -> -fp 

  /*while ((tok = getToken()) != ENDFILE && tok != ERROR)
  {
  }

  destroyTrie(raiz_trie);
  */
  return 0;
}
