#ifndef _UTIL_H_
#define _UTIL_H_

TreeNode * newStmtNode(StmtKind kind);
TreeNode * newExpNode(ExpKind kind);

char* printToken(TokenType token,const char* tokenString);
void printTree(TreeNode * tree);
void printTreeR( TreeNode * tree );
char * copyString(char * s); // copia string, talvez de erro
void insereEscopo(TreeNode * t, char * escopo); // coloca escopo
#endif