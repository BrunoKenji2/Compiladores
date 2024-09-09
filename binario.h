#ifndef BINARIO_H
#define BINARIO_H
#include "assembler.h"

void geraBinario(NoInstrucao * assembly);
char * conversorInst(NoInstrucao * inst);
void imprimeBinario(int * binario, int bits);
#endif