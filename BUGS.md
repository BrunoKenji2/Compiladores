# BUGS.md — Compilador C-

Auditoria estática de `lex.l`, `parser.y`, `semantic.c`, `symtab.c`, `util.c`, `pilha.c`,
`intermediario.c`, `assembler.c`, `binario.c`, comparados com o hardware alvo em
`../ProcessadorMips`.

Não foi possível compilar nem executar (sem gcc/flex/bison/make nesta máquina). As reproduções
marcadas com ✔ foram confirmadas contra os artefatos versionados (`binarios/*.bin`, `saidas/`,
`NOTES.txt`, `Controle.v`); as demais vêm de leitura do código.

**Resumo:** 6 críticos · 11 altos · 15 médios. **1 corrigido** (B-06).

**Corrigidos até agora:** B-06 (`HALT` no fim do `main`) — ver o item para o que ficou pendente.

---

## Críticos

### B-01 — `>`, `>=` e `!=` não geram nenhuma instrução

**Onde:** `assembler.c:585-601` (sgt), `assembler.c:617-632` (sdt), `assembler.c:685-700` (sget)

`verificaOp()` (`intermediario.c:45-81`) mapeia `MAI`→`sgt`, `MAIGL`→`sget`, `DIF`→`sdt`, e
`geraCodigoExp` emite as quádruplas normalmente. Mas os três blocos correspondentes no assembler
estão **comentados**. O laço principal não tem `default`, então a quádrupla é descartada em silêncio
e o registrador de destino segue com lixo — o `iff` seguinte ramifica sobre valor indefinido.

Dos seis operadores relacionais da linguagem, só `<`, `<=` e `==` funcionam.

**Repro ✔:** `entradas/maiorArray.txt` usa `numeros[i] > maior` e é o **único** teste de `entradas/`
ausente da lista de programas funcionais do `NOTES.txt`.

**Correção:** descomentar os três blocos e (a) corrigir os opcodes de `SGT`/`SGTI` em `binario.c`,
hoje `""` (B-14), e (b) `SGET`/`SDT`, hoje colidindo com `MFLO`/`JR` (B-15). Alternativa mais barata
e sem tocar no hardware: reescrever no gerador intermediário — `a > b` → `slt b, a`;
`a >= b` → `slet b, a`; `a != b` → `set` seguido de inversão.

---

### B-02 — `solicitaReg()` aloca registradores que aliasam `$aux`, `$fp`, `$sp` e `$ra`

**Onde:** `intermediario.c:138-153` vs. `assembler.h:55-60` / `assembler.c:134-202`

`regs[]` tem 32 slots e `solicitaReg()` produz nomes de `$t0` até `$t31`. Mas `pegaRegistrador()`
mapeia:

| Nome gerado | Vira |
|---|---|
| `$t26` | `$aux` (scratch do assembler) |
| `$t27` | **`99`** — índice inválido |
| `$t28` | `$fp` |
| `$t29` | `$sp` |
| `$t30` | `$ra` |
| `$t31` | **`99`** — índice inválido |

Ou seja: só `$t0..$t25` são seguros. A partir do 27º temporário vivo, o compilador emite instruções
que sobrescrevem o frame pointer, o stack pointer e o endereço de retorno — sem nenhum aviso. E o
`99` é usado depois como índice em `ListaRegStr[99]` (`assembler.c:937-941`), leitura fora dos
limites do array de 32 posições.

**Correção:** limitar o laço de `solicitaReg()` a 26 (`i < 26`) e trocar o `printf` de
"Registradores insuficientes" por erro fatal — hoje ele retorna `NULL`, que é desreferenciado em
`intermediario.c:436` sem checagem em vários pontos.

---

### B-03 — `MULTI` é codificado como o opcode de `OR`

**Onde:** `binario.c:139-140`

```c
}else if(ins->inst == MULTI){ strcpy(opcode,"000101"); }
```

`000101` é **OR** em `Controle.v:129` (a multiplicação por imediato não existe no hardware). Qualquer
`x * constante` vira um OR bit a bit.

`MULTI` é emitido por `assembler.c:453-461` sempre que um operando de `*` é literal. Não aparece nos
`.bin` versionados ✔ (nenhum dos programas validados multiplica por constante), o que explica por que
nunca foi notado.

**Correção:** materializar o imediato em `$aux` com `ADDI` e usar `MULT` tipo-R — mesmo padrão já
aplicado a `slt` (`assembler.c:572-580`) e `set` (`assembler.c:641-651`).

---

### B-04 — Vetor local com tamanho > 0 causa segfault no compilador

**Onde:** `assembler.c:789`

```c
insereInstI(SW,$sp,$zero,0);   // 4º parâmetro é char*, não int
```

O literal `0` converte para ponteiro nulo; `insereInstI` faz `strlen(imediato)` em `assembler.c:88`.
Todas as outras 40+ chamadas passam `"0"`.

Dispara ao declarar `int v[10];` dentro de uma função. Nenhum programa de `entradas/` faz isso —
`sort.txt` e `maiorArray.txt` declaram o vetor globalmente.

**Correção:** `insereInstI(SW,$sp,$zero,"0");`

---

### B-05 — Condição constante em `if`/`while` causa segfault

**Onde:** `assembler.c:469`

```c
if(q->op == iff){
    insereInstI(BEQ,pegaRegistrador(q->arg1.conteudo.nome),$zero,q->arg2.conteudo.nome);
}
```

Não há teste de `q->arg1.type`. Para `if (1)` ou `while (1)`, `geraCodigoExp` case `ConstK` deixa
`aux.type = Const` (`intermediario.c:442-445`), e o `int` da union é lido como `char*` e passado a
`strcmp`.

**Correção:** se `arg1.type == Const`, emitir `ADDI $zero,$aux,<val>` antes do `BEQ` sobre `$aux` —
mesmo padrão de `slt`/`set`.

---

### B-06 — `HALT` nunca é emitido; a execução cai no fim da ROM — ✅ **CORRIGIDO**

> **Corrigido.** `assembler.c` passou a emitir `HALT` no `endF` do `main` e `binario.c` ganhou o
> caso do opcode `011110`. Os 10 binários foram regenerados (652 → 662 instruções, exatamente uma
> a mais por programa) e `sim/run.sh todos` passa com as mesmas saídas e contagens de ciclo,
> terminando por `FIM: HALT`.
>
> ⚠️ **Só vale em simulação por enquanto.** O `HALT` do hardware não para de verdade com o botão
> pressionado — ver **H-04** no `../ProcessadorMips/BUGS.md`, que continua aberto. Na placa o
> programa ainda reinicia; o que mudou é que agora existe uma instrução explícita de parada para o
> hardware honrar quando H-04 for corrigido.
>
> Falta ainda o outro lado: quando existir o SO, o `endF` do `main` terá de escolher entre `HALT`
> (standalone) e `JR $ra` (rodando sob o SO), e o `main` precisará de prólogo para salvar o `$ra`
> que o SO deixou. O `else` criado em `assembler.c` é o ponto onde essa decisão entra.

O registro original, para contexto:

**Onde:** `assembler.c` (nenhum sítio), `assembler.h:47`, `Controle.v:636`

O enum tem `HALT`, o hardware decodifica `011110`, mas **nenhum caminho do assembler o insere**.
`endF` (`assembler.c:722-733`) é guardado por `if(strcmp("main", ...))`, então `main` não recebe nem
epílogo nem parada. Terminado o `main`, o PC continua avançando por posições não inicializadas da
ROM.

**Confirmado ✔:** o opcode `011110` não aparecia em nenhuma das 652 linhas de `binarios/*.bin`.

**Correção aplicada:** `HALT` emitido no `endF` de `main`.

---

## Altos

### B-07 — `liberaRegs("$rf")` libera `$t0` por engano

**Onde:** `intermediario.c:126-136`

A função extrai o número do registrador sobrescrevendo os dois primeiros caracteres por `'0'`:
`"$t5"` → `"005"` → `atoi` → 5. Mas para `"$rf"` → `"00f"` → `atoi` → **0**, marcando `$t0` como
livre.

Acontece em toda atribuição do retorno de função: `x = f()` gera `storeVar` com `arg1 = "$rf"`, e
`insereQuad` chama `liberaRegs` para `storeVar` (`intermediario.c:119-122`). Se `$t0` estiver vivo,
ele é realocado e sobrescrito.

Além disso a função faz `malloc(strlen(r))` + `strcpy` (B-18) e nunca libera `r`.

**Correção:** retornar cedo se a string não casar com `"$t%d"` (`sscanf(reg, "$t%d", &i) == 1`).

---

### B-08 — `criaEscopo()` deixa `variaveis` não inicializado

**Onde:** `assembler.c:237-243`

Inicializa `nome` e `prox`, mas não `variaveis` — que é lido logo depois em `assembler.c:283`
(`variavel * aux = escopo->variaveis;`) e comparado a `NULL`. `malloc` não zera.

Funciona hoje porque o glibc devolve páginas zeradas em alocações novas; qualquer reuso de arena
transforma isso em corrupção do mapa de memória.

**Correção:** `novo->variaveis = NULL;` (ou `calloc`).

---

### B-09 — `cria_label()`: `strcat` em buffer não inicializado + tamanho errado

**Onde:** `intermediario.c:156-166`

```c
char* lab = malloc((quantLabel%10 + 2)*sizeof(char));
...
lab[0] = 'L';
strcat(lab, n);
```

Dois problemas: (a) `strcat` procura o terminador em memória não inicializada, então escreve em
offset arbitrário — não em `lab[1]`; (b) `quantLabel % 10` é um cálculo sem sentido para número de
dígitos — com `quantLabel = 10` aloca 2 bytes para `"L10\0"` (4).

**Correção:** `char *lab = malloc(16); sprintf(lab, "L%d", quantLabel++);`

---

### B-10 — Leitura fora dos limites em `solicitaReg()`

**Onde:** `intermediario.c:141`

```c
while(regs[i] != 0 && i < 32){ i++; }
```

Condições invertidas: quando `i` chega a 32, `regs[32]` é lido **antes** do teste de limite.

**Correção:** `while(i < 32 && regs[i] != 0)`. Com B-02, o limite passa a ser 26.

---

### B-11 — Registradores não são salvos nas chamadas de função

**Onde:** `assembler.c:868-890`

`empilhaReg()`/`desempilhaReg()` (`intermediario.c:18-42`) geram corretamente quads `empilha` e
`desempilha` ao redor de cada `call`, mas **os dois manipuladores no assembler têm o corpo inteiro
comentado**. As quádruplas são consumidas e descartadas.

Consequência: qualquer temporário vivo durante uma chamada é destruído pelo callee. É exatamente o
"Recursividade falta implementar salvar o contexto" do `NOTES.txt`. `gcd` funciona por sorte de
alocação.

**Correção:** implementar como `SW $sp,$tN,0` + `ADDI $sp,$sp,1` (empilha) e o inverso (desempilha),
lembrando que o intermediário já emite na ordem LIFO correta (0→31 empilhando, 31→0 desempilhando).

---

### B-12 — Declaração local dentro de laço realoca a cada iteração

**Onde:** `intermediario.c:287-298` + `assembler.c:740-769`

Não há escopo de bloco: `insereEscopo` (`util.c:47`) marca toda a subárvore da função com o mesmo
escopo. Uma declaração dentro do corpo de um `while` gera a quádrupla `allocaMemVar` **dentro do
laço**, que vira `ADDI $sp,$sp,1` executado a cada iteração. O `$sp` cresce sem retorno.

**Repro ✔:** `entradas/sort.txt` declara `int t;` dentro do `while` de `sort()`. Com `high = 5` são 4
iterações → `$sp` avança 4 words a mais, numa RAM de 64.

**Correção:** içar as declarações locais para o prólogo da função na fase intermediária.

---

### B-13 — Imediatos negativos são codificados como zero

**Onde:** `binario.c:12-33`

```c
while (numero > 0 && i >= 0) { ... }
```

Negativos saem como todos os bits zero. O caso concreto: `pegaPosMemoria()` retorna **`-1`** quando
não encontra a variável (`assembler.c:329`), e esse `-1` é formatado como imediato de `LW`/`SW`
(`assembler.c:809,813,852,856`). Uma variável não encontrada vira acesso ao endereço 0 em vez de um
erro.

**Correção:** codificar em complemento de dois no tamanho do campo, e transformar o `-1` de
`pegaPosMemoria` em erro fatal.

---

### B-14 — `SGT` e `SGTI` recebem opcode vazio

**Onde:** `binario.c:81-83` e `binario.c:149-150`

`strcpy(opcode, "")` produz uma linha binária com menos de 32 bits, que desalinha toda a carga da
ROM a partir dali. Hoje inerte porque B-01 impede a geração dessas instruções — mas será a primeira
coisa a explodir ao corrigir B-01.

**Confirmado ✔:** as 662 linhas de `binarios/*.bin` têm exatamente 32 caracteres.

---

### B-15 — Divergências de opcode entre `binario.c` e `Controle.v`

**Onde:** `binario.c:59-177` vs. `Controle.v:27-793`

Além de B-03 e B-16, dez mnemônicos apontam para opcodes que o hardware interpreta como outra coisa:

| Compilador | Opcode | Hardware executa |
|---|---|---|
| `SGET` / `ANDI` / `SGETI` | `001010` | `MFLO` |
| `SDT` / `ORI` / `SDTI` | `001100` | `JR` |
| `SLL` / `MODI` | `001101` | `JALR` |
| `SRL` / `BLTZ` | `001110` | `LA` |
| `MOD` / `BGTZ` | `001111` | `ADDI` |
| `SLTI` | `000111` | `SRL` |
| `BEQZ` | `010111` | `BLT` |
| `BNE` | `011000` | `SLET` |
| `LUI` | `010101` | `BGT` |
| `SETI` | `001011` | `MOVE` |

Nenhum é emitido hoje, mas a tabela é uma armadilha para quem for adicionar suporte a qualquer um.
Note também as colisões internas: `ANDI`/`SGET`/`SGETI` compartilham `001010`, e `SDT`/`ORI`/`SDTI`
compartilham `001100` — o hardware não teria como distingui-los (o campo `funct` é `"000"` fixo).

**Correção:** regenerar a tabela a partir de `Controle.v` e adicionar um `default` que aborte com
erro em vez de emitir opcode desconhecido.

---

### B-16 — `setLcd` não existe no hardware

**Onde:** `binario.c:213-221`, `assembler.c:490-493`, `intermediario.c` / `semantic.c:59`

O compilador emite `SETLCD` com opcode `100110`. `Controle.v` decodifica no máximo `100101`, então a
instrução cai no `default` — que deixa `controleULA`, `controleImediato`, `controleWriteRegs`,
`controleMemWrite`, `controleJump` e `controleBranch` todos em `X`. **Não há nenhuma referência a LCD
em `../ProcessadorMips`** ✔ (`grep -il lcd *.v` não retorna nada).

O último commit do compilador é "display lcd"; o processador não recebeu a contraparte.

**Repro ✔:** `entradas/so.txt`; `saidas/binario.txt` contém `10011000000000000000000000001010`.

**Correção:** implementar o opcode `100110` em `Controle.v` + módulo de LCD, ou remover `setLcd` do
compilador até que o hardware exista.

---

### B-17 — Scanner de comentários termina cedo e pode entrar em laço infinito

**Onde:** `lex.l:43-61`

```c
}else{
  flag == 0;    // comparação, não atribuição — o reset nunca acontece
}
```

Depois de ver um `*`, `flag` fica em 1 permanentemente, então **a primeira `/` seguinte fecha o
comentário**, mesmo separada por outros caracteres. `/* a*b/c */` termina no `/` de `b/c`, e
`c */` passa a ser lexado como código.

Nenhum teste de `entradas/` dispara isso hoje ✔ — todos os comentários com `*` e `/` têm a `/`
antes (ex.: `gcd.txt`, `/* u-u/v*v == u mod v */`, onde `flag` ainda é 0 na `/` de `u/v`). É um
bug latente, não uma falha ativa.

Dois problemas secundários no mesmo bloco: `char c = input()` comparado a `EOF` nunca casa se `char`
for unsigned na plataforma; e comentário não fechado gera laço infinito porque `flag` nunca chega a
2.

**Correção:** `flag = 0;` no `else`, `int c` em vez de `char c`, e tratar `c == 0` além de `EOF`.

---

## Médios

### B-18 — `malloc(strlen(s))` sem `+1`, seguido de `strcpy` — ~30 ocorrências

**Onde:** `intermediario.c` (~20 sítios), `assembler.c:37,45,78,88,207,239,258,491,499`, `pilha.c:14`

Estouro de 1 byte no heap em cada uma. `insereInstLcd` (`assembler.c:125`) é a **única** ocorrência
correta do arquivo — use-a como referência.

Igualmente perigoso é o efeito de contágio: quem copiar qualquer bloco existente propaga o bug.

**Correção:** varredura mecânica trocando por `strlen(s) + 1`, ou substituir tudo por `copyString()`
(`util.c:64`), que já faz o certo.

---

### B-19 — Segfault em programa composto só de declarações globais

**Onde:** `assembler.c:338-386`

O laço `while(flagAlocGlobal == 1)` desreferencia `q->op` sem checar `q != NULL`. Se as quádruplas
acabarem durante a alocação de globais (programa sem função alguma), `q` chega a `NULL`.

**Correção:** `while(q != NULL && flagAlocGlobal == 1)`.

---

### B-20 — `pegaPosMemoria()` não checa escopo inexistente

**Onde:** `assembler.c:319-330`

```c
escopos * escopo = procuraEscopo(nomeEscopo);
variavel * aux = escopo->variaveis;   // escopo pode ser NULL
```

Hoje protegido por acidente: `fun` sempre registra `$ra`/`$fp` no escopo da função, e o escopo
`global` é criado pela primeira variável global. Some a proteção em programas sem globais.

---

### B-21 — Erros semânticos não abortam a compilação

**Onde:** `main.c:17`, `semantic.c` (todos os sítios), `parser.y:381-392`

`unsigned char error` é declarado em `main.c:17` e **nunca lido nem escrito**. `insertNode()` só faz
`printf` em cada erro. `main()` retorna `0` incondicionalmente. `yyerror` chama `exit(0)` — código de
sucesso — em erro léxico (`parser.y:385`).

Resultado: um programa com variável não declarada gera assembly e binário, e nenhum script ou CI
consegue detectar a falha pelo exit code.

**Correção:** flag global incrementada em cada erro; abortar antes de `gerarIntermediario`; retornar
`1`.

---

### B-22 — Verificações semânticas ausentes

**Onde:** `semantic.c`

Não são checados: aridade da chamada vs. parâmetros declarados; tipo de retorno vs. tipo da função;
`return` com valor em função `void` (e vice-versa); tipo do índice de vetor; uso de função `void` em
expressão; vetor usado como escalar e escalar indexado; divisão por zero literal.

`verifica_main()` (`semantic.c:121-125`) só testa a existência de `main`, não a assinatura
(`void main(void)`) nem a exigência do C- de ser a última declaração.

---

### B-23 — Tabela de símbolos: busca ignora o escopo

**Onde:** `symtab.c:44-113`

A chave hash é `nome + escopo`, mas a varredura do bucket compara **só `nome`**
(`symtab.c:53,88,105`). Em colisão de bucket entre nomes iguais de escopos diferentes, `lookup()`
retorna falso positivo — uma variável de outra função é dada como declarada.

Dois problemas adicionais na mesma função: `cel->nome = nome` guarda o ponteiro **sem copiar**
(alias da AST) enquanto `escopo` é copiado com `copyString` — assimetria que vira ponteiro pendurado
se a árvore for liberada; e `char nomeConcat[100]` recebe `strcpy`+`strcat` sem limite
(`MAXTOKENLEN` é 40, então hoje não estoura, mas nada garante isso).

**Correção:** comparar `nome` **e** `escopo` nas três funções; usar `copyString` para `nome`;
`snprintf` para `nomeConcat`.

---

### B-24 — Ordem de resolução de escopo inconsistente entre variável e vetor

**Onde:** `semantic.c:89-110`

`VarIdK` consulta `"global"` **antes** do escopo local; `VetIdK` faz o inverso. Combinado com
`insertNode` rejeitando local que sombreia global (`semantic.c:20,37`), o comportamento com nomes
repetidos é imprevisível.

**Correção:** escolher uma ordem (local → global é o esperado) e aplicar nos dois.

---

### B-25 — Leitura do membro errado da union e `case` sem `break`

**Onde:** `semantic.c:64-80`

```c
if(t->filho[1]->kind.stmt == CallK && t->filho[1]->nodeKind == 0)
```

`kind` é uma union: `kind.stmt` é lido **antes** de validar que o nó é `StmtK`. Ordem invertida.
O `case AssignK` também não tem `break` — hoje inofensivo porque `default: break;` vem logo depois,
mas quebra ao inserir qualquer `case` no meio.

---

### B-26 — Arquivos nunca são fechados e `fopen` não é checado

**Onde:** `binario.c:229`, `assembler.c:922`, `intermediario.c:540`, `util.c:267`

Nenhum `fclose()` no projeto inteiro. `fopen` sem checagem de `NULL` em `geraBinario`,
`imprimeInstrucoes` e `imprimeIntemediario` — rodar de outro diretório grava em ponteiro nulo.
`imprimeIntemediario` retorna cedo quando não há quads, deixando o arquivo criado e vazado.

`converteInst()` (`binario.c:35-43`) vaza 8 blocos por instrução, mais os de `decimalParaBinario`.

---

### B-27 — `strcat` em buffer não inicializado no ramo `INPUT`

**Onde:** `binario.c:190-200`

```c
strcpy(opcode,"100010");
strcat(binario,opcode);   // binario nunca foi inicializado
```

O ramo `OUTPUT`, logo abaixo, usa `strcpy` primeiro — está correto. Mesma classe de UB de B-08/B-09.

Além disso a ordem dos campos difere entre os dois: `INPUT` emite `opcode|rt|rt|rs|00000000`
(registrador no 3º campo) e `OUTPUT` emite `opcode|rs|rt|imediato` (registrador no 1º). Vale
confirmar contra o datapath qual é a correta.

**Correção:** `strcpy(binario, opcode);` e depois os `strcat`.

---

### B-28 — Todo `input()` ecoa o valor lido

**Onde:** `assembler.c:479-481`

```c
insereInstIO(INPUT,$rf);
insereInstIO(OUTPUT,$rf);   // imprime o valor lido
```

O `OUTPUT` parece debug esquecido: todo `x = input()` imprime. Infla a contagem de instruções (que
tem teto de 256) e polui a saída do programa.

---

### B-29 — `verificaOp()` sem `return` no caminho `default`

**Onde:** `intermediario.c:45-81`

Retorno indefinido para qualquer token não relacional/aritmético. O `switch` também usa `break` após
cada `return` (morto).

---

### B-30 — Headers declaram símbolos inexistentes ou `static`

**Onde:** `binario.h:6-7`, `semantic.h:4`

`binario.h` declara `conversorInst()` e `imprimeBinario()`, que não existem — a função real é
`converteInst()`. `semantic.h` declara `static void insertNode(TreeNode*)` **em header**: toda unidade
de tradução que o inclua ganha uma declaração `static` sem definição.

---

### B-31 — `Makefile` esconde todos os avisos

**Onde:** `Makefile:3-7`

`gcc -c *.c` sem `-Wall -Wextra`: os avisos que apontariam B-18, B-29, B-30 e o `flag == 0;` de B-17
(`-Wunused-value`) são todos suprimidos. Sem regras de dependência, `make all` recompila tudo sempre
e `make` nunca considera o alvo atualizado.

`-ll -lfl` linka duas bibliotecas de lex — `-ll` é a variante BSD/macOS, `-lfl` a do flex/Linux.
Em máquina que só tenha uma, o link falha.

**Correção:** adicionar `-Wall -Wextra`, `%option noyywrap` em `lex.l` e remover ambas as libs;
opcionalmente regras por alvo em vez de `*.c`.

---

### B-32 — `noFlex.y` é código morto

**Onde:** `noFlex.y` (724 linhas)

Front-end alternativo com lexer manual em trie, não referenciado pelo `Makefile` nem por nenhum
`#include`. `main.c:33-44,70-75` tem o código de suporte comentado.

**Correção:** remover, ou mover para `docs/historico/` com um README explicando que é uma versão
anterior sem flex.

---

## Nota sobre "mas funciona"

B-08, B-09, B-18 e B-27 são comportamento indefinido que hoje passa despercebido porque o `malloc`
do glibc devolve páginas zeradas em alocações novas. A verificação das 662 linhas de
`binarios/*.bin` mostra todas com exatamente 32 caracteres — ou seja, **o binário atual está correto
por sorte, não por construção**.

Isso importa na prática: qualquer mudança que altere o padrão de alocação (adicionar uma fase,
liberar memória, trocar de plataforma, compilar com outra libc ou com sanitizers) pode quebrar vários
programas de uma vez, com sintomas que não apontam para a causa. Corrigir B-18 primeiro é o que
torna todo o resto depurável.

## Ordem de correção sugerida

1. **B-18** (o `+1` em massa) e **B-08/B-09/B-27** — tirar o compilador do território de UB.
2. **B-31** (`-Wall -Wextra`) — a partir daqui o build passa a apontar regressões sozinho.
3. **B-02** — corretude do código gerado em qualquer programa não trivial.
   (~~B-06~~ feito; para completá-lo em hardware falta o **H-04** do processador.)
4. **B-01** + **B-14** — completar a linguagem; `maiorArray.txt` vira teste de aceitação.
5. **B-04**, **B-05**, **B-19**, **B-20** — parar de derrubar o compilador em entradas válidas.
6. **B-11** e **B-12** — recursão e uso de pilha confiáveis.
7. **B-21** — sem isso, nenhuma suíte de testes automatizada consegue reprovar nada.
