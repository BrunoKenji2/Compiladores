#include "assembler.h"
#include <string.h>
#include <ctype.h>
#include "pilha.h"
#include <stdlib.h>


/*
    inst tipo 0 = jump
    SW => SW(REGBASE, REGDATA, IMEDIATO)
    LW => LW(REGBASE, REGDEST, IMEDIATO)
    para o futuro remover tudo relacioando ao sp -> varivel nao o registrador
*/

NoInstrucao * primeiraInstrucao = NULL;
NoInstrucao * ultimaInstrucao = NULL;
int numLinhas = 1;
Pilha * pilhaParam = NULL;
noLabel * primeiraLabel = NULL;
noLabel * ultimaLabel = NULL;
escopos * primeiroEscopo = NULL;
escopos * ultimoEscopo = NULL;
int memLocG = 0; // memória local global
int teste;
int numeroDeParametros = 0;
int flagAlocGlobal = 1; // flag para saber se eu estou alocando variaveis globais ou nao
int flagAlocacaoParam = 0; // flag para saber se eu estou alocando parametros ou nao
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
        if(primeiraInstrucao == NULL){
        primeiraInstrucao = (NoInstrucao*)malloc(sizeof(NoInstrucao));
        primeiraInstrucao->inst = inst;
        primeiraInstrucao->reg1 = reg1;
        primeiraInstrucao->prox = NULL;
        primeiraInstrucao->reg2 = reg2;
        primeiraInstrucao->imediato = (char *)malloc(sizeof(char)*strlen(imediato));
        strcpy(primeiraInstrucao->imediato, imediato);
        primeiraInstrucao->tipo = 2;
        ultimaInstrucao = primeiraInstrucao;
    }else{
        
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
    }
    numLinhas++;
}

void insereInstIO(instrucao inst,registradores reg){

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
    }else if(strcmp(reg,"$rf") == 0){
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

escopos * criaEscopo(char* nome){
    escopos * novo = (escopos*)malloc(sizeof(escopos));
    novo->nome = (char*)malloc(strlen(nome)*sizeof(char));
    strcpy(novo->nome,nome);
    novo->prox = NULL;
    return novo;
}

escopos * procuraEscopo(char * nome){
    escopos * temp = primeiroEscopo;
    while(temp != NULL){
        if(strcmp(temp->nome,nome) == 0){
            return temp;
        }
        temp = temp->prox;
    }
    return NULL;
}

variavel * criaVariavel(char * nome, int posMemoria, int posMemEscopo){
    variavel * novo = (variavel*)malloc(sizeof(variavel));
    novo->nome = (char*)malloc(strlen(nome)*sizeof(char));
    strcpy(novo->nome,nome);
    novo->posMemoria = posMemoria;
    novo->posicaoMemEscopo = posMemEscopo;
    novo->prox = NULL;
    return novo;
}

void insereVar(char * nomeVar, char* nomeEscopo, int posMemoria, int memSize){
    escopos * escopo = procuraEscopo(nomeEscopo);
    if(primeiroEscopo == NULL){
        primeiroEscopo = criaEscopo(nomeEscopo);    // sem nenhum escopo criado
        ultimoEscopo = primeiroEscopo;
        escopo = primeiroEscopo;
        escopo->mem = 0;
    }else{
        if(escopo == NULL){
            escopo = criaEscopo(nomeEscopo);    // escopo ainda não foi criado
            ultimoEscopo->prox = escopo;
            ultimoEscopo = escopo;
            escopo->mem = 0;

        }
    }
    escopo->mem = escopo->mem + memSize; // aloca 1 para cada variavel
    variavel * aux = escopo->variaveis;
    if(strcmp(nomeEscopo,"global") == 0){
        if(aux == NULL){
            //se ainda nao ha variaveis
            escopo->variaveis = criaVariavel(nomeVar,63-memLocG,memLocG);
        }else{
            while(aux->prox != NULL && aux != NULL){
                aux = aux->prox;
            }
        aux->prox = criaVariavel(nomeVar,63-memLocG,memLocG);
        }
    memLocG = memLocG + memSize; // atualiza o valor da memoria global

    }else if(strcmp(nomeEscopo,"main") == 0){
        if(aux == NULL){
            escopo->variaveis = criaVariavel(nomeVar,posMemoria,escopo->mem-1);
        }else{
            while(aux->prox != NULL && aux != NULL){
                 aux = aux->prox;
            }
        aux->prox = criaVariavel(nomeVar,posMemoria,escopo->mem-1);

        }
    }else{
        if(aux == NULL){
            // tem +1 por causa do $ra e $fp
            escopo->variaveis = criaVariavel(nomeVar,posMemoria,escopo->mem-1);
        }else{
            while(aux->prox != NULL && aux != NULL){
                 aux = aux->prox;
            }
        aux->prox = criaVariavel(nomeVar,posMemoria,escopo->mem-1);
        }
    }
}

int pegaPosMemoria(char* nomeVar,char* nomeEscopo)
{
    escopos * escopo = procuraEscopo(nomeEscopo);
    variavel * aux = escopo->variaveis;
    while(aux != NULL){
        if(strcmp(aux->nome,nomeVar) == 0){
            return aux->posicaoMemEscopo; // retorna a posição de memória da variável em relação ao fp
        }
        aux = aux->prox;
    }
    return -1;
}

 NoInstrucao * geraAssembly(Quad* q){
    char temp[50];
    char temp2[50];
    insereInstI(ADDI,$sp,$sp,"0");
    insereInstI(ADDI,$fp,$fp,"0");
    while(flagAlocGlobal == 1)
    {
        if(q->op == allocaMemVar)
        {
            flagAlocGlobal = 1;
            sprintf(temp,"%d",63-memLocG);
            insereInstI(SW,$zero,$zero,temp);
            insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,63-memLocG,1);
            q = q->prox;

        }
        else if( q->op == allocaMemVet)
        {
            if(q->out.conteudo.val > 0)
                {
                    flagAlocGlobal = 1;
                    int indice;
                    for(indice = 0; indice <= q->out.conteudo.val; indice++)
                    {   
                        //63-memLocG e a pos da memoria que vai ser alocada
                        if(indice == 0)
                        {
                            sprintf(temp,"%d",63-memLocG - q->out.conteudo.val);
                            insereInstI(ADDI,$zero,$aux,temp);  //salva o endereco no 0 e os proximos 10 sao os valores note que ele aloca o numero n de espacos, a variavel com o valor do endereco fica no fim e ela aponta para o comeco da lista
                            sprintf(temp,"%d",63-memLocG);
                            insereInstI(SW,$zero,$aux,temp);
                        }else
                        {
                            sprintf(temp,"%d",63-memLocG-indice);
                            insereInstI(SW,$zero,$zero,temp); // guarda o vetor na memoria global posicao por posicao, inicializando com 0
                        }
                    }
                    insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,q->out.conteudo.val);
                }else
                {
                    flagAlocGlobal = 1;
                    sprintf(temp,"%d",63-memLocG); // pega a memoria global gasta - o topo
                    insereInstI(SW,$zero,$zero,temp); // guarda o vetor na memoria global
                    insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,1);
                }
            q = q->prox;        
        }
        else
        {
            flagAlocGlobal = 0;
            insereInstJ(JUMP,"main");  // vai direto para o main
        }
        
    }
        
    
    while(q != NULL){
        //Intruções R
        if(q->op == add){
            if(q->arg1.type == String && q->arg2.type == String){
                // add -> rt = rd + rs
                insereInstR(ADD,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == String && q->arg2.type == Const){
                // addi -> rt = rs + immediate
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
                insereInstR(MULT,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
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
        
        if(q->op == iff){       
            // iff -> se falso entra, não da branch
            insereInstI(BEQ,pegaRegistrador(q->arg1.conteudo.nome),$zero,q->arg2.conteudo.nome);
        }
        
        
        if(q->op == call){
            int numParam = q->arg2.conteudo.val; // pega o numero de parametros da chamada
            char * paramList[numParam];
            int tiposParam[numParam];
            int i = 0;
            int refParam = 0;
            if(!strcmp(q->arg1.conteudo.nome,"input")){
                insereInstIO(INPUT,$rf);                
                insereInstIO(OUTPUT,$rf); // imprime o valor lido
            }else if(!strcmp(q->arg1.conteudo.nome,"output")){
                if(pilhaParam->topo->tipo == 0){
                    insereInstI(ADDI,$zero,$aux,desempilhar(pilhaParam));
                    insereInstIO(OUTPUT,$aux);  // desempilha os parametros imediatos, carregando eles no aux e joga o output
                }else if(pilhaParam->topo->tipo == 1){
                    // desempilha o registrador e joga no output -- tipo = 1 => output é um registrador
                    insereInstIO(OUTPUT,pegaRegistrador(desempilhar(pilhaParam)));
                }
            }else{
                //chamada de função => salva o numero de parametros para desempilhar ao allocar os parametros na funcao
                numeroDeParametros = q->arg2.conteudo.val; // salva o numero de parametros para localizar o offset dos parametros
                 for(i = 0; i < numParam; i++){
                     tiposParam[i] = pilhaParam->topo->tipo; // guarda o tipo do parametro
                     paramList[i] = (char*)malloc(strlen(pilhaParam->topo->parametro)*sizeof(char));
                     strcpy(paramList[i],desempilhar(pilhaParam)); // desempilha os parametros
                 }
                 int contAux = 0;
                 for(i = numParam; i > 0; i--)
                 {
                    
                    /*
                        sw sempre com 2 a mais dando espaco para o ra e o fp que sao obrigatorios, e depois nos allocaMem o $sp sera atualizado de verdade
                    */
                    sprintf(temp,"%d",2+contAux); // cria o nome do parametro
                     if(tiposParam[i-1] == 0)
                     {
                        
                         //insereVar(temp,q->arg1.conteudo.nome,refParam,1); // insere a variavel no escopo
                         insereInstI(ADDI,$zero,$aux,paramList[i-1]); // transforma o valor imediato em string
                         insereInstI(SW,$sp,$aux,temp); // armazena o parametro na pilha
                     }else
                     {
                         // tipo 1 => registrador
                         //insereVar(temp,q->arg1.conteudo.nome,refParam,1); // insere a variavel no escopo
                         insereInstI(SW,$sp,pegaRegistrador(paramList[i-1]),temp);
                     }
                     contAux++;
                 }
                
                insereInstJ(JAL,q->arg1.conteudo.nome);
            }

        }
    
        if(q->op == param){
            
            if(pilhaParam == NULL){
                pilhaParam =(Pilha*)malloc(sizeof(Pilha));
                inicializarPilha(pilhaParam);
                //empilhar(pilhaParam,q->arg1.conteudo.nome);
            }
            
            if(q->arg1.type == Const){
                // transforma o valor inteiro em string e empilha tipo 0
                sprintf(temp,"%d",q->arg1.conteudo.val);
                empilhar(pilhaParam,temp,0);
            }else{
                // empilha o nome do registrador tipo 1
                empilhar(pilhaParam,q->arg1.conteudo.nome,1);
            }
        }

        if(q->op == move){
            if(q->arg1.type == Const){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                //adiciona o valor imediato no registrador com o ADDI
                insereInstI(ADDI,$zero,pegaRegistrador(q->arg2.conteudo.nome),temp);
            }else{
                // move -> copia o valor de um registrador para outro
                insereInstI(ADDI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),"0");
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
                // set less than "<"
                insereInstR(SLT,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(ADDI,$zero,$aux,temp);
                // insere o valor do imediato no $aux para realizar a comparação
                insereInstR(SLT,pegaRegistrador(q->arg2.conteudo.nome),$aux,pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(ADDI,$zero,$aux,temp);
                insereInstR(SLT,pegaRegistrador(q->arg1.conteudo.nome),$aux,pegaRegistrador(q->out.conteudo.nome));
            }else{
                // não tem slt com dois imediatos
            }
        }
        /*
        REVER PARA O FUTURO
        if(q->op ==  sgt){ // maior que
            if(q->arg1.type == String && q->arg2.type == String){
                //  ">"
                insereInstR(SGT,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SGTI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SGTI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
            
            }
        }
        */
        
        if(q->op ==  slet){ // menor ou igual
            if(q->arg1.type == String && q->arg2.type == String){
                // slet <=
                insereInstR(SLET,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SLETI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SLETI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
                // não tem slet com dois imediatos
            }
        }
        /*
        if(q->op ==  sdt){ //diferente
            if(q->arg1.type == String && q->arg2.type == String){
                // sdt >=
                insereInstR(SDT,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SDTI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SDTI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
            
            }
        }
        */
        if(q->op == set) 
        {
            if(q->arg1.type == String && q->arg2.type == String)
            {
                // rt = rd == rs
                insereInstR(SET,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }
            // se for um imediato, carrega no aux e faz a operação
            else if(q->arg1.type == Const && q->arg2.type == String)
            {
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(ADDI,$zero,$aux,temp);
                insereInstR(SET,pegaRegistrador(q->arg2.conteudo.nome),$aux,pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == String && q->arg2.type == Const)
            {
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(ADDI,$zero,$aux,temp);
                insereInstR(SET,pegaRegistrador(q->arg1.conteudo.nome),$aux,pegaRegistrador(q->out.conteudo.nome));
            }
        }
        /*
        if(q->op ==  set){ //igual
            if(q->arg1.type == String && q->arg2.type == String){
                // set
                if(q->prox->op == iff){
                    insereInstR(ADDI,$zero,pegaRegistrador(q->arg1.conteudo.nome),$aux);
                    strcpy(q->prox->arg1.conteudo.nome,q->arg2.conteudo.nome);
                }else{
                    insereInstR(SET,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
                }

            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                if(q->prox->op == iff){
                    insereInstI(ADDI,$zero,$aux,temp);
                    strcpy(q->prox->arg1.conteudo.nome,q->arg2.conteudo.nome);
                }else{
                insereInstI(SETI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
                }
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                if(q->prox->op == iff){
                    insereInstI(ADDI,$zero,$aux,temp);
                    strcpy(q->prox->arg1.conteudo.nome,q->arg1.conteudo.nome);
                }else{
                    insereInstI(SETI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
                }
            }else{
            
            }
        }
        */
       /*
        if(q->op ==  sget){     //maior igual
            if(q->arg1.type == String && q->arg2.type == String){
                // sget
                insereInstR(SGET,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SGETI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SGETI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
            
            }
        }
        */

        if(q->op ==  fun){
            criaLabel(q->arg1.conteudo.nome);
            if(strcmp("main",q->arg1.conteudo.nome) != 0){ 
                insereInstI(SW,$sp,$ra,"0"); 
                insereInstI(ADDI,$sp,$sp,"1");
                insereVar("$ra",q->arg1.conteudo.nome,0,1);    
                // armazena o endereço de retorno na pilha na memoria para não perder e att o sp

                insereInstI(SW,$sp,$fp,"0"); // armazena o $fp na pilha
                insereInstI(ADDI,$sp,$sp,"1"); // incrementa o sp
                insereVar("$fp",q->arg1.conteudo.nome,0,1);
                insereInstI(SUBI,$sp,$fp,"2"); //calculo do novo $fp, guardando o antigo $fp
                if(q->prox->op == allocaMemVar || q->prox->op == allocaMemVet)
                {
                    //alocacao de parametros sempre ocorre apos o fun
                    flagAlocacaoParam = 1; // flag para indicar que tem alocação de variaveis
                }
            }
        }

        if(q->op == endF){
            
            if(strcmp("main",q->arg1.conteudo.nome)){
                escopos * guardaNo = procuraEscopo(q->arg1.conteudo.nome); 
                sprintf(temp,"%d",guardaNo->mem);
                insereInstI(SUBI,$sp,$sp,temp); // reseta o $sp
                insereInstI(LW,$fp,$ra,"0");    // carrega o endereço de retorno que estava salvo na memoria, indicado por $fp
                insereInstI(LW,$fp,$fp,"1");    // apos a execução da função o $fp volta para a sua origem 
                insereInstR(JR,$ra,$zero,$zero);  // incrementa o ponteiro da pilha
            }

        }

        /*
        lembrar que arg1 = rs, arg2 = rt, out = rd, manter sempre a ordem lembrando da arquitetura do processador
        $sp so aloca para variaveis locais
        */

        if(q->op == allocaMemVar){
            //declaração de variavel
            /*
                falta a inserção das variaveis em lista com a posição da memoria em que elas estão
            */
            // se for global -> começa em baixo, se for local começa no topo
            if(!strcmp(q->arg1.conteudo.nome,"global")){
                sprintf(temp,"%d",63-memLocG);
                insereInstI(SW,$zero,$zero,temp);
                insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,63-memLocG,1);
            }else{
                if(flagAlocacaoParam == 1)
                {
                    insereInstI(ADDI,$sp,$sp,"1"); // incrementa o sp para alocar a variavel
                    insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,1);
                    if(q->prox->op == allocaMemVet || q->prox->op == allocaMemVar)
                    {
                        // se for alocação de variaveis, incrementa o sp => unico problema é caso tenha alocacao de memoria logo apos a alocacao dos param -> mas como é mais para inicializar não há problema
                        flagAlocacaoParam = 1; // reseta a flag
                    }else{
                        flagAlocacaoParam = 0; // reseta a flag
                    }
                }else{                
                insereInstI(SW,$sp,$zero,"0"); // deixa a posição de memoria guardada e atribui o valor 0 para elas
                insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,1);
                insereInstI(ADDI,$sp,$sp,"1");
                }
            }
            
        }

        if(q->op == allocaMemVet){
            if(strcmp(q->arg1.conteudo.nome,"global")==0){
                if(q->out.conteudo.val > 0)
                {
                    insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,q->out.conteudo.val);
                    sprintf(temp,"%d",63-memLocG); // pega a memoria global gasta - o topo
                    insereInstI(SW,$zero,$zero,temp); // guarda o vetor na memoria global
                }else
                {
                    insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,1);
                    sprintf(temp,"%d",63-memLocG); // pega a memoria global gasta - o topo
                    insereInstI(SW,$zero,$zero,temp); // guarda o vetor na memoria global
                }
                
            }else{
                    if(q->out.conteudo.val > 0){
                    
                        sprintf(temp,"%d",q->out.conteudo.val); // pega o numero de posições e multiplica por 4
                        insereInstI(SW,$sp,$zero,0);
                        insereInstI(ADDI,$sp,$sp,temp); // incrementa o sp para o tamanho do vetor
                        insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,q->out.conteudo.val);

                    }else if(q->out.conteudo.val == 0){
                        //allocacao de vetor como parametro
                        insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,1); //vetor parametro
                        insereInstI(ADDI,$sp,$sp,"1"); // declarando o vetor
                    }
            }
            
        }
        /*
            No exemplo ele quando ele declara as var ele deixa $fp de ref para a var e $zero para as memoria globais
        */
        if(q->op == storeVar){
            
            if(q->arg1.type == String){
                if(strcmp(q->out.conteudo.nome,"global")){
                    // store local
                    sprintf(temp,"%d",pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
                    insereInstI(SW,$fp,pegaRegistrador(q->arg1.conteudo.nome),temp);
                }else{
                    // store global
                    sprintf(temp,"%d",63-pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
                    insereInstI(SW,$zero,pegaRegistrador(q->arg1.conteudo.nome),temp);

                }
                
            }else if(q->arg1.type == Const){
                sprintf(temp2,"%d",q->arg1.conteudo.val);
                insereInstI(ADDI,$zero,$aux,temp2);
                if(strcmp(q->out.conteudo.nome,"global")){
                    // store local
                    sprintf(temp,"%d",pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
                    sprintf(temp2,"%d",q->arg1.conteudo.val);
                    insereInstI(SW,$fp,$aux,temp);
                }else{
                    sprintf(temp,"%d",63-pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
                    sprintf(temp2,"%d",q->arg1.conteudo.val);
                    insereInstI(SW,$zero,$aux,temp);
                }     
            }
        }

        if(q->op == storeVet){

            if(q->arg1.type == String){
                insereInstI(SW,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->arg1.conteudo.nome),"0");
            }else{
                sprintf(temp2,"%d",q->arg1.conteudo.val);
                insereInstI(ADDI,$zero,$aux,temp2);
                insereInstI(SW,pegaRegistrador(q->arg2.conteudo.nome),$aux,"0");
            }
        }
        /*
            guarda valores nos indices dos vetores -> calcula o endereço e fazer o store usando valores dos registradores
        */
       if(q->op == loadVar){
                        
                if(strcmp(q->arg1.conteudo.nome,"global")){
                    //load local
                    //pega a posicao em relacao ao fp
                    sprintf(temp,"%d",pegaPosMemoria(q->arg2.conteudo.nome,q->arg1.conteudo.nome));
                    insereInstI(LW,$fp,pegaRegistrador(q->out.conteudo.nome),temp);
                }else{
                    //load global => como comeca no topo, entao temos 63(topo) - a pos em relacao ao topo
                    sprintf(temp,"%d",63-pegaPosMemoria(q->arg2.conteudo.nome,q->arg1.conteudo.nome));
                    insereInstI(LW,$zero,pegaRegistrador(q->out.conteudo.nome),temp);
                }

       }

       if(q->op == loadVet){

            insereInstI(LW,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),"0");

       }

       if(q->op == empilha){
            //alteracoes => a funcao do empilha vai ser embutida no call
        /*
            if(q->arg1.type == Const){
                sprintf(temp,"$t%d",q->arg1.conteudo.val);
            }
            //param  joga na pilha e o empilha da um store no registrador do param
            insereInstI(SW,$sp,pegaRegistrador(temp),"0");
            insereInstI(ADDI,$sp,$sp,"1");  // abre espaço na pilha e salva o valor do reg na pilha
            sp = sp + 1;
        */
        }
    
       if(q->op == desempilha){
            /*
            if(q->arg1.type == Const){
                sprintf(temp,"$t%d",q->arg1.conteudo.val);
            }
            sp = sp + 4;
            insereInstI(LW,pegaRegistrador(temp),$sp,"0");
            insereInstI(ADDI,$sp,$sp,"4");  // fecha espaço na pilha e carrega o valor do reg na pilha
            */
       }
       
        /*
            A ideia vai ser salvar var globais no começo, de forma que elas sempre vão ter que ser declaradas no começo do código,
            deixar um indicador avisando até que parte vão ter var globais
        */

        




 
        q = q->prox;

    }
    
    imprimeInstrucoes();
    //imprimeLabel();
    return primeiraInstrucao;
    
}

void imprimeLabel(){
    noLabel * temp = primeiraLabel;
    while(temp != NULL){
        temp = temp->prox;
    }
}

void imprimeInstrucoes(){

    FILE * f = fopen("saidas/assembly.txt","w"); 
    NoInstrucao * p = primeiraInstrucao;
    NoInstrucao * aux;
    noLabel * temp = primeiraLabel;
    int count = 1;
    int atraso = 0;
    while(p != NULL){

        if(p->tipo == 0){
           
            fprintf(f,"%s , %i \n",ListaInstStr[p->inst],pegaLinhaLabel(p->endereco));
            
            

        }else if(p->tipo == 1){
            fprintf(f,"%s , %s , %s , %s \n",ListaInstStr[p->inst],ListaRegStr[p->reg1],ListaRegStr[p->reg2],ListaRegStr[p->reg3]);
        }else if(p->tipo == 2){
            fprintf(f,"%s , %s , %s , %s \n",ListaInstStr[p->inst],ListaRegStr[p->reg1],ListaRegStr[p->reg2],p->imediato);
        }else if(p->tipo == 3){
            fprintf(f,"%s , %s \n",ListaInstStr[p->inst],ListaRegStr[p->reg1]);
        }
        p = p->prox;
        count++;
    }
    printf("Assembly gerado com sucesso!\n");

}