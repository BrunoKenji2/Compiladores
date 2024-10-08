#include "pilha.h"
#include <string.h>

void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

int pilhaVazia(Pilha *pilha) {
    return (pilha->topo == NULL);
}

void empilhar(Pilha *pilha, char *endereco,int tipo) {
    NoPilha *novoNo = (NoPilha*) malloc(sizeof(NoPilha));
    novoNo->parametro = (char*)malloc(strlen(endereco)*sizeof(char));
    strcpy(novoNo->parametro, endereco);
    novoNo->prox = pilha->topo;
    pilha->topo = novoNo;
    novoNo->tipo = tipo;

}

char* desempilhar(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        return NULL;
    }
    NoPilha *noRemovido = pilha->topo;
    char *endereco = noRemovido->parametro;
    pilha->topo = noRemovido->prox;
    free(noRemovido);
    return endereco;
}

void liberarPilha(Pilha *pilha) {
    while (!pilhaVazia(pilha)) {
        desempilhar(pilha);
    }
}
