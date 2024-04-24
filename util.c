#include "globals.h"
#include "util.h"
static int indentno = 0;
#define INDENT indentno+=2
#define UNINDENT indentno-=2

FILE* listing;

// cria novo no do tipo stmt
TreeNode* newStmtNode(StmtKind kind){
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    int i;
    if(t == NULL){
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    }else{
        for(i = 0; i < MAXCHILDREN; i++){
            t->filho[i] = NULL;
        }
        t->irmao = NULL;
        t->nodeKind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}

TreeNode* newExpNode(ExpKind kind){
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    int i;
    if(t == NULL){
        fprintf(listing,"Out of memory error at line %d\n", lineno);

    }else{
        for(i = 0; i < MAXCHILDREN; i++){
            t->filho[i] = NULL;
        }
        t->irmao = NULL;
        t->nodeKind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        t->type = Void;
    }
    return t;

}

void insereEscopo(TreeNode* tree, char* escopo){

    int i;

    while(tree != NULL){
        tree->escopo = copyString(escopo);
        for(i = 0; i < MAXCHILDREN; i++){
            if(tree->filho[i] != NULL){
                insereEscopo(tree->filho[i],escopo);    // bota escopo em geral
            }
        }
        tree = tree->irmao; //
    }


}

char * copyString(char* s){
    int n;
    char* t;
    if(s == NULL){
        return NULL;
    }
    n = strlen(s) + 1;
    t =(char*)malloc(n*sizeof(char));   // talvez de erro
    if(t != NULL){
        strcpy(t,s);
    }
    return t;
}


char *printToken(TokenType token, const char* tokenString)
{
	char *tokenS;
	tokenS = malloc(100);
	switch(token)
	{
		case IF:
		case ELSE:
		case INT:
		case VOID:
		case WHILE:
		case RETURN:
			strcpy(tokenS,tokenString);
			break;
		case NUM:
			strcpy(tokenS,"NUM");
			break;
		case SOMA:
			strcpy(tokenS,"+");
			break;
		case SUB:
			strcpy(tokenS,"-");
			break;
		case DIV:
			strcpy(tokenS,"/");
			break;
		case MUL:
			strcpy(tokenS,"*");
			break;
		case APR:
			strcpy(tokenS,"(");
			break;
		case FPR:
			strcpy(tokenS,")");
			break;
		case ID:
			strcpy(tokenS,tokenString);
			break;
		case ACOL:
			strcpy(tokenS,"[");
			break;
		case FCOL:
			strcpy(tokenS,"]");
			break;
		case ACH:
			strcpy(tokenS,"{");
			break;
		case FCH:
			strcpy(tokenS,"}");
			break;
		case ATRIB:
			strcpy(tokenS,"=");
			break;
		case IGL:
			strcpy(tokenS,"==");
			break;
		case DIF:
			strcpy(tokenS,"!=");
			break;
		case MAIGL:
			strcpy(tokenS,">=");
			break;
		case MEIGL:
			strcpy(tokenS,"<=");
			break;
		case MAI:
			strcpy(tokenS,">");
			break;
		case MEN:
			strcpy(tokenS,"<");
			break;
		case VIRG:
			strcpy(tokenS,",");
			break;
		case PV:
			strcpy(tokenS,";");
			break;
	}
	return tokenS;
}

static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

// tem partes faltando aqui



