# BigFloat — Biblioteca numérica de Precisão Arbitrária em C 

**BigFloat** é uma biblioteca escrita em C  para manipulação, comparação e aritmética de números reais de precisão arbitrária, projetada para superar as limitações de *overflow* e perda de precisão dos tipos primitivos nativos (`double`, `uint64_t`).

---

## Destaques Arquiteturais

* **Representação em Base $10^9$:** A mantissa é armazenada em um vetor dinâmico de blocos de 32 bits (`uint32_t` / `limb_t`), onde cada posição comporta até 9 dígitos decimais, maximizando a densidade de memória e utilizando `uint64_t` / `int64_t` para evitar *overflow* em cálculos intermediários.
* **Validação Estrita:** A conversão de entradas textuais (`string_para_bf`) realiza uma varredura preliminar que rejeita imediatamente formatos corrompidos antes de qualquer alocação ou mutação de estado, garantindo atomicidade.
* **Comparação Posicional em $O(1)$ de Espaço:** O módulo `comparacao_bf` compara números de diferentes escalas e expoentes calculando a posição virtual de cada dígito (`posicao_digito_bf`) sem precisar alocar memória extra para alinhar casas decimais.
* **Entrada/Saida Agnóstico em Memória $O(1)$:** A exportação de dados (`imprimir_bf`) opera sobre fluxos genéricos (`FILE *`), permitindo a escrita direta no terminal (`stdout`) ou em arquivos sem construir *strings* intermediárias na RAM.

---

## Estrutura do Projeto

```text
.
├── app/
│   └── main.c                         # Aplicação cliente demonstrando o uso da biblioteca
├── include/
│   ├── gerenciamento_de_memoria_bf.h  # Definição da struct BigFloat e ciclo de vida
│   ├── entrada_e_saida.h              # Conversão de strings e impressão em streams
│   ├── comparacao_bf.h                # Comparação com/sem sinal, validação e checagem de zero
│   └── bf_aritmetico.h                # Operações de soma, subtração, multiplicação e divisão
├── src/
│   ├── gerenciamento_de_memoria_bf.c  # Implementação da alocação e liberação na Heap
│   ├── entrada_e_saida.c              # Implementação da validação, I/O
│   ├── comparacao_bf.c                # Implementação das rotinas de comparação
│   └── bf_aritmetico.c                # Implementação dos algoritmos aritméticos em base 10^9
├── tests/
│   ├── main.c                         # Orquestrador central da bateria de testes (Test Runner)
│   └── test_*.c                       # Testes unitários modulares com <assert.h> e tmpfile()
└── Makefile                           # Automação de build, testes e instalação
```

*(Nota: Os diretórios `obj/`, `libs/` e `bin/` são gerados automaticamente durante a compilação).*

---

## Resumo da API Pública

### 1. Gerenciamento de Memória (`gerenciamento_de_memoria_bf.h`)

* `bool inicializar_bf(BigFloat *bf)`: Inicializa os metadados e pré-aloca a mantissa inicial.
* `void liberar_bf(BigFloat *bf)`: Libera o vetor da mantissa na *Heap* e zera os metadados da *struct*.

### 2. Entrada e Saída (`entrada_e_saida.h`)

* `bool string_para_bf(BigFloat *destino, const char *string)`: Converte uma *string* numérica validada para a base $10^9$.
* `void imprimir_bf(FILE *stream, const BigFloat *bf)`: Imprime o número formatado no fluxo especificado (`stdout` ou arquivo).

### 3. Comparação e Validação (`comparacao_bf.h`)

* `int comparar_bf(const BigFloat *bf1, const BigFloat *bf2)`: Retorna `-1` se `bf1 < bf2`, `0` se `bf1 == bf2`, `1` se `bf1 > bf2`, ou `BF_CMP_ERRO` (`2`) se inválido.
* `int comparar_modulo_bf(const BigFloat *bf1, const BigFloat *bf2)`: Compara os valores absolutos (`|bf1|` e `|bf2|`).
* `bool bf_e_zero(const BigFloat *bf)`: Verifica se o número vale zero (incluindo `-0`).
* `bool bf_e_negativo(const BigFloat *bf)`: Verifica se o número é estritamente menor que zero.
* `bool bf_verificar_bigfloat_valido(const BigFloat *bf)`: Valida a integridade estrutural do ponteiro e da mantissa.

### 4. Operações Aritméticas (`bf_aritmetico.h`)

* `BigFloat *bf_somar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois)`: Aloca e retorna um novo `BigFloat` com a soma.
* `BigFloat *bf_subtrair(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois)`: Aloca e retorna um novo `BigFloat` com a diferença.
* `BigFloat *bf_multiplicar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois)`: Aloca e retorna um novo `BigFloat` com o produto.
* `BigFloat *bf_dividir(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois, size_t casasDecimais)`: Aloca e retorna o quociente com a precisão decimal especificada.

---

## Como Compilar e Executar

O projeto utiliza o `Make` com compilação incremental e flags rigorosas (`-fPIC -Wall -Wextra -Werror`).

### 1. Compilar tudo (Bibliotecas e Executáveis)

Gera a biblioteca estática (`libs/libbf.a`), a biblioteca dinâmica (`libs/libbf.so`) e ambas as versões da aplicação cliente:

```bash
make
```

### 2. Executar a Aplicação Cliente

Para rodar o executável compilado com **ligação estática** (`bin/calculadora_bf_estatica`):

```bash
make run
```

Para rodar o executável compilado com **ligação dinâmica** (`bin/calculadora_bf_dinamica`), configurando automaticamente o `LD_LIBRARY_PATH` em tempo de execução:

```bash
make run_dynamic
```

### 3. Executar a Bateria de Testes Unitários

Compila o *Test Runner* (`bin/test_runner`) contra a biblioteca estática e executa todas as validações automatizadas:

```bash
make test
```

### 4. Instalação da Biblioteca (`install`)

Instala os cabeçalhos (`.h`) e os binários (`.a` e `.so`) nos diretórios `include/` e `lib/` definidos por `PREFIX` (padrão `/usr/local`), permitindo instalação sem privilégios administrativos:

```bash
make install PREFIX=$HOME/.local
```

### 5. Limpeza dos Artefatos de Build

Remove todos os diretórios gerados na compilação (`obj/`, `bin/` e `libs/`):

```bash
make clean
```

---

## Exemplo de Uso (`app/main.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento_de_memoria_bf.h"
#include "entrada_e_saida.h"
#include "comparacao_bf.h"
#include "bf_aritmetico.h"

int main() {
    // 1. Declaração das variáveis de entrada na Stack
    BigFloat numero_a, numero_b;
    const char* str_a = "-83156898747988.6482966126441861";
    const char* str_b = "12345678901234.55";

    // 2. Inicialização segura
    if (!inicializar_bf(&numero_a) || !inicializar_bf(&numero_b)) {
        printf("Falha ao inicializar os BigFloats.\n");
        return 1;
    }

    // 3. Injeção e validação de dados (Fail-Fast)
    if (!string_para_bf(&numero_a, str_a) || !string_para_bf(&numero_b, str_b)) {
        printf("String invalida!\n");
        liberar_bf(&numero_a);
        liberar_bf(&numero_b);
        return 1;
    }

    // 4. Comparação e Processamento Aritmético
    int cmp = comparar_bf(&numero_a, &numero_b);
    if (cmp != BF_CMP_ERRO) {
        printf("Comparacao (A vs B): %d\n", cmp);
    }

    BigFloat *resultado_soma = bf_somar(&numero_a, &numero_b);
    if (resultado_soma == NULL) {
        printf("Erro ao realizar a soma.\n");
        liberar_bf(&numero_a);
        liberar_bf(&numero_b);
        return 1;
    }

    // 5. Exportação de dados (Terminal e Arquivo)
    printf("Resultado no terminal: ");
    imprimir_bf(stdout, resultado_soma);

    FILE *saida = fopen("resultado.txt", "w"); // "w" = write
    if (saida != NULL) {
        imprimir_bf(saida, resultado_soma);
        fclose(saida);
    }

    // 6. Liberação de memória
    liberar_bf(&numero_a);
    liberar_bf(&numero_b);
  
    // Para resultados alocados pelas funções aritméticas, libera-se a mantissa e a struct:
    liberar_bf(resultado_soma);
    free(resultado_soma);

    return 0;
}
```
