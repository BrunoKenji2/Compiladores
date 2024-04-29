#include "symtab.h"
#include "globals.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "util.h"

#define SIZE 211
#define SHIFT 4

// ------------------ tabela hash -------------------

typedef struct LineListRec
{
    int lineno;
    struct LineListRec * next;  // as linhas que a var aparece
} * LineList;

typedef struct hashCell
{
    char * nome;
    char * escopo;
    int tipoDados; // 1 = inteiro, 0 = void
    int isVar;  // 1 = função
    LineList linhas;
    struct hashCell * prox;
} * hashList;

static hashList hashTable[SIZE];    // tabela hash

// pega a chave que é o indice da tabela
static int hash (char * key)
{
    int temp = 0;
    int i = 0;
    while (key[i] != '\0')
    {
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

void insertTab(char* nome,char * escopo, int tipoDados, int isVar, int lineno){

    char nomeConcat[100];
    strcpy(nomeConcat, nome);
    strcat(nomeConcat, escopo); // concatena o nome com o escopo para ver a key

    int key = hash(nomeConcat);
    hashList cel = hashTable[key];
    
    while((cel != NULL) && (strcmp(nome, cel->nome) != 0)){ // caso ja tenha um elemento com o mesmo nome
        cel = cel->prox;
    }
    // se não tem o elemento na tabela
    if( cel == NULL){
        cel = (hashList) malloc(sizeof(struct hashCell));
        cel->nome = nome;
        cel->escopo = copyString(escopo);
        cel->tipoDados = tipoDados;
        cel->isVar = isVar;
        cel->linhas = (LineList) malloc(sizeof(struct LineListRec));
        cel->linhas->lineno = lineno;
        cel->linhas->next = NULL;
        cel->prox = hashTable[key];
        hashTable[key] = cel;
    }else{
        // caso a var apareça em mais de uma linha
        LineList l = cel->linhas;
        while(l->next != NULL){
            l = l->next;
        }
        l->next = (LineList) malloc(sizeof(struct LineListRec));
        l->next->lineno = lineno;
        l->next->next = NULL;
    }

}

int lookup(char* nome, char* escopo){
    char nomeConcat[100];
    strcpy(nomeConcat, nome);
    strcat(nomeConcat, escopo); // concatena o nome com o escopo para ver a key

    int key = hash(nomeConcat);
    hashList cel = hashTable[key];
    while((cel != NULL) && (strcmp(nome, cel->nome) != 0)){
        cel = cel->prox;
    }
    if(cel == NULL){
        return 0;  // não achou
    }else{
        return 1;   // achou
    }
}

int pegaTipoFunc(char* nome, char * escopo){
    char nomeConcat[100];
    strcpy(nomeConcat, nome);
    strcat(nomeConcat, escopo); // concatena o nome com o escopo para ver a key

    int key = hash(nomeConcat);
    hashList cel = hashTable[key];
    while((cel != NULL) && (strcmp(nome, cel->nome) != 0)){
        cel = cel->prox;
    }
    if(cel == NULL){
        return -1;  // não achou
    }else{
        return cel->tipoDados;   // achou
    }
}

void printSymTab(FILE * listing){
    int i;
    int size = 0, j = 0;
    fprintf(listing,"                    Nome                   Var/func  Tipo         Escopo                       Número de linhas\n");
    fprintf(listing,"-----------------------------------------  --------  ----  --------------------  ------------------------------------------------\n");
    for (i=0;i<SIZE;++i){
        if (hashTable[i] != NULL){
        hashList l = hashTable[i];
            while (l != NULL){
                LineList t = l->linhas;
                fprintf(listing,"%s",l->nome);
                size = strlen(l->nome);
                for(j=0;j<43-size;j++)
                    fprintf(listing," ");

                if(l->isVar)
                    fprintf(listing,"variável  ");
                else 
                    fprintf(listing,"funcao    ");

                if(l->tipoDados) 
                    fprintf(listing,"int   ");
                else 
                    fprintf(listing,"void  ");

                fprintf(listing,"%s ",l->escopo);
                size = strlen(l->escopo);
                for(j=0;j<21-size;j++)
                    fprintf(listing," ");

				while (t != NULL){
                    fprintf(listing,"%d, ",t->lineno);
                    t = t->next;
                }
                fprintf(listing,"\n");
                l = l->prox;
            }
        }
    }
}