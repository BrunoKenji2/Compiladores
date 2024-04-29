#include "globals.h"
#include "semantic.h"
#include "stdio.h"
#include "symtab.h"
#include "util.h"

FILE* semanticFile;


static void insertNode(TreeNode * t)
{
	int tipoFuncao = 0;
    switch (t->nodeKind)
    {
    case StmtK:
        switch (t->kind.stmt)
        {
        case VarK://se o nó for declaração de variavel

            if(!lookup(t->attr.nome,t->escopo) && !lookup(t->attr.nome,"global") )//não foi encontrada na tabela de simbolos
            {
                if(t->type == Void)
                {
                    printf("ERRO SEMÂNTICO: Variáveis não podem ser do tipo Void linha: %d\n",t->lineno);
                    break;
                }
                insertTab(t->attr.nome, t->escopo, t->type, 1, t->lineno);
            }
            else //já está na tabela de simbolos e é uma redeclaração
            {
                printf("ERRO SEMÂNTICO: Redeclaração da variavel '%s' linha: %d\n",t->attr.nome,t->lineno);
            }

            break;

        case VetK://se o no for declaração de vetor
            if(!lookup(t->attr.nome,t->escopo) && !lookup(t->attr.nome,"global"))
            {
                if(t->type == Void)
                {
                    printf("ERRO SEMÂNTICO: Variáveis não podem ser do tipo Void linha: %d\n",t->lineno);
                    break;
                }
                insertTab(t->attr.nome, t->escopo, t->type, 1, t->lineno);
            }
            else 
                printf("ERRO SEMÂNTICO: Redeclaração do vetor '%s' linha: %d\n",t->attr.nome,t->lineno);
            break;
        case FuncaoK:
            if (!lookup(t->attr.nome,"global"))
            {
                insertTab(t->attr.nome, "global", t->type, 0, t->lineno);
            }
            else
                printf("ERRO SEMÂNTICO: Redeclaração da função '%s' linha: %d\n",t->attr.nome,t->lineno);
            break;
        case CallK: //erro 5
            if (!lookup(t->attr.nome,"global") && strcmp(t->attr.nome,"input") != 0 && strcmp(t->attr.nome,"output") != 0)//chamada de funcao não encontrada
                printf("ERRO SEMÂNTICO: Chamada da função '%s' não declarada linha: %d\n",t->attr.nome,t->lineno);
            else if (strcmp(t->attr.nome,"input") != 0 && strcmp(t->attr.nome,"output") != 0)
                insertTab(t->attr.nome, "global", 0, 0, t->lineno);
            break;
        case AssignK:
			if(t->filho[1]->kind.stmt == CallK && t->filho[1]->nodeKind == 0)//está atribuindo o retorno de uma função à varivel
			{
				tipoFuncao = pegaTipoFunc(t->filho[1]->attr.nome, "global");
				if(tipoFuncao != -1)
				{
					if(t->filho[0]->type != tipoFuncao)
            		{
                		printf("ERRO SEMÂNTICO: Atribuição de tipo invalido para a variavel %s na linha: %d\n",t->filho[0]->attr.nome,t->filho[0]->lineno);
            		}
				}
			}

			else if(t->filho[0]->type != t->filho[1]->type)
            {
                printf("ERRO SEMÂNTICO: Atribuição de tipo invalido para a variavel %s na linha: %d\n",t->filho[0]->attr.nome,t->filho[0]->lineno);
            }
        default:
            break;
        }
        break;
    case ExpK:

        switch (t->kind.exp)
        {
        case VarIdK:
            if(lookup(t->attr.nome,"global"))
            {
                insertTab(t->attr.nome,"global",0,0,t->lineno);
                t->escopo = copyString("global");//se encontrou o VarIdK  no escopo global altera seu escopo para global
            }
            else if (lookup(t->attr.nome,t->escopo)) // erro 1
                insertTab(t->attr.nome,t->escopo,0,0,t->lineno);
            else
                printf("ERRO SEMÂNTICO: Variavel '%s' não declarada na linha: %d\n", t->attr.nome,t->lineno);
            break;
        case VetIdK:
            if (lookup(t->attr.nome,t->escopo))
                insertTab(t->attr.nome,t->escopo,0,0,t->lineno);
            else if (lookup(t->attr.nome,"global")) // erro 1
            {
                insertTab(t->attr.nome,"global",0,0,t->lineno);
                t->escopo = copyString("global");//se encontrou o VetIdK  no escopo global altera seu escopo para global
            }
            else
                printf("ERRO SEMÂNTICO: Vetor '%s' não declarado na linha: %d\n", t->attr.nome,t->lineno);
            break;
        default:

            break;
        }
        break;
    default:
        break;
    }
}

static void verifica_main()
{
    if (!lookup("main","global")) // erro 1
        printf("ERRO SEMÂNTICO: Função main() não declarada\n");
}


static void traverse(TreeNode *t)
{
    if(t!=NULL)
    {
        insertNode(t);
        int i;
        for(i=0; i<MAXCHILDREN; i++)
            traverse(t->filho[i]);
        traverse(t->irmao);
    }
}

void buildSymtab(TreeNode *syntaxTree)
{
    traverse(syntaxTree);
    verifica_main();
    semanticFile = fopen("tabelaSimbolos.txt","w");
    if(semanticFile!=NULL)
    {
        printSymTab(semanticFile);
    }
}
