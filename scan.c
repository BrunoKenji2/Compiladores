#include "globals.h"
#include "scan.h"

#define BUFLEN 256

static int linepos = 0;
static int bufsize = 0;
static int EOF_flag = 0;
static char lineBuf[BUFLEN];
int lineno = 0;
char tokenString[MAXTOKENLEN + 1];

no *cria_no()
{
  int i = 0;
  no *p = NULL;
  p = (no *)malloc(sizeof(no));
  if (!p)
  {
    printf("\n ERRO \n");
  }
  else
  {
    p->tipo = 0;
    p->token = ERROR;
    for (i = 0; i < alfabeto; i++)
    {
      p->filhos[i] = NULL;
    }
  }

  return (p);
}

int encontra_indice(char c)
{
  int chave = (int)c - (int)'a';
  return chave;
}

void insere(no *raiz, char str[], TokenType tok)
{
  int nivel;
  int indice;
  int tam = strlen(str);

  no *p = raiz;

  for (nivel = 0; nivel < tam; nivel++)
  {
    indice = encontra_indice(str[nivel]);
    if (p->filhos[indice] == NULL)
    {
      p->filhos[indice] = cria_no();
    }
    p = p->filhos[indice];
  }
  p->tipo = 1;
  p->token = tok;
}

TokenType busca(no *raiz, char str[])
{
  int nivel;
  int tam = strlen(str);
  int indice;
  no *p = raiz;

  for (nivel = 0; nivel < tam; nivel++)
  {
    indice = encontra_indice(str[nivel]);
    if (p->filhos[indice] == NULL)
    {
      return ID; // nao achou
    }
    else
    {
      p = p->filhos[indice];
    }
  }

  if (p->tipo == 1)
  {
    return p->token; // achou
  }
  else
  {
    return ID; // nao achou
  }
}

void destroyTrie(no *raiz)
{
  int i;
  if (!raiz)
  {
    return;
  }
  for (i = 0; i < alfabeto; i++)
  {
    destroyTrie(raiz->filhos[i]);
  }
  free(raiz);
}

static char getNextChar(void)
{
  if (!(linepos < bufsize))
  {
    lineno++;
    if (fgets(lineBuf, BUFLEN - 1, source_file))
    {
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    {
      EOF_flag = 1;
      return EOF;
    }
  }

  return lineBuf[linepos++];
}

static void ungetNextChar(void)
{
  if (!EOF_flag)
  {
    linepos--;
  }
  else
  {
    lineno--;
  }
}

void resetLexema()
{
  int i;
  for (i = 0; i < MAXTOKENLEN + 1; i++)
  {
    tokenString[i] = '\0';
  }
}

void printToken(TokenType token, const char *tokenString)
{
  switch (token)
  {
  case ELSE:
  case IF:
  case INT:
  case RETURN:
  case VOID:
  case WHILE:
    printf("reserved word: %s\n", tokenString);
    break;
  case PLUS:
    printf("+\n");
    break;
  case MINUS:
    printf("-\n");
    break;
  case TIMES:
    printf("*\n");
    break;
  case OVER:
    printf("/\n");
    break;
  case LT:
    printf("<\n");
    break;
  case LTE:
    printf("<=\n");
    break;
  case GT:
    printf(">\n");
    break;
  case GTE:
    printf(">=\n");
    break;
  case EQ:
    printf("==\n");
    break;
  case NEQ:
    printf("!=\n");
    break;
  case ASSIGN:
    printf("=\n");
    break;
  case SEMI:
    printf(";\n");
    break;
  case COMMA:
    printf(",\n");
    break;
  case LPAREN:
    printf("(\n");
    break;
  case RPAREN:
    printf(")\n");
    break;
  case LBRACKET:
    printf("[\n");
    break;
  case RBRACKET:
    printf("]\n");
    break;
  case LBRACE:
    printf("{\n");
    break;
  case RBRACE:
    printf("}\n");
    break;
  case ENDFILE:
    printf("EOF\n");
    break;
  case NUM:
    printf("NUM, val= %s\n", tokenString);
    break;
  case ID:
    printf("ID, name= %s\n", tokenString);
    break;
  case ERROR:
    printf("ERRO LEXICO: %s LINHA %i\n", tokenString, lineno);
    break;
  default:
    printf("Unknown token: %d\n", token);
  }
}

static TokenType reservedLookup(char *s)
{
  TokenType token;
  token = busca(raiz_trie, s);
  return token;
}

static int T[17][10] = { // tabela transição dos estados
    {1, 2, 0, 15, 15, 3, 7, 4, 9, 11},
    {1, 16, 15, 15, 15, 15, 15, 15, 15, 15},
    {16, 2, 15, 15, 15, 15, 15, 15, 15, 15},
    {15, 15, 15, 15, 15, 15, 5, 15, 15, 15},
    {15, 15, 15, 15, 15, 15, 6, 15, 15, 15},
    {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
    },
    {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
    },
    {15, 15, 15, 15, 15, 15, 8, 15, 15, 15},
    {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
    },
    {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        10,
        -1,
        -1,
        -1,
    },
    {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
    },
    {15, 15, 15, 12, 15, 15, 15, 15, 15, 15},
    {12, 12, 12, 13, 12, 12, 12, 12, 12, 12},
    {12, 12, 12, 12, 12, 12, 12, 12, 12, 14},
    {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
    },
    {
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
    }

};

static int consome[17][10] = {
    // tabela de avança
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, 1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

static int aceita[16] = {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1};

int entrada(char c)
{
  if (isdigit(c))
  {
    return 0;
  }
  else if (isalnum(c))
  {
    return 1;
  }
  else if (c == ' ' || c == '\t' || c == '\n')
  {
    return 2;
  }
  else if (c == '*')
  {
    return 3;
  }
  else if (c == '+' || c == '-' || c == ';' || c == ',' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
  {
    return 4;
  }
  else if (c == '<')
  {
    return 5;
  }
  else if (c == '=')
  {
    return 6;
  }
  else if (c == '>')
  {
    return 7;
  }
  else if (c == '!')
  {
    return 8;
  }
  else if (c == '/')
  {
    return 9;
  }
  else if (c == EOF)
  {
    return 10;
  }
  else
  {
    printf("\n ERRO na funcao entrada \n");
    return -1;
  }
}

TokenType getToken(void)
{
  int tokenStringIndex = 0;
  TokenType currentToken;
  int save;
  char c;
  int estado = 0;
  int fim = 0;
  int flag_unget = 0;
  int estado_antigo = 0;
  resetLexema(); // deixa o lexema zerado
  while (aceita[estado] == 0 && fim == 0)
  {
    flag_unget = 0;
    c = getNextChar();
    save = 1;
    if (consome[estado][entrada(c)] != 1)
    {
      flag_unget = 1;
    }

    if (entrada(c) != -1 && entrada(c) != 10)
    {
      estado = T[estado][entrada(c)];
      if (estado == -1)
      {
        currentToken = ERROR;
        fim = 1;
      }
    }

    if (entrada(c) == 2)
    {
      save = 0;
    }

    if (entrada(c) == 10)
    {
      currentToken = ENDFILE;
      fim = 1;
    }
    if (flag_unget == 1)
    {
      ungetNextChar();
    }

    switch (estado)
    {
    case 0:
      // start
      break;
    case 1:
      currentToken = NUM;
      break;
    case 2:
      currentToken = ID;
      break;
    case 3:
      currentToken = LT;
      break;
    case 4:
      currentToken = GT;
    case 5:
      currentToken = LTE;
      break;
    case 6:
      currentToken = GTE;
      break;
    case 7:
      currentToken = ASSIGN;
      break;
    case 8:
      currentToken = EQ;
      break;
    case 9:
      currentToken = ERROR;
      break;
    case 10:
      currentToken = NEQ;
      break;
    case 11:
      currentToken = OVER;
      break;
    case 12:
      // /*
      save = 0;
      break;
    case 13:
      // /* coment
      save = 0;
      break;
    case 14:
      estado = 0; // sai do comentario e recomeca
      save = 0;
      resetLexema();
      tokenStringIndex = 0;
      break;
    case 15:
      if (currentToken == ID)
      {
        currentToken = reservedLookup(tokenString);
      }
      save = 0;
      if (estado_antigo == 0)
      {
        save = 1;
        switch (c)
        {
        case '+':
          currentToken = PLUS;
          break;
        case '-':
          currentToken = MINUS;
          break;
        case '*':
          currentToken = TIMES;
          break;
        case ';':
          currentToken = SEMI;
          break;
        case ',':
          currentToken = COMMA;
          break;
        case '(':
          currentToken = LPAREN;
          break;
        case ')':
          currentToken = RPAREN;
          break;
        case '[':
          currentToken = LBRACKET;
          break;
        case ']':
          currentToken = RBRACKET;
          break;
        case '{':
          currentToken = LBRACE;
          break;
        case '}':
          currentToken = RBRACE;
          break;
        default:
          break;
        }
      }
      break;
    case 16:
      currentToken = ERROR;
      fim = 1;
      break;
    default:

      break;
    }
    estado_antigo = estado;

    if (save && (tokenStringIndex <= MAXTOKENLEN))
    {
      tokenString[tokenStringIndex] = c;
      tokenStringIndex++;
    }
  }

  printToken(currentToken, tokenString);

  return currentToken;
}
