#include "assembler.h"
#include <string.h>
#include <ctype.h>
#include "pilha.h"
#include <stdlib.h>


/*
    INSTRUÇÕES QUE FALTAM
    -call
    -move
    -imprimir as labels e fazer com que elas ocupem linhas
*/

/*
    inst tipo 0 = jump
*/

NoInstrucao * primeiraInstrucao = NULL;
NoInstrucao * ultimaInstrucao = NULL;
int numLinhas = 1;
Pilha * pilhaParam = NULL;
noLabel * primeiraLabel = NULL;
noLabel * ultimaLabel = NULL;
escopos * primeiroEscopo = NULL;
escopos * ultimoEscopo = NULL;
int sp = 0x7FFFFFFF; // pilha começa no endereço 0x7FFFFFFF
int memLocG = 0; // memória local global

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

variavel * criaVariavel(char * nome, int posMemoria){
    variavel * novo = (variavel*)malloc(sizeof(variavel));
    novo->nome = (char*)malloc(strlen(nome)*sizeof(char));
    strcpy(novo->nome,nome);
    novo->posMemoria = posMemoria;
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
    escopo->mem = escopo->mem + memSize; // aloca 4 bytes para cada variavel
    variavel * aux = escopo->variaveis;
    if(strcmp(nomeEscopo,"global") == 0){
        if(aux == NULL){
            escopo->variaveis = criaVariavel(nomeVar,memLocG);
        }else{
            while(aux->prox != NULL && aux != NULL){
                aux = aux->prox;
            }
        aux->prox = criaVariavel(nomeVar,memLocG);
        memLocG = memLocG + memSize; // atualiza o valor da memoria global

        }
    }else{
        if(aux == NULL){
            escopo->variaveis = criaVariavel(nomeVar,posMemoria);
        }else{
            while(aux->prox != NULL && aux != NULL){
                 aux = aux->prox;
            }
        aux->prox = criaVariavel(nomeVar,posMemoria);

        }
    }
}

int pegaPosMemoria(char* nomeVar,char* nomeEscopo)
{
    escopos * escopo = procuraEscopo(nomeEscopo);
    variavel * aux = escopo->variaveis;
    while(aux != NULL){
        if(strcmp(aux->nome,nomeVar) == 0){
            return aux->posMemoria;
        }
        aux = aux->prox;
    }
    return -1;
}

 NoInstrucao * geraAssembly(Quad* q){
    char temp[50];
    char temp2[50];
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
            // iff
            insereInstI(BEQZ,pegaRegistrador(q->arg1.conteudo.nome),$zero,q->arg2.conteudo.nome);
        }
        
        
        if(q->op == call){

            if(!strcmp(q->arg1.conteudo.nome,"input")){

                insereInstIO(INPUT,$rf);                
                
            }else if(!strcmp(q->arg1.conteudo.nome,"output")){
                if(pilhaParam->topo->tipo == 0){
                    insereInstI(ADDI,$zero,$aux,desempilhar(pilhaParam));
                    insereInstIO(OUTPUT,$aux);  // desempilha no aux e joga o output
                }else if(pilhaParam->topo->tipo == 1){
                    insereInstIO(OUTPUT,pegaRegistrador(desempilhar(pilhaParam)));
                }
            }else{
                int numParam = q->arg2.conteudo.val;
                int h = 1;
                for(numParam;numParam > 0; numParam--){
                    insereInstI(ADDI,$sp,$sp,"-4"); // aloca espaço na pilha
                    sprintf(temp,"%d",h*-4);
                    sp = sp -4;
                    if(pilhaParam->topo->tipo == 0){
                        insereInstI(ADDI,$zero,$aux,desempilhar(pilhaParam));
                        insereInstI(SW,$fp,$aux,temp);
                    }else if(pilhaParam->topo->tipo == 1){
                        insereInstI(SW,$fp,pegaRegistrador(desempilhar(pilhaParam)),temp);
                    }
                }
                insereInstJ(JAL,q->arg1.conteudo.nome);
                /*
                insereInstI(ADDI,$fp,$sp,"0");  //atualiza o $sp
                insereInstI(LW,$fp,$fp,"0");    //carrega o antigo $fp
                não precisa fazer isso pois, esse procedimento já é feito no final da função
                */
                //fazer uma pilha de parametros
            }

        }
    
        if(q->op == param){

            if(pilhaParam == NULL){
                pilhaParam =(Pilha*)malloc(sizeof(Pilha));
                inicializarPilha(pilhaParam);
                //empilhar(pilhaParam,q->arg1.conteudo.nome);
            }
            
            if(q->arg1.type == Const){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                empilhar(pilhaParam,temp,0);
            }else{
                empilhar(pilhaParam,q->arg1.conteudo.nome,1);
            }
        }

        if(q->op == move){
            if(q->arg1.type == Const){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(ADDI,$zero,pegaRegistrador(q->arg2.conteudo.nome),temp);
            }else{
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
                // set less than
                insereInstR(SLT,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SLTI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SLTI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
                // não tem slt com dois imediatos
            }
        }

        if(q->op ==  sgt){ // maior que
            if(q->arg1.type == String && q->arg2.type == String){
                // sgt
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

        if(q->op ==  slet){ // menor ou igual
            if(q->arg1.type == String && q->arg2.type == String){
                // slet
                insereInstR(SLET,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SLETI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SLETI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
            
            }
        }

        if(q->op ==  sdt){ //diferente
            if(q->arg1.type == String && q->arg2.type == String){
                // sdt
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

        if(q->op ==  set){ //igual
            if(q->arg1.type == String && q->arg2.type == String){
                // set
                insereInstR(SET,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome));
            }else if(q->arg1.type == Const && q->arg2.type == String){
                sprintf(temp,"%d",q->arg1.conteudo.val);
                insereInstI(SETI,pegaRegistrador(q->arg2.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else if(q->arg1.type == String && q->arg2.type ==  Const){
                sprintf(temp,"%d",q->arg2.conteudo.val);
                insereInstI(SETI,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->out.conteudo.nome),temp);
            }else{
            
            }
        }

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


        if(q->op ==  fun){
            criaLabel(q->arg1.conteudo.nome);
            if(strcmp("main",q->arg1.conteudo.nome) != 0){
                printf("fun %s\n",q->arg1.conteudo.nome);
                insereInstI(ADDI,$sp,$sp,"-8");  // aumenta a pilha, note que a pilha cresce para baixo
                insereInstI(SW,$sp,$ra,"4");    // armazena o endereço de retorno na pilha na memoria para não perder
                insereInstI(SW,$sp,$fp,"0");    //guarda o antigo $fp
                insereInstI(ADDI,$sp,$fp,"0");  //atualiza o $fp
                sp = sp - 8;
            
            }
        }

        if(q->op == endF){
            
            if(strcmp("main",q->arg1.conteudo.nome)){
                escopos * guardaNo = procuraEscopo(q->arg1.conteudo.nome); 
                sprintf(temp,"%d",guardaNo->mem);
                insereInstI(ADDI,$sp,$sp,temp); // reseta o $sp
                insereInstI(LW,$ra,$sp,"4");    // carrega o endereço de retorno que estava salvo na memoria, indicado por $fp
                insereInstI(LW,$fp,$sp,"0");    // apos a execução da função o $fp volta para a sua origem
                insereInstI(ADDI,$sp,$sp,"8");  // libera o espaço na pilha 
                insereInstR(JR,$ra,$zero,$zero);  // incrementa o ponteiro da pilha
                sp = sp - guardaNo->mem - 8;
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
                insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,4);
            }else{                
                insereInstI(ADDI,$sp,$sp,"-4");
                sp = sp - 4;
                insereInstI(SW,$zero,$sp,"0"); // deixa a posição de memoria guardada e atribui o valor 0 para elas
                insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,sp,4);
            }
        }

        if(q->op == allocaMemVet){
            if(strcmp(q->arg1.conteudo.nome,"global")==0){
                if(q->out.conteudo.val > 0)
                {
                    insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,q->out.conteudo.val*4);
                }else
                {
                    insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,0,4);
                }
                
            }else{
                    if(q->out.conteudo.val > 0){
                
                        sprintf(temp,"%d",q->out.conteudo.val*-4); // pega o numero de posições e multiplica por 4
                        sp = sp - q->out.conteudo.val*4;
                        insereInstI(ADDI,$sp,$sp,temp);
                        insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,sp,q->out.conteudo.val*4);

                    }else if(q->out.conteudo.val == 0){
                        insereVar(q->arg2.conteudo.nome,q->arg1.conteudo.nome,sp,4); //vetor parametro
                        sp = sp - 4;
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
                    sprintf(temp,"%d",sp-pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
                    insereInstI(SW,$fp,pegaRegistrador(q->arg1.conteudo.nome),temp);
                }else{
                    // store global
                    sprintf(temp,"%d",pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
                    insereInstI(SW,$zero,pegaRegistrador(q->arg1.conteudo.nome),temp);

                }
                
            }else if(q->arg1.type == Const){
                sprintf(temp2,"%d",q->arg1.conteudo.val);
                insereInstI(ADDI,$zero,$aux,temp2);
                if(strcmp(q->out.conteudo.nome,"global")){
                    // store local
                    sprintf(temp,"%d",sp-pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
                    sprintf(temp2,"%d",q->arg1.conteudo.val);
                    insereInstI(SW,$fp,$aux,temp);
                }else{
                    sprintf(temp,"%d",pegaPosMemoria(q->arg2.conteudo.nome,q->out.conteudo.nome));
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
                    sprintf(temp,"%d",sp-pegaPosMemoria(q->arg2.conteudo.nome,q->arg1.conteudo.nome));
                    insereInstI(LW,$fp,pegaRegistrador(q->out.conteudo.nome),temp);
                }else{
                    //load global
                    sprintf(temp,"%d",pegaPosMemoria(q->arg2.conteudo.nome,q->arg1.conteudo.nome));
                    insereInstI(LW,$zero,pegaRegistrador(q->out.conteudo.nome),temp);
                }

       }

       if(q->op == loadVet){

            insereInstI(LW,pegaRegistrador(q->arg1.conteudo.nome),pegaRegistrador(q->arg2.conteudo.nome),"0");

       }

       if(q->op == empilha){
            if(q->arg1.type == Const){
                sprintf(temp,"$t%d",q->arg1.conteudo.val);
            }
            sp = sp -4;
            insereInstI(ADDI,$sp,$sp,"-4");  // abre espaço na pilha e salva o valor do reg na pilha
            insereInstI(SW,pegaRegistrador(temp),$sp,"0");
       }
    
       if(q->op == desempilha){
            if(q->arg1.type == Const){
                sprintf(temp,"$t%d",q->arg1.conteudo.val);
            }
            sp = sp + 4;
            insereInstI(LW,pegaRegistrador(temp),$sp,"0");
            insereInstI(ADDI,$sp,$sp,"4");  // fecha espaço na pilha e carrega o valor do reg na pilha

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
        printf("%s linha %i\n",temp->nome,temp->linha);
        temp = temp->prox;
    }
}

void imprimeInstrucoes(){

    FILE * f = fopen("assembly.txt","w"); 
    NoInstrucao * p = primeiraInstrucao;
    NoInstrucao * aux;
    noLabel * temp = primeiraLabel;
    int count = 1;
    int atraso = 0;
    while(p != NULL){

        /*
        if(temp != NULL){
            if(temp->linha == count-atraso){
                fprintf(f,"%s: \n",temp->nome);
                temp->linha = count;
                //printf("label %s linha %d cout %d\n",temp->nome,temp->linha,count);
                temp = temp->prox;
                count++;
                atraso++;
            }
        }
        */
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

}