#ifndef _entrada_e_saida_h
#define _entrada_e_saida_h
#include "gerenciamento_de_memoria_bf.h"

/**
 * @brief Converte uma string numérica para a estrutura BigFloat validando seu formato.
 * 
 * @param destino Ponteiro para a estrutura BigFloat que armazenará o valor.
 * @param string String contendo o número a ser convertido (ex: "-1234.567").
 * 
 * @pre O ponteiro "destino" deve ser válido (não nulo) e previamente inicializado.
 * @post Em caso de sucesso, "destino" terá seus atributos (capacidade, tamanho, sinal, expoente) 
 *       atualizados e sua "mantissa" realocada.
 * 
 * @warning Passar o ponteiro "destino" como nulo resultará em falha de segmentação.
 * 
 * @return bool Retorna "true" em caso de sucesso. Retorna "false" se a string for nula, 
 *         vazia, mal formatada (letras, múltiplos pontos), ou se faltar memória (realloc).
 */
bool string_para_bf(BigFloat *destino, const char *string);

/**
 * @brief Imprime o valor numérico de um BigFloat em uma stream de saída.
 * 
 * Lida automaticamente com o sinal, o posicionamento correto do ponto decimal 
 * (baseado no expoente) e o preenchimento com zeros para números fracionários.
 * 
 * @param stream Ponteiro para a stream de saída (ex: "stdout" para imprimir no terminal, ou um arquivo aberto).
 * @param bf Ponteiro constante para a estrutura BigFloat que será impressa.
 * @pre Os ponteiros "stream" e "bf" não devem ser nulos, e "bf" deve estar inicializado.
 * @post O valor numérico formatado é escrito na "stream" fornecida, seguido de uma quebra de linha. O estado de "bf" permanece inalterado.
 * @warning Se "bf" ou "stream" forem nulos, a função não quebra o programa; ela exibe uma mensagem de erro no console e retorna precocemente.
 */
void imprimir_bf(FILE *stream, const BigFloat *bf);


#endif