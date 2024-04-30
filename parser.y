%{
#define YYPARSER
#define YYDEBUG 1
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parser.h"
#include "util.h"

static int yylex();
void yyerror(char* msg);

TreeNode* parse(void);

#define YYSTYPE TreeNode*
static TreeNode* raiz;  // raiza da árvore sintatica




%}

%start programa
%token VOID INT IF WHILE ELSE RETURN
%left SOMA SUB MUL DIV
%token APR FPR NUM ESP ID ACOL FCOL ACH FCH ATRIB IGL DIF MAIGL MEIGL MAI MEN VIRG PV NL ERRO FIM


%%

programa : declaracao_lista { raiz = $1;};

declaracao_lista : declaracao_lista declaracao 
{
    YYSTYPE t = $1;
    if(t != NULL){
        while(t->irmao != NULL){    //gera n declarações, que serão todos irmão, o primeiro no é quando declaração_lista deriva em declaração
            t = t->irmao;
        }

        t->irmao  = $2;
        $$ = $1;
    } // pode dar erro
}
    | declaracao {
        $$ = $1;    //primeira declaração, que será a raiz
    };

declaracao : var_declaracao{
    $$ = $1;
}
    |   fun_declaracao{ // so passa a o no pra cima
        $$ = $1;
    };

var_declaracao :tipo_especificador id PV{   // como tem nos folha, aloca-se nos
    $$ = $1;
    $$->filho[0] = newStmtNode(VarK);
    $$->filho[0]->type = $$->type;
    $$->filho[0]->attr.nome = copyString($2->attr.nome);    //para declaração de variaveis globais
    $$->filho[0]->lineno = $2->lineno;
    $$->filho[0]->escopo = copyString("global");
}
    |   tipo_especificador id ACOL vet_num FCOL PV{
        $$ = $1;
        $$->filho[0] = newStmtNode(VetK);
        $$->filho[0]->type = $$->type;
        $$->filho[0]->attr.nome = copyString($2->attr.nome); //mesma coisa so que com vetores
        $$->filho[0]->lineno = $2->lineno;
        $$->filho[0]->escopo = copyString("global");
        $$->filho[0]->filho[0] = $4;    // o filho do vetor é o numero de elementos
};

vet_num: NUM{
    $$ = newExpNode(ConstK);
    $$->attr.val = atoi(tokenString);   //cria o no folha para nums
    $$->type = Integer; 
};

fun_declaracao: tipo_especificador id APR params FPR composto_decl{
    $$ = $1;
    $$->filho[0] = newStmtNode(FuncaoK);
    $$->filho[0]->type = $$->type;
    $$->filho[0]->filho[0] = $4;
    $$->filho[0]->filho[1] = $6;
    $$->filho[0]->attr.nome = copyString($2->attr.nome);
    $$->filho[0]->lineno = $2->lineno;
    $$->filho[0]->escopo = copyString("global");    // note que todo escopo é global até estar dentro de uma função
    $$->filho[0]->filho[1] = $6;    //  função tem 2 filhos parametros e o que ela faz
    insereEscopo($$->filho[0]->filho[0],$2->attr.nome); // o escopo ddas variaveis a baixo da declaração de função são o nome da propria
    insereEscopo($$->filho[0]->filho[1],$2->attr.nome);
};

tipo_especificador: INT {
    $$ = newExpNode(TypeK);
    $$->type = Integer;
}
    |   VOID {
        $$ = newExpNode(TypeK);
        $$->type = Void;
    };

params: param_lista{
    $$ = $1;
}
    |   VOID {$$ = NULL;}; /*{
        $$ = newExpNode(ConstK); // o parametro é void, então cria-se um no do tipo void
        $$->type = Void;    //pode dar erro
    };*/

param_lista: param_lista VIRG param {

                
                YYSTYPE t = $1;
                if(t != NULL){      // verifica se a lista de parametros não é vazia
                    while(t->irmao != NULL){
                        t = t->irmao;   //vai adicionando os parametros ao final da lista de irmaos
                    }
                    t->irmao = $3;  //adiciona o parametro
                    $$ = $1;
                }   //pode dar erro
}
    |   param {
        $$ = $1;     //primeiro parametro a ser adicionado
    };

param : tipo_especificador id{
    $$ = $1;
    $$->filho[0] = newStmtNode(VarK);   // o filho do tipo da variavel é a variavel
    $$->filho[0]->type = $$->type;
    $$->filho[0]->attr.nome = copyString($2->attr.nome);
    $$->filho[0]->lineno = $2->lineno;
}
    |  tipo_especificador id ACOL FCOL{
        $$ = $1;
        $$->filho[0] = newStmtNode(VetK);   //mesma coisa so que para listas
        $$->filho[0]->type = $$->type;
        $$->filho[0]->attr.nome = copyString($2->attr.nome);
        $$->filho[0]->lineno = $2->lineno;
};

composto_decl : ACH local_declaracoes statement_lista FCH{
        YYSTYPE t = $2;
        if(t != NULL){
            while(t->irmao != NULL){
                t = t->irmao;
            }
            t->irmao = $3;//o primeiro no de statement vai ficar no final da fila de irmaos
            $$ = $2;
        }else{
            $$ = $3;    //  caso não tenha declarações locais
        }
};

local_declaracoes : local_declaracoes var_declaracao{
    YYSTYPE t = $1;
    if(t != NULL){
        while(t->irmao != NULL){
            t = t->irmao;
        }
        t->irmao = $2;
        $$ = $1;
    }else{
        $$ = $2;
    }
}
    | %empty{
        $$ = NULL;
    };

statement_lista : statement_lista statement{

    YYSTYPE t = $1;
    if(t != NULL){
        while(t->irmao != NULL){
            t = t->irmao;
        }
        t->irmao = $2;
    }else{
        $$ = $2;
    }

} | %empty{$$ = NULL;};

statement : expressao_decl{
    $$ = $1;
    }
    |   composto_decl{
        $$ = $1;
    }
    |   selecao_decl{
        $$ = $1;
    }
    |   iteracao_decl{
        $$ = $1;
    }
    |   retorno_decl{
        $$ = $1;
    };

expressao_decl : expressao PV{

    $$ = $1;
    }
    |  PV{
        $$ = NULL;
    };

selecao_decl:IF APR expressao FPR statement{
    $$ = newStmtNode(IfK);
    $$->filho[0] = $3;
    $$->filho[1] = $5; 
} | IF APR expressao FPR statement ELSE statement{
    $$ = newStmtNode(IfK);
    $$->filho[0] = $3;
    $$->filho[1] = $5;
    $$->filho[2] = $7;  // quando tem o else tem 3 filhos
};

iteracao_decl: WHILE APR expressao FPR statement{
    $$ = newStmtNode(WhileK);
    $$->filho[0] = $3;
    $$->filho[1] = $5;
};

retorno_decl: RETURN PV{

        $$ = newStmtNode(ReturnK);
} | RETURN expressao PV{
    $$ = newStmtNode(ReturnK);
    $$->filho[0] = $2;
};

expressao: var ATRIB expressao{
    $$ = newStmtNode(AssignK);
    $$->filho[0] = $1;
    $$->filho[1] = $3;
}
    |   simples_expressao{
        $$ = $1;
    };

var: id{
    $$ = $1;
    $$->type = Integer;
    $$->kind.exp = VarIdK;
}
    | id ACOL expressao FCOL{
        $$ = $1;
        $$->filho[0] = $3;
        $$->kind.exp = VetIdK;
        $$->type = Integer;
    };

simples_expressao : soma_expressao relacional soma_expressao{
    $$ = $2;
    $$->filho[0] = $1;
    $$->filho[1] = $3;
}

    | soma_expressao{
        $$ = $1;
    };

relacional : MEIGL{
                $$ = newExpNode(OpK);
                $$->attr.op = MEIGL;
            } 
            | MEN{
                $$ = newExpNode(OpK);
                $$->attr.op = MEN;
            } 
            | MAI{
                $$ = newExpNode(OpK);
                $$->attr.op = MAI;
            } 
            | MAIGL{
                $$ = newExpNode(OpK);
                $$->attr.op = MAIGL;
            } 
            | IGL{
                $$ = newExpNode(OpK);
                $$->attr.op = IGL;
            } 
            | DIF{
                $$ = newExpNode(OpK);
                $$->attr.op = DIF;
            };

soma_expressao : soma_expressao soma termo{
    $$ = $2;
    $$->filho[0] = $1;
    $$->filho[1] = $3;
}
    |   termo{
        $$ = $1;
    };

soma : SOMA{
    $$ = newExpNode(OpK);
    $$->attr.op = SOMA;
    $$->type = Integer;
    } 
    | SUB{
    $$ = newExpNode(OpK);
    $$->attr.op = SUB;
    $$->type = Integer;
    };

termo: termo mult fator{

    $$ = $2;
    $$->filho[0] = $1;
    $$->filho[1] = $3;

    } 
    | fator{

     $$ = $1;

    };

mult : MUL{
    $$ = newExpNode(OpK);
    $$->type = Integer;
    $$->attr.op = MUL;
    }
    | DIV{
    $$ = newExpNode(OpK);
    $$->type = Integer;
    $$->attr.op = DIV;    
    };

fator : APR expressao FPR {$$ = $2;}| var {$$ = $1;} | ativacao {$$ = $1;}
    |NUM {
        $$ = newExpNode(ConstK);
        $$->attr.val = atoi(tokenString);
        $$->type = Integer;
    };

ativacao : id APR args FPR{

    $$ = newStmtNode(CallK);
    $$->filho[0] = $3;
    $$->attr.nome  = copyString($1->attr.nome);
    $$->lineno = $1->lineno;
}

    | id APR FPR{
        $$ = newStmtNode(CallK);
        $$->attr.nome = copyString($1->attr.nome);
        $$->lineno = $1->lineno;
    };

args : arg_lista {$$ = $1;};

arg_lista : arg_lista VIRG expressao{
        YYSTYPE t = $1;
        if(t != NULL){
            while(t->irmao != NULL){
                t = t->irmao;
            }
            t->irmao = $3;
        }else{
            $$ = $3;
        }
} 
    | expressao{
        $$ = $1;
    };

id : ID{
    $$ = newExpNode(IdK);
    $$->attr.nome = copyString(tokenString);
    $$->lineno = lineno;
}

%%


void yyerror(char *msg)
{
	if(yychar == ERRO)
	{
		exit(0);
	}
	else
	{
		char *t = printToken(yychar,tokenString);
	   	printf("ERRO SINTÁTICO: %s Linha %d\n",t,lineno);
	}
}

static int yylex(void)
{
	TokenType t = getToken();
	return t;
}

TreeNode *parse(void)
{
	yyparse();
    return raiz;
}
