#ifndef _entrada_e_saida_h
#define _entrada_e_saida_h
#include "gerenciamento_de_memoria_bf.h"

/**
 * @brief Converte uma string numérica para a estrutura BigFloat. 
 * @param destino Ponteiro para a estrutura BigFloat que vai armazenar o valor.
 * @param string String que contém o número a ser convertido (ex: "-1234.567").
 * @pre O ponteiro "destino" e a "string" devem ser válidos (não nulos) e "destino" 
 *      já deve ter sido inicializado. A string deve conter apenas formatação 
 *      numérica válida.
 * @post A estrutura apontada por "destino" terá sua capacidade, tamanho, sinal 
 *       e expoente atualizados. A "mantissa" sofrerá um realloc para armazenar os blocos.
 * @warning Passar ponteiros nulos resultará em falha de segmentação (segmentation fault). 
 *          A função não verifica se há letras ou símbolos inválidos na string, 
 *          o que causaria cálculos incorretos na conversão ASCII.
 * @return bool Retorna "true" se a conversão for concluída com sucesso. 
 *         Retorna "false" se a realocação de memória (realloc) da mantissa falhar.
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