#ifndef _gerenciamento_de_memoria_bf_h
#define _gerenciamento_de_memoria_bf_h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint32_t limb_t;

/**
 * @brief Estrutura principal para representar um número de precisão arbitrária.
 * Gerencia o sinal, a magnitude (mantissa) e o controle dinâmico de memória.
 */
typedef struct {
    int sinal;           /**< 1 para positivo, -1 para negativo. */
    long expoente;       /**< Potência da base. */
    size_t tamanho;      /**< Quantidade de blocos limb_t atualmente em uso. */
    size_t capacidade;   /**< Quantidade total de blocos alocados na memória. */
    limb_t *mantissa;    /**< Ponteiro para o array dinâmico que guarda os dígitos. */
  
} BigFLoat;

/**
 * @brief Inicializa e aloca memória para uma nova estrutura BigFLoat.
 * @pre Nenhuma.
 * @post A estrutura BigFLoat é retornada com seus valores zerados/padrão 
 * @warning Se houver falta de memória e o malloc falhar, a função exibirá 
 * uma mensagem de erro fatal e encerrará a execução do programa com exit(1).
 * @return BigFLoat Uma nova instância da estrutura BigFLoat pronta para uso.
 */
BigFLoat inicializar_bf();

/**
 * @brief Libera a memória alocada para a mantissa de um BigFloat.
 * @param bf Ponteiro para a estrutura BigFLoat que será limpa.
 * @pre O ponteiro "bf" deve ser válido (diferente de NULL) e a estrutura deve ter sido previamente inicializada.
 * @post A memória de "bf->mantissa" é devolvida ao sistema, o ponteiro passa a apontar para NULL, e os valores de "capacidade" e "tamanho" são zerados.
 */
void liberar_bf(BigFLoat *bf);

#endif