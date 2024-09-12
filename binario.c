#include "binario.h"
#include "assembler.h"
#include "globals.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    char * rs = (char *)malloc(sizeof(char)*6);
    char * rt = (char *)malloc(sizeof(char)*6);
    char * rd = (char *)malloc(sizeof(char)*6);
    char * imediato = (char *)malloc(sizeof(char)*17);
    char * endereco = (char *)malloc(sizeof(char)*27);
    char * funct = (char *)malloc(sizeof(char)*7);
    char * opcode = (char *)malloc(sizeof(char)*7);
    char * binario = (char *)malloc(sizeof(char)*33);

    if(ins->tipo == 0){
        if(ins->inst == JUMP){
            strcpy(opcode,"01");
            strcpy(endereco,decimalParaBinario(pegaLinhaLabel(ins->endereco),26));
            strcpy(binario,opcode);
            strcat(binario,endereco);
        }else if(ins->inst == JAL){
            strcpy(opcode,"010000");
            strcpy(endereco,decimalParaBinario(pegaLinhaLabel(ins->endereco),26));
            strcpy(binario,opcode);
            strcat(binario,endereco);
        }
    }else if(ins->tipo == 1){
        strcpy(opcode,"000000");
        switch(ins->inst){
            case ADD:
                strcpy(funct,"000001");
                break;
            case SUBB:
                strcpy(funct,"000010");
                break;
            case MULT:
                strcpy(funct,"000011");
                break;
            case DIVV:
                strcpy(funct,"000100");
                break;
            case AND:   //set less than
                strcpy(funct,"000101");
                break;
            case OR:
                strcpy(funct,"000110");
                break;
            case SLT:
                strcpy(funct,"000111");
                break;
            case SGT:
                strcpy(funct,"001000");
                break;
            case SLET:
                strcpy(funct,"001001");
                break;
            case SGET: 
                strcpy(funct,"001010");
                break;
            case SET:
                strcpy(funct,"001011");
                break;
            case SDT:
                strcpy(funct,"001100");
                break;
            case SLL:
                strcpy(funct,"001101");
                break;
            case SRL:
                strcpy(funct,"001110");
                break;
            case MOD:
                strcpy(funct,"001111");
                break;
            case JR:
                strcpy(funct,"010000");
                break;
        }
        if(ins->inst == JR){
            strcpy(rs,decimalParaBinario(ins->reg1,5));
            strcpy(rt,"00000");
            strcpy(rd,"00000");
            strcpy(imediato,"00000");
            strcpy(binario,opcode);
            strcat(binario,rs);
            strcat(binario,rt);
            strcat(binario,rd);
            strcat(binario,imediato);
            strcat(binario,funct);
        }else{
            strcpy(rs,decimalParaBinario(ins->reg1,5));
            strcpy(rt,decimalParaBinario(ins->reg2,5));
            strcpy(rd,decimalParaBinario(ins->reg3,5));
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
            strcpy(opcode,"000001");
        }else if(ins->inst == SUBI){
            strcpy(opcode,"000010");
        }else if(ins->inst == MULTI){
            strcpy(opcode,"000011");
        }else if(ins->inst == DIVI){
            strcpy(opcode,"000100");
        }else if(ins->inst == ANDI){
            strcpy(opcode,"000101");
        }else if(ins->inst == ORI){
            strcpy(opcode,"000110");
        }else if(ins->inst == SLTI){
            strcpy(opcode,"000111");
        }else if(ins->inst == SGTI){
            strcpy(opcode,"001000");
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
            strcpy(opcode,"010000");
        }else if(ins->inst == BEQ){
            strcpy(opcode,"010001");
        }else if(ins->inst == BNE){
            strcpy(opcode,"010010");
        }else if(ins->inst == LW){
            strcpy(opcode,"010011");
        }else if(ins->inst == SW){
            strcpy(opcode,"010100");
        }else if(ins->inst == LUI){
            strcpy(opcode,"010101");
        }

        strcpy(rs,decimalParaBinario(ins->reg1,5));
        strcpy(rt,decimalParaBinario(ins->reg2,5));
        strcpy(imediato,decimalParaBinario(atoi(ins->imediato),16));
        strcpy(binario,opcode);
        strcat(binario,rs);
        strcat(binario,rt);
        strcat(binario,imediato);
    }else if(ins->tipo == 3){
        // inst IO
        if(ins->inst == INPUT){
            strcpy(opcode,"010110");
        }else if(ins->inst == OUTPUT){
            strcpy(opcode,"010111");
        }
        strcpy(rs,"00000");
        strcpy(rt,"00000");
        strcpy(imediato,"0000000000000000");
        strcpy(binario,opcode);
        strcat(binario,rs);
        strcat(binario,rt);
        strcat(binario,imediato);
    }
    
    return binario;
}

void geraBinario(NoInstrucao * assembly)
{
    FILE * f = fopen("binario.txt","w");

    while(assembly != NULL){
        
        char* binario = converteInst(assembly);
        fprintf(f,"%s\n",binario);
        assembly = assembly->prox;
    }
}