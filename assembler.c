#include "assembler.h"
#include <string.h>
#include <ctype.h>
#include "pilha.h"
#include <stdlib.h>

/*

problema de analise sintatica, quando há um * e uma / dentro do comentario, o compilador não reconhece o comentario

*/


/*
    INSTRUÇÕES QUE FALTAM
    -call
    -move
    -store vet
*/
/*
    inst tipo 0 = jump
*/

NoInstrucao * primeiraInstrucao = NULL;
NoInstrucao * ultimaInstrucao = NULL;
int numLinhas = 0;
Pilha * pilhaParam = NULL;
noLabel * primeiraLabel = NULL;
noLabel * ultimaLabel = NULL;

char * ListaInstStr[43] = {"add","addi","sub","subi","mult","multi","div","divi","and","andi","or","ori",
"slt","sgt","slet","sget","set","sdt","sgti","sleti","sgeti","seti","sdti","sll","srl","slti",
"mod","jr","modi","bltz","bgtz","beqz","beq","bne","lw","sw","jump","jal","halt","nop","input","output","lui"};

char * ListaRegStr[32] = {"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","r16","r17","r18","r19","r20","r21","r22","r23","r24","r25","r26","r27","r28","r29","r30","r31"};
void insereInstJ(instrucao inst, char * label){
    if(primeiraInstrucao == NULL){
        primeiraInstrucao = (NoInstrucao*)malloc(sizeof(NoInstrucao));
        primeiraInstrucao->inst = inst;
        primeiraInstrucao->endereco = (char *)malloc(sizeof(char)*strlen(label));
        strcpy(primeiraInstrucao->endereco, label);
        primeiraInstrucao->prox = NULL;
        primeiraInstrucao->tipo = 0;
        ultimaInstrucao = primeiraInstrucao;
    }else{
        NoInstrucao * novo = (NoInstrucao*)malloc(sizeof(NoInstrucao));
        novo->inst = inst;
        novo->endereco = (char *)malloc(sizeof(char)*strlen(label));
        strcpy(novo->endereco, label);
        novo->prox = NULL;
        novo->tipo = 0;
        ultimaInstrucao->prox = novo;
        ultimaInstrucao = novo;
    }
    numLinhas++;
}

void insereInstR(instrucao inst,registradores reg1,registradores reg2,registradores reg3){
    // primeira instrucao é sempre um jump para o main
        NoInstrucao * novo = (NoInstrucao*)malloc(sizeof(NoInstrucao));
        novo->inst = inst;
        novo->reg1 = reg1;
        novo->reg2 = reg2;
        novo->reg3 = reg3;
        novo->prox = NULL;
        novo->tipo = 1;
        ultimaInstrucao->prox = novo;
        ultimaInstrucao = novo;
    
    numLinhas++;
}

void insereInstI(instrucao inst,registradores reg1,registradores reg2,char* imediato){
    // primeira instrucao é sempre um jump para o main
        NoInstrucao * novo = (NoInstrucao*)malloc(sizeof(NoInstrucao));
        novo->inst = inst;
        novo->reg1 = reg1;
        novo->reg2 = reg2;
        novo->imediato = (char *)malloc(sizeof(char)*strlen(imediato));
        strcpy(novo->imediato, imediato);
        novo->prox = NULL;
        novo->tipo = 2;
        ultimaInstrucao->prox = novo;
        ultimaInstrucao = novo;
    
    numLinhas++;
}

void insereIsntIO(instrucao inst,registradores reg){

    if(primeiraInstrucao == NULL){
        primeiraInstrucao =(NoInstrucao*)malloc(sizeof(NoInstrucao));
        primeiraInstrucao->inst = inst;
        primeiraInstrucao->reg1 = reg;
        primeiraInstrucao->prox = NULL;
        ultimaInstrucao = primeiraInstrucao;
        primeiraInstrucao->tipo = 3;

    }else{
        NoInstrucao * novo = (NoInstrucao*)malloc(sizeof(NoInstrucao));
        novo->inst = inst;
        novo->reg1 = reg;
        novo->prox = NULL;
        novo->tipo = 3;
        ultimaInstrucao->prox = novo;
        ultimaInstrucao = novo;
    }

    numLinhas++;
}

registradores pegaRegistrador(char * reg){
    //char teste[4] = "$t0";  // falta arrumar, não sei porque funciona, mas sem isso o strcmp nao roda
    if(strcmp(reg,"$zero") == 0){
        return $zero;
    }else if(strcmp(reg,"$t0") == 0){
        return $t0;
    }else if(strcmp(reg,"$t1") == 0){
        return $t1;
    }else if(strcmp(reg,"$t2") == 0){
        return $t2;
    }else if(strcmp(reg,"$t3") == 0){
        return $t3;
    }else if(strcmp(reg,"$t4") == 0){
        return $t4;
    }else if(strcmp(reg,"$t5") == 0){
        return $t5;
    }else if(strcmp(reg,"$t6") == 0){
        return $t6;
    }else if(strcmp(reg,"$t7") == 0){
        return $t7;
    }else if(strcmp(reg,"$t8") == 0){
        return $t8;
    }else if(strcmp(reg,"$t9") == 0){
        return $t9;
    }else if(strcmp(reg,"$t10") == 0){
        return $t10;
    }else if(strcmp(reg,"$t11") == 0){
        return $t11;
    }else if(strcmp(reg,"$t12") == 0){
        return $t12;
    }else if(strcmp(reg,"$t13") == 0){
        return $t13;
    }else if(strcmp(reg,"$t14") == 0){
        return $t14;
    }else if(strcmp(reg,"$t15") == 0){
        return $t15;
    }else if(strcmp(reg,"$t16") == 0){
        return $t16;
    }else if(strcmp(reg,"$t17") == 0){
        return $t17;
    }else if(strcmp(reg,"$t18") == 0){
        return $t18;
    }else if(strcmp(reg,"$t19") == 0){
        return $t19;
    }else if(strcmp(reg,"$t20") == 0){
        return $t20;
    }else if(strcmp(reg,"$t21") == 0){
        return $t21;
    }else if(strcmp(reg,"$t22") == 0){
        return $t22;
    }else if(strcmp(reg,"$t23") == 0){
        return $t23;
    }else if(strcmp(reg,"$t24") == 0){
        return $t24;
    }else if(strcmp(reg,"$t25") == 0){
        return $t25;
    }else if(strcmp(reg,"$t26") == 0){
        return $aux;
    }else if(strcmp(reg,"$t27") == 0){
        return $rf;
    }else if(strcmp(reg,"$t28") == 0){
        return $fp;
    }else if(strcmp(reg,"$t29") == 0){
        return $sp;
    }else if(strcmp(reg,"$t30") == 0){
        return $ra;
    }
    return 99; // ERRO
} 

void criaLabel(char * label){

    noLabel* novo = (noLabel*)malloc(sizeof(noLabel));
    novo->nome = (char*)malloc(strlen(label)*sizeof(char));
    strcpy(novo->nome,label);
    novo->prox = NULL;
    novo->linha = numLinhas;

    if(primeiraLabel == NULL){
        primeiraLabel = novo;
        ultimaLabel = novo;
    }else{
        ultimaLabel->prox = novo;
        ultimaLabel = novo;
    }

}

int pegaLinhaLabel(char * label){
    noLabel* temp = primeiraLabel;
    while(temp != NULL ){
        if(strcmp(temp->nome,label) == 0){
            break;
        }
        temp = temp->prox;
    }
    if(temp != NULL){
        return temp->linha;
    }else{
        return -1;
    }
}

void geraAssembly(Quad* q){
    char temp[50];
    insereInstJ(JUMP,"main");  // vai direto para o main
    while(q != NULL){
        if(q->op == add){
            if(q->arg1.type == String && q->arg2.type == String){
                // add
                insereInstR(ADD,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == String && q->arg2.type == Const){
                // addi
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(ADDI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);

            }else if(q->arg2.type ==  String && q->arg1.type == Const){
                // addi
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(ADDI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
                // soma de dois imediatos não foi implementada
            }
        }

        if(q->op == sub){
            
            if(q->arg1.type == String && q->arg2.type == String){
                //sub
                insereInstR(SUBB,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));

            }else if(q->arg1.type == Const && q->arg2.type == String){
                // subi
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SUBI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            
            }else if(q->arg1.type == String && q->arg2.type == Const){
                // subi
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SUBI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
                // sub de dois imediatos não foi implementada
            }
    }
        
        if(q->op == divi){

            if(q->arg1.type == String && q->arg2.type == String){
                // div
                insereInstR(DIVV,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
        
            }else if(q->arg1.type == Const && q->arg2.type == String){
                // divi
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(DIVI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type == Const){
                // divi
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(DIVI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
                // div de dois imediatos não foi implementada
            }
        }
        
        if(q->op == mul){

            if(q->arg1.type == String && q->arg2.type == String){
                // mul
                insereInstR(MUL,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                // multi
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(MULTI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);

            }else if(q->arg1.type == String && q->arg2.type == Const){
                // multi
                sprintf(temp,"%d",q->arg2.conteudo.val); //transofrma o int em char
                insereInstI(MULTI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
                // mul de dois imediatos não foi implementada
            } 
        }
        
        if(q->op == iff){   // bugado
            // iff
            insereInstI(BEQZ,pegaRegistrador(q->arg1.conteudo.nome),$zero,q->arg2.conteudo.nome);
        }
        
        
        if(q->op == call){

            if(!strcmp(q->arg1.conteudo.nome,"input")){

                insereIsntIO(INPUT,$rf);                //ESTUDAR COMO FUNCIONA A PARTE DE INPUT E OUTPUT

            }else if(!strcmp(q->arg1.conteudo.nome,"output")){
                


            }else{

                //fazer uma pilha de parametros
            }

        }
    
        if(q->op == param){

            if(pilhaParam == NULL){
                pilhaParam =(Pilha*)malloc(sizeof(Pilha));
                inicializarPilha(pilhaParam);
                empilhar(pilhaParam,q->arg1.conteudo.nome);
            }
            
            if(q->arg1.type == Const){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                empilhar(pilhaParam,temp);
            }else{
                empilhar(pilhaParam,q->arg1.conteudo.nome);
            }
        }

        if(q->op == jump){
            insereInstJ(JUMP,q->arg1.conteudo.nome);
        }

        if(q->op == label){
            criaLabel(q->arg1.conteudo.nome);
        }

        if(q->op == slt){

            if(q->arg1.type == String && q->arg2.type == String){
                // slt
                insereInstR(SLT,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }
        }


        
        q = q->prox;

    }
    
    imprimeInstrucoes();
    
}

void imprimeInstrucoes(){

    FILE * f = fopen("assembly.txt","w"); 
    NoInstrucao * p = primeiraInstrucao;
    NoInstrucao * aux;
    while(p != NULL){

        if(p->tipo == 0){
            if(strcmp(p->endereco,"main")!= 0){
                fprintf(f,"%s , %i \n",ListaInstStr[p->inst],pegaLinhaLabel(p->endereco));  
            }else{
                fprintf(f,"%s , %s \n",ListaInstStr[p->inst],p->endereco);
            }

        }else if(p->tipo == 1){
            fprintf(f,"%s , %s , %s , %s \n",ListaInstStr[p->inst],ListaRegStr[p->reg1],ListaRegStr[p->reg2],ListaRegStr[p->reg3]);
        }else if(p->tipo == 2){
            fprintf(f,"%s , %s , %s , %s \n",ListaInstStr[p->inst],ListaRegStr[p->reg1],ListaRegStr[p->reg2],p->imediato);
        }else if(p->tipo == 3){
            fprintf(f,"%s , %s \n",ListaInstStr[p->inst],ListaRegStr[p->reg1]);
        }
        p = p->prox;
    }

}