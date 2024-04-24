#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER
#include "parser.tab.h"
#endif

typedef int TokenType;  // tokens

extern FILE *source_file;   // arquivo de entrada
extern int lineno;  // contador linhas

#define MAXCHILDREN 3

// struct da arvore


typedef enum {StmtK, ExpK} NodeKind;    // no tem 2 tipos
typedef enum {IfK,WhileK,AssignK,ReturnK,CallK,Vark,VetK,FuncaoK} StmtKind; //tipos de declaração
typedef enum {OpK,ConstK,Idk,TypeK,VarIdK,VetIdK} ExpKind; //tipos de expressão
typedef enum {Void, Integer,Bool}ExpType; // tipos de dados da expressão 

typedef struct treeNode{
    struct treeNode* filho[MAXCHILDREN]; //supondo que o max e 3
    struct treeNode* irmao;
    int lineno;
    char* escopo;
    NodeKind nodeKind;
    union{StmtKind stmt; ExpKind exp} kind;
    union{TokenType op; int val; char* nome} attr;
    ExpType type;
}TreeNode;


#endif