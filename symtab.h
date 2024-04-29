#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include <stdio.h>

void insertTab(char* nome,char * escopo, int tipoDados, int isVar, int lineno);
int lookup(char* nome, char* escopo);
int pegaTipoFunc(char* nome, char * escopo);

void printSymTab(FILE * listing);

#endif