#ifndef _PILHA_H_
#define _PILHA_H_

#include <stdlib.h>
#include <stdio.h>


typedef struct NoPilha{
    char * parametro;
    struct NoPilha * prox;
    int tipo;
}NoPilha;

typedef struct Pilha {
    NoPilha *topo;
} Pilha;


void inicializarPilha(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
void empilhar(Pilha *pilha, char *endereco,int tipo);
char* desempilhar(Pilha *pilha);
void liberarPilha(Pilha *pilha);
#endif