#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <stdio.h>
#include "globals.h"
#include "intermediario.h"

typedef enum {
    ADD,
    ADDI,
    SUBB,
    SUBI,
    MULT,
    MULTI,
    DIVV,
    DIVI,
    AND,
    ANDI,
    OR,
    ORI,
    SLT,
    SGT,
    SLET,
    SGET,
    SET,
    SDT,
    SGTI,
    SLETI,
    SGETI,
    SETI,
    SDTI,
    SLL,
    SRL,
    SLTI,
    MOD,
    JR,
    MODI,
    BLTZ,
    BGTZ,
    BEQZ,
    BEQ,
    BNE,
    LW,
    SW,
    JUMP,
    JAL,
    HALT,
    NOP,
    INPUT,
    OUTPUT,
    LUI
}instrucao;

typedef enum {
    $zero,$t0,$t1, $t2, $t3, $t4, $t5, $t6, $t7, $t8, $t9, 
    $t10, $t11, $t12, $t13, $t14, $t15, $t16, $t17, $t18, 
    $t19, $t20, $t21, $t22, $t23, $t24, $t25, $aux, $rf, 
    $fp, $sp, $ra
}registradores;

typedef struct noInstrucao{
    instrucao inst;
    registradores reg1; //rs
    registradores reg2; //rt
    registradores reg3; //rd
    char * imediato;
    char * endereco;
    int tipo;
    struct noInstrucao *prox;
} NoInstrucao;

typedef struct NoLabel{
    int linha;
    char* nome;
    struct NoLabel * prox; 
}noLabel;

/*
typedef struct instrucao{
    char* nome;
    char* op1;
    char* op2;
    char* op3;
} Instrucao;
*/

void geraAssembly(Quad * q);    //  faz o assembly a partir das quadruplas
void insereInstJ(instrucao inst, char * label); // insere instruções de jump
void insereInstR(instrucao inst, registradores reg1, registradores reg2, registradores reg3);
void insereInstI(instrucao isnt, registradores reg1, registradores reg2, char* imediato);
void insereInstIO(instrucao inst, registradores reg);
registradores pegaRegistrador(char * reg);
void imprimeInstrucoes();
void criaLabel(char* label);
int pegaLinhaLabel(char * label);

#endif