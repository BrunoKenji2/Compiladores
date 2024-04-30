#include "intermediario.h"
#include "symtab.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arg aux;    // variavel auxiliar para guardar os argumentos atuais
int *regs;   // registradores disponiveis
Quad * quadPrimeiro = NULL; // ponteiro para o primeiro elemento da lista de quads
int quantLabel = 0;
int b = 0;
const char* OpString[] = {"add","sub","divi","mul","fun","endF","call","param","iff","label","jump","assign",
"slt","sgt","slet","sget","set","sdt","move","storeVet","loadVar","loadVet","storeVar","allocaMemVar","allocaMemVet",
"empilha","desempilha"};

void desempilhaReg(){   
    int i = 0;
    arg a1,a2;
    for(i = 31;i>=0;i--){   // desempilha a pilha de regs
        if(regs[i] == 1){
            a1.type = Const;
            a1.conteudo.val = i;
            a2.type = Vazio;
            insereQuad(desempilha,a1,a2,a2);
        }
    }
}

void empilhaReg(){
    int i;
    arg a1,a2;
    a2.type = Vazio;
    for(i = 0;i <32;i++){
        if(regs[i] == 1){
            a1.type = Const;
            a1.conteudo.val = i;
            insereQuad(empilha,a1,a2,a2);
        }
    }
}


operacoes verificaOp(TokenType tok){
    switch(tok)
	{
		case SOMA:
			return add;
			break;
		case SUB:
			return sub;
			break;
		case DIV:
			return divi;
			break;
		case MUL:
			return mul;
			break;
		case IGL:
			return set;	
			break;
		case DIF:
			return sdt;
			break;
		case MAIGL:
			return sget;
			break;
		case MEIGL:
			return slet;
			break;
		case MAI:
			return sgt;
			break;
		case MEN:
			return slt;
			break;
		default:
			break;
	}
}

void liberaRegEndFun(){
    for(int i = 0; i < 32; i++){
        if(regs[i] == 1){
            regs[i] == 0;
        }
    }
}

void insereQuad(operacoes op,arg a1,arg a2, arg destino){
    Quad * novo = (Quad*)malloc(sizeof(Quad));
    novo->op = op;
    novo->arg1 = a1;
    novo->arg2 = a2;
    novo->out = destino;
    novo->prox = NULL;
    if(quadPrimeiro == NULL){
        quadPrimeiro = novo;
    }else{
        Quad * temp = quadPrimeiro;
        while(temp->prox != NULL){
            temp = temp->prox;
        }
        temp->prox = novo;
    }
    //printf("a");
    if(op == add || op == mul || op == sub || op == divi || op == slt || 
		op == sgt || op == slet || op == sget || op == set || op == sdt || op == storeVet)
    {
        if(a1.type == String)
        {
            liberaRegs(a1.conteudo.nome);
        }
        if(a2.type == String)   // libera o registrador, caso ele faça parte da operação
        {
            liberaRegs(a2.conteudo.nome);
        }
    }else if(op == iff || op == loadVet || op == storeVar || op == move){
            if(a1.type == String){
                liberaRegs(a1.conteudo.nome);
            }
        }
    }

void liberaRegs(char * registrador){
    char r[3];
    int i;
    strcpy(r,registrador);   //formata o nome do registrador para pegar o numero
    r[0] = '0';
    i = atoi(r);
    regs[i] = 0;    // libera o registrador

}

void inicializaRegs(){
    for(int i = 0; i < 32; i++){
        regs[i] = 0;    // inicializa todos os registradores como disponiveis
    }
}

char * solicitaReg(){
    int i = 0;
    char * temp;
    while(regs[i] != 0 && i < 32){  //verifica se o registrador está disponivel
        i++;
    }
    if(i == 32){
        printf("ERRO: Registradores insuficientes\n");
        return NULL;
    }else{
        regs[i] = 1;    // marca o registrador como ocupado
        temp = (char*)malloc(4*sizeof(char)); // aloca espaço para o registrador
        sprintf(temp,"$t%d",i); // formata o nome do registrador
    }
    return temp;
}

// retorno o nome da label
char *cria_label(){
    
    char* lab =(char*)malloc((quantLabel%10 + 2)*sizeof(char)); //calculo para que a quantidade de digitos do char seja suficiente
    char* n = (char*)malloc((quantLabel%10 + 1)*sizeof(char));
    sprintf(n,"%d",quantLabel); // transforma quantLabel em string e armazena no n

        lab[0] = 'L'; // coloca o L no inicio do label
        strcat(lab,n); // concatena o L com o numero
        quantLabel++; // incrementa a quantidade de labels
        return lab;
    }

    void geraCodigoStmt(TreeNode *t){
        
        arg a1,a2,destino,a3;
        arg condicaoFalsa;  // vai ser o destino do jump para iff
        char * guardaLabel;
        char* regDestino;


        switch(t->kind.stmt){
            case IfK:
                geraCodigo(t->filho[0]);    // condição do iff
                a1 = aux;
                condicaoFalsa.type = String;
                guardaLabel = cria_label();
                condicaoFalsa.conteudo.nome = (char*)malloc(strlen(guardaLabel)*sizeof(char));
                strcpy(condicaoFalsa.conteudo.nome,guardaLabel);
                a2.type = Void;
                insereQuad(iff,a1,condicaoFalsa,a2); // insere o iff

                geraCodigo(t->filho[1]);    // bloco do if

                if(t->filho[2] != NULL){    // se tiver else
                    guardaLabel = cria_label();
                    arg endElse;
                    endElse.type = String;
                    endElse.conteudo.nome =(char*)malloc(strlen(guardaLabel)*sizeof(char));
                    strcpy(endElse.conteudo.nome,guardaLabel);
                    a1.type = Vazio;
                    a2.type = Vazio;
                    insereQuad(jump,endElse,a1,a2);
                    insereQuad(label,condicaoFalsa,a1,a2);
                    geraCodigo(t->filho[2]);
                    insereQuad(label,endElse,a1,a2);
                }else{
                    a1.type = Vazio;
                    a2.type = Vazio;
                    insereQuad(label,condicaoFalsa,a1,a2);  // se não tiver else é so criar um label para o iff
                }

            break;
            case AssignK :
                geraCodigo(t->filho[1]);    // x = atr, atr é o filho[1]
                arg conteudoAtribuicao;
                conteudoAtribuicao = aux;
                // verifica o que vai receber a atr
                if(t->filho[0]->kind.exp == VarK){
                    a1.type = String;
                    a1.conteudo.nome = (char*)malloc(strlen(t->filho[0]->attr.nome)*sizeof(char));
                    strcpy(a1.conteudo.nome,t->filho[0]->attr.nome);

                    a2.type = String;
                    a2.conteudo.nome = (char*)malloc(strlen(t->filho[0]->escopo)*sizeof(char));
                    strcpy(a2.conteudo.nome,t->filho[0]->escopo);

                    insereQuad(storeVar,conteudoAtribuicao,a1,a2);

                }

                if(t->filho[0]->kind.exp == VetIdK){
                    a1.type = String;   // pega o escopo do vetor
                    a1.conteudo.nome  = (char*)malloc(strlen(t->filho[0]->escopo)*sizeof(char));
                    strcpy(a1.conteudo.nome,t->filho[0]->escopo);

                    a2.type = String;   //  pega o nome do vetor
                    a2.conteudo.nome = (char*)malloc(strlen(t->filho[0]->attr.nome)*sizeof(char));
                    strcpy(a2.conteudo.nome,t->filho[0]->attr.nome);

                    regDestino = solicitaReg();
                    destino.type = String;
                    destino.conteudo.nome = (char*)malloc(strlen(regDestino)*sizeof(char));
                    strcpy(destino.conteudo.nome,regDestino);

                    insereQuad(loadVar,a1,a2,destino);   // carrega o end do vetor no destino
                    a1 = destino;

                    geraCodigo(t->filho[0]->filho[0]);
                    a2 = aux;   //  pega o valor do indice

                    regDestino = solicitaReg();
                    destino.type = String;
                    destino.conteudo.nome =(char*)malloc(strlen(regDestino)*sizeof(char));
                    strcpy(destino.conteudo.nome,regDestino);

                    insereQuad(add,a1,a2,destino);
                    a1 = destino; // posicao que sera efetuada o store
                    a2.type = Vazio;

                    insereQuad(storeVet,conteudoAtribuicao,a1,a2);
                    


                }
            break;
            case FuncaoK:   // declaração de funcao
                a1.type = String;
                a1.conteudo.nome = (char*)malloc(strlen(t->attr.nome)*sizeof(char));
                strcpy(a1.conteudo.nome,t->attr.nome);
                a2.type = Vazio;
                insereQuad(fun,a1,a2,a2);
                geraCodigo(t->filho[0]);    // parametros
                geraCodigo(t->filho[1]);    // corpo da função
                insereQuad(endF,a1,a2,a2);
                liberaRegEndFun();  // libera os registradores usados na função
            break;
            case VarK : //declaração de variavel
                a1.type = String;//escopo da var
                a1.conteudo.nome = (char*)malloc(strlen(t->escopo)*sizeof(char));
                strcpy(a1.conteudo.nome,t->escopo);

                a2.type = String;   // nome da var
                a2.conteudo.nome = (char*)malloc(strlen(t->attr.nome)*sizeof(char));
                strcpy(a2.conteudo.nome,t->attr.nome);

                insereQuad(allocaMemVar,a1,a2,a2);  // não usa reg pra alocar na memoria
            break;
            case VetK :     //aloca vetor
                a1.type = String;   // escopo do vetor
                a1.conteudo.nome = (char*)malloc(strlen(t->escopo)*sizeof(char));
                strcpy(a1.conteudo.nome,t->escopo);

                a2.type = String;   // nome do vetor
                a2.conteudo.nome = (char*)malloc(strlen(t->attr.nome)*sizeof(char));
                strcpy(a2.conteudo.nome,t->attr.nome);

                a3.type = Const;    // tamanho do vetor
                if(t->filho[0] != NULL){
                    a3.conteudo.val = t->filho[0]->attr.val;
                }else{
                    a3.conteudo.val = 0; // ERROR
                }
                insereQuad(allocaMemVet,a1,a2,a3);
            break;
            case WhileK :
                char * inicioW;
                char* fimW;
                inicioW = cria_label();
                a1.type = String;
                a1.conteudo.nome = (char*)malloc(strlen(inicioW)*sizeof(char));
                strcpy(a1.conteudo.nome,inicioW);

                a2.type = Vazio;
                insereQuad(label,a1,a2,a2);    // cria o label do while

                geraCodigo(t->filho[0]);    // condição do while
                a1 = aux;

                fimW = cria_label();
                condicaoFalsa.type = String;
                condicaoFalsa.conteudo.nome = (char*)malloc(strlen(fimW)*sizeof(char));
                strcpy(condicaoFalsa.conteudo.nome,fimW);

                a2.type = Vazio;
                insereQuad(iff,a1,condicaoFalsa,a2); // insere o iff
                geraCodigo(t->filho[1]);    // corpo do while
                
                a1.type = String;
                a1.conteudo.nome = (char*)malloc(strlen(inicioW)*sizeof(char));
                strcpy(a1.conteudo.nome,inicioW);
                a2.type = Vazio;
                insereQuad(jump,a1,a2,a2); // volta para o inicio do while
                insereQuad(label,condicaoFalsa,a2,a2); // cria o label do fim do while


            break;
            case ReturnK:
                if(t->filho[0] != NULL){    // caso retorne algo
                    geraCodigo(t->filho[0]);
                    a1 = aux;
                    char retorno[10] = "$rf"; // endereço de retorno
                    a2.conteudo.nome = (char*)malloc(10*sizeof(char));
                    a2.type = String;
                    strcpy(a2.conteudo.nome,retorno);
                    destino.type = Vazio;
                    insereQuad(move,a1,a2,destino);
                }
            break;
            case CallK:
                int nParam = 0;
                if(t->filho[0] != NULL){
                    TreeNode* t_aux;
                    t_aux = t->filho[0];
                    while(t_aux != NULL){
                        nParam++;
                        switch (t_aux->nodeKind)
                        {
                        case StmtK:
                            geraCodigoStmt(t_aux);    
                        break;
                        case ExpK:
                            geraCodigoExp(t_aux);
                        break;
                        }
                        a1 = aux;
                        a2.type = Vazio;
                        insereQuad(param,a1,a2,a2); // percorre a lista de parametros
                        t_aux = t_aux->irmao;
                    }
                }

                a1.type = String;
                a1.conteudo.nome = (char*)malloc(strlen(t->attr.nome)*sizeof(char));
                strcpy(a1.conteudo.nome,t->attr.nome);  // nome da func
                a2.type = Const; // n de parametros
                a2.conteudo.val = nParam;
                destino.type = Vazio;
                
                char verificaOutput[20];
    			char verificaInput[20];
    			strcpy(verificaOutput,"output");
    			strcpy(verificaInput,"input");

                if(strcmp(verificaOutput,a1.conteudo.nome)!=0 && strcmp(verificaInput,a1.conteudo.nome)!=0)
    				empilhaReg();   

    			insereQuad(call,a1,a2,destino);
    			
    			if(strcmp(verificaOutput,a1.conteudo.nome)!=0 && strcmp(verificaInput,a1.conteudo.nome)!=0)
    				desempilhaReg();
    			
    			aux.type = String;
    			char endRetorno[10] = "$rf";
    			aux.conteudo.nome = (char*) malloc(10*sizeof(char));
    			strcpy(aux.conteudo.nome,endRetorno);

            break;
        }
    }

    void geraCodigoExp(TreeNode *t){
        arg a1,a2,destino;  // argumentos de referencia
        char* regDestino;
        if(t == NULL){
            return;
        }
        switch(t->kind.exp){
            case OpK:
                geraCodigo(t->filho[0]);
                a1 = aux;
                geraCodigo(t->filho[1]);    // coloca os valores dentro dos registradores antes de realizar ass operações
                a2 = aux;
                regDestino = solicitaReg();
                if(regDestino != NULL){
                    destino.conteudo.nome = (char*)malloc(strlen(regDestino)*sizeof(char));
                    strcpy(destino.conteudo.nome,regDestino);
                }
                insereQuad(verificaOp(t->attr.op),a1,a2,destino);
                aux = destino;
            break;
        case ConstK:
            aux.type = Const;   // o no const so vai passar o valor para o arg
            aux.conteudo.val = t->attr.val;

            break;
        case IdK:
            /*
            aux.type = String;
            aux.conteudo.nome = copyString(t->attr.nome);
            */
            break;
        case VarIdK:
            // carregar a variavel no registrador, precisa mostrar o escopo (interrogação)
            a1.type = String;// escopo da var a ser carregada
            a2.type = String;// nome da var
            a1.conteudo.nome =(char*)malloc(strlen(t->escopo)*sizeof(char));
            strcpy(a1.conteudo.nome,t->escopo);
            a2.conteudo.nome = (char*)malloc(strlen(t->attr.nome)*sizeof(char));
            strcpy(a2.conteudo.nome,t->attr.nome);

            regDestino = solicitaReg();
            destino.type = String;
            destino.conteudo.nome  = (char*)malloc(strlen(regDestino)*sizeof(char));
            strcpy(destino.conteudo.nome,regDestino);

            insereQuad(loadVar,a1,a2,destino);
            aux = destino;  // salva o registrador onde a variavel foi carregada
            break;
        case VetIdK:
            
            // carregar o vetor no registrador
            
            a1.type = String;   // escopo do vetor
            a2.type = String;   // nome do vetor
            a1.conteudo.nome = (char*)malloc(strlen(t->escopo)*sizeof(char));
            strcpy(a1.conteudo.nome,t->escopo);
            a2.conteudo.nome = (char*)malloc(strlen(t->attr.nome)*sizeof(char));
            strcpy(a2.conteudo.nome,t->attr.nome);

            regDestino = solicitaReg();
            destino.type = String;
            destino.conteudo.nome = (char*)malloc(strlen(regDestino)*sizeof(char));
            strcpy(destino.conteudo.nome,regDestino);   //nome do registrador de destino salvo
            
            insereQuad(loadVar,a1,a2,destino);  //carrega a var com o endereço do vet

            a1 = destino; // a1 vai carregar o endereço base no loadVet
            geraCodigo(t->filho[0]); // tamanho do vetor
            a2 = aux; // recebe o tamanho do vetor

            regDestino = solicitaReg();
            destino.type = String;
            destino.conteudo.nome =(char*)malloc(strlen(regDestino)*sizeof(char));
            strcpy(destino.conteudo.nome,regDestino);
            insereQuad(add,a1,a2,destino);

            a1 = destino;   // a1 recebe o deslocamento
            regDestino = solicitaReg();
            a2.type = String;   // a2 recebe o endereço do vetor
            a2.conteudo.nome = (char*)malloc(strlen(regDestino)*sizeof(char));
            strcpy(a2.conteudo.nome,regDestino);

            destino.type = Vazio;
            insereQuad(loadVet,a1,a2,destino);
            aux = a2;
            

            
            insereQuad(loadVet,a1,a2,destino);


            break;
        case TypeK:
                if(t->filho[0]->nodeKind == ExpK){
                    printf("%d \n",t->filho[0]->kind.exp);
                }
                printf("%d \n",t->filho[0]->kind.stmt);
                geraCodigo(t->filho[0]);    // o filho do tipo é o que vai ter o valor
            break;
        default:
            break;
    }
}

void geraCodigo(TreeNode* raiz){
    if(raiz == NULL){
        //return;   
    }else{
        switch(raiz->nodeKind){
            case StmtK:
                printf("S %i \n",raiz->kind.stmt);
                geraCodigoStmt(raiz);
                break;
            case ExpK:
                printf("E %i \n",raiz->kind.exp);
                geraCodigoExp(raiz);
                break;
            default:
                break;
        }
        geraCodigo(raiz->irmao);
    }
            // percorre os irmaos e vai gerando o codigo conforme os tipos dos nos
}

void imprimeIntemediario()
{
	FILE *arq = fopen("intermediario.txt","w");
	if(quadPrimeiro == NULL)
		return;
	Quad *q = quadPrimeiro;
	do
	{
		fprintf(arq,"%s,",OpString[q->op]);
		switch(q->arg1.type)
		{
			case Vazio:
				fprintf(arq, "___,");
				break;
			case Const:
				fprintf(arq, "%d,", q->arg1.conteudo.val);
				break;
			case String:
				fprintf(arq, "%s,", q->arg1.conteudo.nome);
			default:
				break;
		}
		switch(q->arg2.type)
		{
			case Vazio:
				fprintf(arq, "___,");
				break;
			case Const:
				fprintf(arq, "%d,", q->arg2.conteudo.val);
				break;
			case String:
				fprintf(arq, "%s,", q->arg2.conteudo.nome);
			default:
				break;
		}
		switch(q->out.type)
		{
			case Vazio:
				fprintf(arq, "___\n");
				break;
			case Const:
				fprintf(arq, "%d\n", q->out.conteudo.val);
				break;
			case String:
				fprintf(arq, "%s\n", q->out.conteudo.nome);
			default:
				break;
		}
		q = q->prox;
	}
	while(q != NULL);
	printf("Codigo intermediario gerado...\n");
}

void gerarIntermediario(TreeNode *t)
{
	int i = 0;
	regs = malloc(32*sizeof(int));
	for(i=0;i<32;i++)
	{
		regs[i] = 0;
	}
	geraCodigo(t);
	imprimeIntemediario();
	
}