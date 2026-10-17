#ifndef BF_ARITMETICO_H
    #include "gerenciamento_de_memoria_bf.h"
    #define BF_ARITMETICO_H

    /*!
        @brief Função que realiza a soma de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a soma dos dois números fornecidos.
        @return Retorna um novo BigFloat que representa a soma dos dois números fornecidos.
    */
    BigFloat *bf_somar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois);

    /*------------------------------------------------------------------------*/
    
    /*!
        @brief Função que realiza a subtração de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a subtração do segundo número do primeiro.
        @return Retorna um novo BigFloat que representa a subtração do segundo número do primeiro.
    */
    BigFloat *bf_subtrair(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois);

    /*------------------------------------------------------------------------*/

    /*!
        @brief Função que realiza a multiplicação de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a multiplicação dos dois números fornecidos.
        @return Retorna um novo BigFloat que representa a multiplicação dos dois números fornecidos.
    */
    BigFloat *bf_multiplicar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois);

    /*------------------------------------------------------------------------*/

    /*!
        @brief Função que realiza a divisão de dois números de precisão arbitrária.
        @param bigFloatUm Ponteiro para o primeiro número de precisão arbitrária.
        @param bigFloatDois Ponteiro para o segundo número de precisão arbitrária.
        @pre Nenhum dos ponteiros bigFloatUm ou bigFloatDois deve ser nulo. O segundo número não deve ser zero.
        @post Um ponteiro não nulo para um novo BigFloat é retornado, representando a divisão do primeiro número pelo segundo.
        @return Retorna um novo BigFloat que representa a divisão do primeiro número pelo segundo.
    */
    BigFloat *bf_dividir(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois);

#endif 