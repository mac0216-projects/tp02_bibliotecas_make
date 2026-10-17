#ifndef BF_ERROR_H
#define BF_ERROR_H

#define BF_ERRORS_LIST(X) \
    X(BF_OK,                "Sucesso") \
    X(BF_ERROR_NULL,        "Ponteiro nulo") \
    X(BF_ERROR_ALLOC,       "Falha de alocacao de memoria") \
    X(BF_ERROR_INVALID_ARG, "Argumento inválido") \
    X(BF_ERROR_DIV_ZERO,    "Divisão por 0") \

typedef enum {
    #define X(bf_macro_erro, bf_mensagem_erro) bf_macro_erro,
        BF_ERRORS_LIST(X)
    #undef X

    BF_ERROR_ENUM_COUNT /* Contabiliza a quantidade de erros. É necessário para evitar typo de erro */
} BFErrorEnum;

const char *bf_mensagem_erro(BFErrorEnum BF_ERROR_MACRO);

#endif