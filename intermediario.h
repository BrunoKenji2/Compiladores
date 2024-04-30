#ifndef _INTERMEDIARIO_H_
#define _INTERMEDIARIO_H_
#include "globals.h"

typedef enum{add,sub,divi,mul,fun,endF,call,param,iff,label,jump,assign,
slt,sgt,slet,sget,set,sdt,move,storeVet,loadVar,loadVet,storeVar,allocaMemVar,allocaMemVet,
empilha,desempilha} operacoes;

typedef enum{Vazio,Const,String} tipoArg;

typedef struct{
    tipoArg type;
    union{
        int val;
        char* nome; // struct dos argumentos/endereços
    }conteudo;
}arg;

typedef struct quad{
    operacoes op;
    arg arg1;   // parametros usados
    arg arg2;
    arg out;    // destino
    struct quad *prox;  // fila de instruções
}Quad;

void geraCodigo(TreeNode *raiz);
void geraCodigoExp(TreeNode *t);
void geraCodigoStmt(TreeNode *t);
void desempilhaReg();
void empilhaReg();
void liberaRegEndFun();
void insereQuad(operacoes op,arg a1,arg a2, arg destino);
void liberaRegs(char * registrador);
void gerarIntermediario(TreeNode *t);
void imprimeIntemediario();


#endif