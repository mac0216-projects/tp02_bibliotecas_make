#ifndef _comparacao_bf_h
#define _comparacao_bf_h
#include "gerenciamento_de_memoria_bf.h"
/** Valor devolvido por comparar_bf() e comparar_modulo_bf() quando um argumento é inválido. */
#define BF_CMP_ERRO 2

/**
 * @brief Compara dois BigFloat levando em conta o sinal.
 * @param bf1 Ponteiro para o primeiro número.
 * @param bf2 Ponteiro para o segundo número.
 * @pre "bf1" e "bf2" devem ser válidos (não nulos) e já inicializados.
 * @post Nenhum dos números é modificado.
 * @return int -1 se bf1 < bf2, 0 se bf1 == bf2, 1 se bf1 > bf2,
 *         ou BF_CMP_ERRO se algum argumento for inválido.
 *         Quem chama deve comparar com BF_CMP_ERRO antes de interpretar o resultado.
 */
int comparar_bf(const BigFloat *bf1, const BigFloat *bf2);

/**
 * @brief Compara dois BigFloat ignorando o sinal (compara |bf1| com |bf2|).
 * @param bf1 Ponteiro para o primeiro número.
 * @param bf2 Ponteiro para o segundo número.
 * @pre "bf1" e "bf2" devem ser válidos (não nulos) e já inicializados.
 * @post Nenhum dos números é modificado.
 * @return int -1 se |bf1| < |bf2|, 0 se |bf1| == |bf2|, 1 se |bf1| > |bf2|,
 *         ou BF_CMP_ERRO se algum argumento for inválido.
 *         Quem chama deve comparar com BF_CMP_ERRO antes de interpretar o resultado.
 */
int comparar_modulo_bf(const BigFloat *bf1, const BigFloat *bf2);

/**
 * @brief Verifica se o número vale zero.
 * @param bf Ponteiro para o número.
 * @pre "bf" deve ser válido (não nulo) e já inicializado.
 * @post O número não é modificado.
 * @return bool true se o valor for zero (inclusive "-0"), false caso contrário.
 *         Retorna false se "bf" for inválido.
 */
bool bf_e_zero(const BigFloat *bf);

/**
 * @brief Verifica se o número é estritamente negativo.
 * @param bf Ponteiro para o número.
 * @pre "bf" deve ser válido (não nulo) e já inicializado.
 * @post O número não é modificado.
 * @return bool true se o valor for menor que zero, false caso contrário
 *         (zero não é negativo, mesmo com sinal -1).
 *         Retorna false se "bf" for inválido.
 */
bool bf_e_negativo(const BigFloat *bf);

#endif