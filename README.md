# Compilador C-

Um compilador completo para a linguagem C- (subconjunto da linguagem C) que realiza análise léxica, sintática, semântica e gera código binário executável.

## 📖 Sobre o Projeto

Este projeto implementa um compilador completo para a linguagem C-, uma versão simplificada da linguagem C. O compilador foi desenvolvido como parte de um projeto acadêmico de Compiladores e realiza todas as fases de compilação:

1. **Análise Léxica** - Tokenização do código fonte
2. **Análise Sintática** - Construção da árvore sintática abstrata (AST)
3. **Análise Semântica** - Verificação de tipos e construção da tabela de símbolos
4. **Geração de Código Intermediário** - Código de três endereços (quadruplas)
5. **Geração de Assembly** - Código assembly MIPS-like
6. **Geração de Código Binário** - Instruções em formato binário

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C
- **Ferramentas:**
  - **Flex** - Gerador de analisadores léxicos
  - **Bison** - Gerador de analisadores sintáticos
  - **GCC** - Compilador para construção do projeto
  - **Make** - Automação da compilação

## 📁 Estrutura do Projeto

```
Compiladores/
├── main.c              # Programa principal
├── lex.l               # Especificação léxica (Flex)
├── parser.y            # Gramática sintática (Bison)
├── globals.h           # Definições globais e tipos
├── scan.h              # Interface do analisador léxico
├── parser.h            # Interface do analisador sintático
├── symtab.c/h          # Tabela de símbolos
├── semantic.c/h        # Análise semântica
├── intermediario.c/h   # Geração de código intermediário
├── assembler.c/h       # Geração de código assembly
├── binario.c/h         # Geração de código binário
├── pilha.c/h           # Estrutura de dados auxiliar
├── util.c/h            # Funções utilitárias
├── Makefile            # Script de compilação
├── entradas/           # Os 10 programas de teste (ver "Testes Inclusos")
├── binarios/           # Binário de referência de cada programa de entradas/
├── saidas/            # Arquivos gerados
│   ├── arvore.txt     # Árvore sintática
│   ├── assembly.txt   # Código assembly
│   ├── binario.txt    # Código binário
│   ├── intermediario.txt # Código intermediário
│   └── tabelaSimbolos.txt # Tabela de símbolos
└── sofs/              # Bitstreams da FPGA (.sof) de gravações antigas na placa
```

## 🚀 Como Usar

### Pré-requisitos

- GCC (GNU Compiler Collection)
- Flex (Fast Lexical Analyzer Generator)
- Bison (GNU Parser Generator)
- Make

### Compilação

```bash
# Clone o repositório
git clone <url-do-repositorio>
cd Compiladores

# Compile o projeto
make all

# Comandos de limpeza
make clean      # Remove arquivos de compilação (mantém saídas)
make clean-all  # Remove tudo incluindo saídas
make rebuild    # Limpa e recompila
```

### Execução

```bash
# Execute o compilador com um arquivo C-
./cmenos entradas/factorial.txt

# O compilador gerará automaticamente os seguintes arquivos:
# - saidas/arvore.txt (árvore sintática)
# - saidas/assembly.txt (código assembly)
# - saidas/binario.txt (código binário)
# - saidas/intermediario.txt (código intermediário)
# - saidas/tabelaSimbolos.txt (tabela de símbolos)
```

### Exemplos de Uso

```bash
# Compilar o fatorial (recursivo)
./cmenos entradas/factorial.txt

# Compilar algoritmo de ordenação
./cmenos entradas/sort.txt

# Compilar programa personalizado
./cmenos meu_programa.c-
```

## 📝 Linguagem C-

A linguagem C- é um subconjunto da linguagem C com as seguintes características:

### Tipos de Dados
- `int` - Números inteiros
- `void` - Tipo vazio (para funções)
- Arrays de inteiros `int[]`

### Estruturas de Controle
- `if` / `else` - Condicionais
- `while` - Laços de repetição
- `return` - Retorno de função

### Operadores
- **Aritméticos:** `+`, `-`, `*`, `/`
- **Relacionais:** `==`, `!=`, `<`, `<=`, `>`, `>=`
- **Atribuição:** `=`

### Funções Especiais
- `input()` - Leitura de entrada
- `output(valor)` - Saída de dados

### Exemplo de Programa C-

```c
/* Programa para calcular o fatorial (entradas/factorial.txt) */
int factorial(int n) {
    int resultF;
    int aux;
    if (n <= 1) {
        return 1;
    } else {
        aux = n - 1;
        resultF = factorial(aux);
        return (n * resultF);
    }
}

void main(void) {
    int number;
    int result;
    number = input();
    result = factorial(number);
    output(result);
}
```

## 🔧 Arquitetura do Compilador

### 1. Análise Léxica (`lex.l`)
- Reconhece tokens da linguagem (palavras-chave, identificadores, números, operadores)
- Trata comentários e espaços em branco
- Gerencia contagem de linhas para relatório de erros

### 2. Análise Sintática (`parser.y`)
- Implementa a gramática da linguagem C-
- Constrói a árvore sintática abstrata (AST)
- Detecta erros de sintaxe

### 3. Análise Semântica (`semantic.c`)
- Verifica compatibilidade de tipos
- Valida declarações e usos de variáveis
- Constrói e gerencia a tabela de símbolos

### 4. Código Intermediário (`intermediario.c`)
- Gera código de três endereços (quadruplas)
- Implementa otimizações básicas
- Gerencia alocação de registradores temporários

### 5. Código Assembly (`assembler.c`)
- Converte código intermediário para assembly MIPS-like
- Gerencia alocação de memória (global e local)
- Implementa convenções de chamada de função

### 6. Código Binário (`binario.c`)
- Converte instruções assembly para formato binário
- Suporta diferentes tipos de instrução (R, I, J)
- Gera arquivo binário executável

## 📊 Arquivos de Saída

### `arvore.txt`
Representação textual da árvore sintática abstrata gerada pela análise sintática.

### `tabelaSimbolos.txt`
Lista de todos os símbolos (variáveis, funções) encontrados no programa com suas informações de escopo e tipo.

### `intermediario.txt`
Código intermediário em formato de quadruplas (operação, arg1, arg2, resultado).

### `assembly.txt`
Código assembly MIPS-like gerado a partir do código intermediário.

### `binario.txt`
Instruções em formato binário de 32 bits, prontas para execução.

## 🧪 Testes Inclusos

O projeto inclui programas de teste na pasta `entradas/`:

| Programa | O que faz |
|---|---|
| `imprime21.txt` | imprime uma constante |
| `areaTriangulo.txt` | área do triângulo (`l*h/2`) |
| `contador.txt` | contagem regressiva de 5 a 1 (sem `input()`) |
| `volume.txt` | volume (`x*y*z`) |
| `factorial.txt` | fatorial recursivo |
| `fibonacciI.txt` | Fibonacci iterativo |
| `primo.txt` | teste de primalidade |
| `maiorArray.txt` | maior de 4 números lidos |
| `buscaArray.txt` | busca num vetor fixo `{10,20,30,40,50}` |
| `sort.txt` | ordenação por seleção de 5 números |

Os binários de referência ficam em `binarios/`. Para validar, rode no WSL
`bash ../ProcessadorMips/sim/run.sh todos`, que executa os 10 no processador simulado.

## 🔧 Manutenção do Projeto

### Limpeza de Arquivos

Para manter o repositório limpo e não versionar arquivos desnecessários:

```bash
# Remove apenas arquivos de compilação (mantém as saídas exemplo)
make clean

# Remove tudo incluindo arquivos de saída
make clean-all

# Limpa e recompila
make rebuild
```

### Arquivos Versionados vs Ignorados

**Versionados (mantidos no git):**
- Código fonte (`.c`, `.h`, `.l`, `.y`)
- Arquivos de entrada (`entradas/`)
- Arquivos de saída exemplo (`saidas/`) - para demonstração
- Documentação (`README.md`)

**Ignorados pelo git:**
- Arquivos objeto (`*.o`)
- Executável (`cmenos`)
- Arquivos gerados pelo Flex/Bison (`lex.yy.c`, `parser.tab.*`)
- Arquivos temporários

## ⚠️ Limitações Conhecidas

- O compilador foi testado principalmente com os algoritmos GCD e Sort
- Algumas funcionalidades de assembly e binário podem estar incompletas para casos mais complexos
- A arquitetura alvo é baseada em MIPS mas com algumas adaptações


## 👨‍💻 Autor

**Bruno Kenji** - [BrunoKenji2](https://github.com/BrunoKenji2)

## 📚 Referências

- Aho, A. V., Sethi, R., & Ullman, J. D. - Compilers: Principles, Techniques, and Tools
- Documentação do Flex e Bison
- Arquitetura MIPS

---

**Nota:** Para executar os programas gerados, você precisará de um simulador apropriado para a arquitetura alvo implementada no compilador.
