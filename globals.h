#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern FILE *source_file;
extern int lineno;
/*
typedef enum {StmtK, ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,Idk} ExpKind;
typedef enum {Void, Integer,Bool}ExpType;

typedef struct treeNode{
    struct treeNode* filho[3]; //supondo que o max e 3
    struct treeNode* irmao;
    int linha;
    NodeKind nodekind;
    union{StmtKind stmt; ExpKind exp} kind;
    union{int token; int val; char* nome} attr;
    ExpType type;
}nodeArv;
*/