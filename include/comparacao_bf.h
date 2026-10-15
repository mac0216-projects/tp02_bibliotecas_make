#ifndef _comparacao_bf_h
#define _comparacao_bf_h
#include "gerenciamento_de_memoria_bf.h"

/**
 * @brief Compara dois BigFloat levando em conta o sinal.
 * @param a Ponteiro para o primeiro número.
 * @param b Ponteiro para o segundo número.
 * @pre "a" e "b" devem ser válidos (não nulos) e já inicializados.
 * @post Nenhum dos números é modificado.
 * @return int -1 se a < b, 0 se a == b, 1 se a > b.
 */
int comparar_bf(const BigFloat *a, const BigFloat *b);

/**
 * @brief Compara dois BigFloat ignorando o sinal (compara |a| com |b|).
 * @param a Ponteiro para o primeiro número.
 * @param b Ponteiro para o segundo número.
 * @pre "a" e "b" devem ser válidos (não nulos) e já inicializados.
 * @post Nenhum dos números é modificado.
 * @return int -1 se |a| < |b|, 0 se |a| == |b|, 1 se |a| > |b|.
 */
int comparar_modulo_bf(const BigFloat *a, const BigFloat *b);

/**
 * @brief Verifica se o número vale zero.
 * @param bf Ponteiro para o número.
 * @pre "bf" deve ser válido (não nulo) e já inicializado.
 * @post O número não é modificado.
 * @return bool true se o valor for zero (inclusive "-0"), false caso contrário.
 */
bool bf_e_zero(const BigFloat *bf);

/**
 * @brief Verifica se o número é estritamente negativo.
 * @param bf Ponteiro para o número.
 * @pre "bf" deve ser válido (não nulo) e já inicializado.
 * @post O número não é modificado.
 * @return bool true se o valor for menor que zero, false caso contrário
 *         (zero não é negativo, mesmo com sinal -1).
 */
bool bf_e_negativo(const BigFloat *bf);

#endif