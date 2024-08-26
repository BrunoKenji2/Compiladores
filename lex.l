%{
    #include "globals.h"
    #include "util.h"
    #include "scan.h"

    int lineno = 0;
    char tokenString[MAXTOKENLEN+1];

    FILE * source_file;
%}

DIGITO [0-9]
LETRA [a-zA-Z]
ESPACO [ \r\t]+

%%
"void"    return VOID;
"int"     return INT;
"while"   return WHILE;
"if"      return IF;
"else"    return ELSE;
"return"  return RETURN;
"\n"    {++lineno;}
"+"     return SOMA;
"-"     return SUB;
"*"	    return MUL;
"/"		return DIV;
"="		return ATRIB;
"=="     return IGL;
"!="    return DIF;
">="    return MAIGL;
"<="    return MEIGL;
">"     return MAI;
"<"     return MEN;
","     return VIRG;
";"		return PV;
"("		return APR;
")"		return FPR;
"["       return ACOL;
"]"     return FCOL;
"{"     return ACH;
"}"     return FCH;
"/*"        {
                char c;
                int flag = 0;
                while(flag != 2){
                  c = input();
                  if(c == '\n'){
                    lineno++;
                  }
                  if(c == EOF){
                    break;
                  }else if(c == '/' && flag){
                        flag++;
                  }else if(c == '*' && !flag){
                        flag++;
                  }else{
                    flag == 0;
                  }
                }
            }
{LETRA}+  return ID;
{DIGITO}+ return NUM;
{ESPACO}  {};
<<EOF>>   return 0;
({LETRA}|{DIGITO})+ {return ERRO;}
.			{return ERRO;}
%%

TokenType getToken(void)
{
  static int primeiraExecucao = 1;
	TokenType tokenAtual;
	if(primeiraExecucao)	
	{
		primeiraExecucao = 0;
    lineno++;
		yyin = source_file;
	}
	tokenAtual = yylex();
	strncpy(tokenString, yytext, MAXTOKENLEN);
	if(tokenAtual == ERRO)
	{
		 printf("ERRO LÉXICO: %s Linha: %d \n",yytext,(lineno));
	}
	return tokenAtual;
}

