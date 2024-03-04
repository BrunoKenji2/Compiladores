#ifndef SCAN_H
#define SCAN_H

#define alfabeto 26
#define MAXTOKENLEN 40
#define MAXRESERVED 6

typedef enum
{
    START,
    INDEC,
    INCOMMENT,
    INCOMMENTOUT,
    INNUM,
    INID,
    IN2SS,
    DONE
} StateType;

typedef enum
{
    ENDFILE,
    ERROR,
    ELSE,
    IF,
    INT,
    RETURN,
    VOID,
    WHILE,
    RESERVEDWORD,
    PLUS,
    MINUS,
    TIMES,
    OVER,
    LT,
    LTE,
    GT,
    GTE,
    EQ,
    NEQ,
    ASSIGN,
    SEMI,
    COMMA,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    ID,
    NUM
} TokenType;

typedef struct no
{
    struct no *filhos[alfabeto];
    int tipo; // indica se é estado de aceitação
    TokenType token;
} no;

no *cria_no();
int encontra_indice(char c);
void insere(no *raiz, char str[], TokenType tok);
TokenType busca(no *raiz, char str[]);
void destroyTrie(no *raiz);
extern char tokenString[MAXTOKENLEN + 1];
void resetLexema();
void printToken(TokenType token, const char *tokenString);
TokenType getToken(void);
extern no *raiz_trie;

#endif // SCAN_H