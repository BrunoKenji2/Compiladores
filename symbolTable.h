#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 127
#define SHIFT 4

typedef struct Symbol
{
    char name[50];
    int value;
    struct Symbol *next;
} Symbol;

int hash(char *key);
void insertSymbol(char *name, int value);
void removeSymbol(char *name);
Symbol *findSymbol(char *name);