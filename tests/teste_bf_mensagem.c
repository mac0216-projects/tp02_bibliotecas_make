#include "bf_mensagem.h"
#include <assert.h>
#include <string.h>

static void test_buscar_mensagem_macro() {
    BfMensagemEnum codigo;
    const char *mensagens_esperadas[] = {
        "Sucesso",
        "Ponteiro nulo",
        "Falha de alocação de memória",
        "Argumento inválido",
        "Divisão por 0"
    };

    for (codigo = BF_SUCESSO ; codigo < BF_CONTADOR_MACRO_MENSAGEM ; codigo += 1) {
        assert(
            strcmp(
                bf_buscar_mensagem_macro(codigo),
                mensagens_esperadas[codigo]
            ) == 0
        );
    }
}

static void test_buscar_mensagem_macro_codigo_invalido() {
    assert(
        strcmp(
            bf_buscar_mensagem_macro((BfMensagemEnum)-1),
            "Código de erro inválido."
        ) == 0
    );

    assert(
        strcmp(
            bf_buscar_mensagem_macro(BF_CONTADOR_MACRO_MENSAGEM),
            "Código de erro inválido."
        ) == 0
    );
}

static void test_mensagem_debug() {
    const BfMensagemEnum codigos[] = {
        BF_SUCESSO,
        BF_ERROR_NULL,
        BF_ERROR_ALLOC,
        BF_ERROR_INVALID_ARG,
        BF_ERROR_DIV_ZERO
    };
    const BfMensagemTipoEnum tipos[] = {
        BF_OK,
        BF_ERROR,
        BF_WARNING,
        BF_INFO,
        BF_CONTADOR_MACRO_MENSAGEM_TIPO
    };

    for (size_t indice_codigo = 0 ; indice_codigo < (sizeof(codigos) / sizeof(codigos[0])); indice_codigo += 1) {
        for (size_t indice_tipo = 0 ; indice_tipo < sizeof(tipos) / sizeof(tipos[0]) ; indice_tipo++) {
            bf_mensagem_debug(
                codigos[indice_codigo],
                tipos[indice_tipo],
                   "mensagem de teste"
            );
        }
    }
}

void test_modulo_bf_mensagem() {
    test_buscar_mensagem_macro();
    test_buscar_mensagem_macro_codigo_invalido();
    test_mensagem_debug();
}