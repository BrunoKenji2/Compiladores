#include "binario.h"
#include "assembler.h"
#include "globals.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
    NOT SR LOADI MOVE NOP HLT
*/
// Função para converter decimal em binário e retornar uma string com tamanho específico
char* decimalParaBinario(int numero, int size) {
    // Aloca memória para a string binária com o tamanho especificado + 1 para o caractere nulo
    char *binario = (char *)malloc(size + 1);
    if (binario == NULL) {
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    // Inicializa a string com zeros
    memset(binario, '0', size);
    binario[size] = '\0'; // Adiciona o caractere nulo ao final da string

    // Converte o número decimal para binário
    int i = size - 1; // Começa do final da string
    while (numero > 0 && i >= 0) {
        binario[i] = (numero % 2) ? '1' : '0'; // Adiciona o bit menos significativo
        numero /= 2; // Divide o número por 2 para a próxima iteração
        i--;
    }

    return binario;
}

char *  converteInst(NoInstrucao * ins){
    char * rs = (char *)malloc(sizeof(char)*7);
    char * rt = (char *)malloc(sizeof(char)*7);
    char * rd = (char *)malloc(sizeof(char)*7);
    char * imediato = (char *)malloc(sizeof(char)*15);
    char * endereco = (char *)malloc(sizeof(char)*27);
    char * funct = (char *)malloc(sizeof(char)*7);
    char * opcode = (char *)malloc(sizeof(char)*7);
    char * binario = (char *)malloc(sizeof(char)*33);

    if(ins->tipo == 0){
        if(ins->inst == JUMP){
            strcpy(opcode,"011100");
            strcpy(endereco,decimalParaBinario(pegaLinhaLabel(ins->endereco)-1,26));
            strcpy(binario,opcode);
            strcat(binario,endereco);
        }else if(ins->inst == JAL){
            strcpy(opcode,"011101");
            strcpy(endereco,decimalParaBinario(pegaLinhaLabel(ins->endereco)-1,26));
            strcpy(binario,opcode);
            strcat(binario,endereco);
        }
    }else if(ins->tipo == 1){
        strcpy(funct,"000");
        switch(ins->inst){
            case ADD:
                strcpy(opcode,"000000");         
                break;
            case SUBB:
                strcpy(opcode,"000001");
                break;
            case MULT:
                strcpy(opcode,"000010");
                break;
            case DIVV:
                strcpy(opcode,"000011");
                break;
            case AND:   //set less than
                strcpy(opcode,"000100");
                break;
            case OR:
                strcpy(opcode,"000101");
                break;
            case SLT:
                strcpy(opcode,"001000");
                break;
            case SGT:
                strcpy(opcode,"");
                break;
            case SLET:
                strcpy(opcode,"001001");
                break;
            case SGET: 
                strcpy(opcode,"001010");
                break;
            case SET:
                strcpy(opcode,"100011");
                break;
            case SDT:
                strcpy(opcode,"001100");
                break;
            case SLL:
                strcpy(opcode,"001101");
                break;
            case SRL:
                strcpy(opcode,"001110");
                break;
            case MOD:
                strcpy(opcode,"001111");
                break;
            case JR:
                strcpy(opcode,"001100");
                break;
        }
        if(ins->inst == JR){
            strcpy(rs,decimalParaBinario(ins->reg1,6));
            strcpy(rt,"000000");
            strcpy(rd,"000000");
            strcpy(imediato,"00000");
            strcpy(binario,opcode);
            strcat(binario,rs);
            strcat(binario,rt);
            strcat(binario,rd);
            strcat(binario,imediato);
            strcat(binario,funct);
        }else{
            strcpy(rs,decimalParaBinario(ins->reg1,6));
            strcpy(rt,decimalParaBinario(ins->reg2,6));
            strcpy(rd,decimalParaBinario(ins->reg3,6));
            strcpy(imediato,"00000");
            strcpy(binario,opcode);
            strcat(binario,rs);
            strcat(binario,rt);
            strcat(binario,rd);
            strcat(binario,imediato);
            strcat(binario,funct);

        }
    }else if(ins->tipo == 2){
        // inst I
        if(ins->inst == ADDI){
            strcpy(opcode,"001111");
        }else if(ins->inst == SUBI){
            strcpy(opcode,"010000");
        }else if(ins->inst == MULTI){
            strcpy(opcode,"000101");
        }else if(ins->inst == DIVI){
            strcpy(opcode,"100100");
        }else if(ins->inst == ANDI){
            strcpy(opcode,"001010");
        }else if(ins->inst == ORI){
            strcpy(opcode,"001100");
        }else if(ins->inst == SLTI){
            strcpy(opcode,"000111");
        }else if(ins->inst == SGTI){
            strcpy(opcode,"");
        }else if(ins->inst == SLETI){
            strcpy(opcode,"001001");
        }else if(ins->inst == SGETI){
            strcpy(opcode,"001010");
        }else if(ins->inst == SETI){
            strcpy(opcode,"001011");
        }else if(ins->inst == SDTI){
            strcpy(opcode,"001100");
        }else if(ins->inst == MODI){
            strcpy(opcode,"001101");
        }else if(ins->inst == BLTZ){
            strcpy(opcode,"001110");
        }else if(ins->inst == BGTZ){
            strcpy(opcode,"001111");
        }else if(ins->inst == BEQZ){
            strcpy(opcode,"010111");
        }else if(ins->inst == BEQ){
            strcpy(opcode,"010011");
        }else if(ins->inst == BNE){
            strcpy(opcode,"011000");
        }else if(ins->inst == LW){
            strcpy(opcode,"011001");
        }else if(ins->inst == SW){
            strcpy(opcode,"011010");
        }else if(ins->inst == LUI){
            strcpy(opcode,"010101");
        }
        if(ins->inst == BEQ){
            strcpy(imediato,decimalParaBinario(pegaLinhaLabel(ins->imediato)-1,14));
        }else{
            strcpy(imediato,decimalParaBinario(atoi(ins->imediato),14));
        
        }
        strcpy(rs,decimalParaBinario(ins->reg1,6));
        strcpy(rt,decimalParaBinario(ins->reg2,6));
        strcpy(binario,opcode);
        strcat(binario,rs);
        strcat(binario,rt);
        strcat(binario,imediato);
    }else if(ins->tipo == 3){
        // inst IO
        if(ins->inst == INPUT){
            strcpy(opcode,"100010");
            strcat(binario,opcode);
            strcpy(rs,decimalParaBinario(ins->reg1,6));
            strcpy(rt,"000000");
            strcat(binario,rt);
            strcat(binario,rt);
            strcat(binario,rs);
            strcat(binario,"00000000");
        }else if(ins->inst == OUTPUT){
            strcpy(opcode,"100000");
            strcpy(rs,decimalParaBinario(ins->reg1,6));
            strcpy(rt,"000000");
            strcpy(imediato,"00000000000000");
            strcpy(binario,opcode);
            strcat(binario,rs);
            strcat(binario,rt);
            strcat(binario,imediato);
            
        }
        
    }
    
    return binario;
}

void geraBinario(NoInstrucao * assembly)
{
    FILE * f = fopen("saidas/binario.txt","w");

    while(assembly != NULL){
        
        char* binario = converteInst(assembly);
        fprintf(f,"%s\n",binario);
        assembly = assembly->prox;
    }
    printf("Arquivo binario gerado...\n");
}