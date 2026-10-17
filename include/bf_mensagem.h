#ifndef BF_MENSAGEM_H

    #define BF_MENSAGEM_H
    #define BF_MACRO_LISTA_MENSAGEM(X) \
        X(BF_SUCESSO,                "Sucesso") \
        X(BF_ERROR_NULL,        "Ponteiro nulo") \
        X(BF_ERROR_ALLOC,       "Falha de alocação de memória") \
        X(BF_ERROR_INVALID_ARG, "Argumento inválido") \
        X(BF_ERROR_DIV_ZERO,    "Divisão por 0") \

    typedef enum {
        #define X(bfMacroMensagem, bfMacroTexto) bfMacroMensagem,
            BF_MACRO_LISTA_MENSAGEM(X)
        #undef X

        BF_CONTADOR_MACRO_MENSAGEM /* Contabiliza a quantidade de erros. Necessário para evitar typo de erro */
    } BfMensagemEnum;

    typedef enum {
        BF_OK,
        BF_ERROR,
        BF_WARNING,
        BF_INFO,
        BF_CONTADOR_MACRO_MENSAGEM_TIPO
    } BfMensagemTipoEnum;

    /*------------------------------------------------------------------------*/

    /*!
        @brief Busca a mensagem correspondente ao código de erro fornecido.
        @param BF_MACRO_MENSAGEM O código de erro para o qual a mensagem deve ser buscada.
        @return Uma string contendo a mensagem correspondente ao código de erro fornecido.
    */
    const char *bf_buscar_mensagem_macro(BfMensagemEnum BF_MACRO_MENSAGEM);

    /*------------------------------------------------------------------------*/

    /*!
        @brief Exibe uma mensagem de depuração no console.
        @param BF_MACRO_MENSAGEM O código de erro para o qual a mensagem deve ser exibida.
        @param BF_TIPO_MENSAGEM O tipo da mensagem (OK, ERROR, WARNING, INFO).
        @param mensagemUsuario A mensagem personalizada fornecida pelo usuário.
    */
    void bf_mensagem_debug(BfMensagemEnum BF_MACRO_MENSAGEM, BfMensagemTipoEnum BF_TIPO_MENSAGEM, const char *mensagemUsuario);

#endif 