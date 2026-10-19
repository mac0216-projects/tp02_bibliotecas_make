#ifndef BF_ARITMETICO_H

    #include "gerenciamento_de_memoria_bf.h"

    #define BF_ARITMETICO_H
    #define BF_BASE 1000000000U
    #define BF_DIGITOS_POR_LIMB 9

    /*!
        @brief Função que realiza a soma de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a soma dos dois números fornecidos.
        @return Ponteiro para um novo BigFloat que representa a soma dos dois números fornecidos.
    */
    BigFloat *bf_somar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois);

    /*------------------------------------------------------------------------*/
    
    /*!
        @brief Função que realiza a subtração de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a subtração do segundo número do primeiro.
        @return Ponteiro para um novo BigFloat que representa a subtração do segundo número do primeiro.
    */
    BigFloat *bf_subtrair(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois);

    /*------------------------------------------------------------------------*/

    /*!
        @brief Função que realiza a multiplicação de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a multiplicação dos dois números fornecidos.
        @return Ponteiro para um novo BigFloat que representa a multiplicação dos dois números fornecidos.
    */
    BigFloat *bf_multiplicar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois);

    /*------------------------------------------------------------------------*/

    /*!
        @brief Função que realiza a divisão de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @param casasDecimais Quantidade de casas decimais desejadas no resultado da divisão.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo. O segundo número não deve ser zero.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a divisão do primeiro número pelo segundo.
        @return Ponteiro para um novo BigFloat que representa a divisão do primeiro número pelo segundo.
            Em caso de divisão por 0, a função retorna NULL.
    */
    BigFloat *bf_dividir(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois, size_t casasDecimais);

#endif