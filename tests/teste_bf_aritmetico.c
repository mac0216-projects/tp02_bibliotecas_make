#include "bf_aritmetico.h"
#include "entrada_e_saida.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    BF_SOMA,
    BF_SUBTRACAO,
    BF_MULTIPLICACAO,
    BF_DIVISAO
} OperacaoAritmetica;

static void conferir_operacao(const char *entrada_um, const char *entrada_dois, const char *esperado, OperacaoAritmetica operacao) {
    BigFloat primeiro;
    BigFloat segundo;
    BigFloat *resultado = NULL;

    assert(inicializar_bf(&primeiro));
    assert(inicializar_bf(&segundo));
    assert(string_para_bf(&primeiro, entrada_um));
    assert(string_para_bf(&segundo, entrada_dois));

    switch(operacao) {
        case BF_SOMA:
            resultado = bf_somar(&primeiro, &segundo);
            break;
        case BF_SUBTRACAO:
            resultado = bf_subtrair(&primeiro, &segundo);
            break;
        default:
            assert(false && "Operação aritmética não suportada neste teste.");
    }
    assert(resultado != NULL);

    FILE *arquivo = tmpfile();
    assert(arquivo != NULL);
    imprimir_bf(arquivo, resultado);
    rewind(arquivo);

    char texto[256];
    assert(fscanf(arquivo, "%255s", texto) == 1);
    assert(strcmp(texto, esperado) == 0);

    fclose(arquivo);
    liberar_bf(resultado);
    free(resultado);
    liberar_bf(&primeiro);
    liberar_bf(&segundo);
}

static void test_somar(void) {
    conferir_operacao("1.25", "2.5", "3.75", false);
    conferir_operacao("-5", "-2", "-7", false);
    conferir_operacao("-5", "2", "-3", false);
    conferir_operacao("999999999", "1", "1000000000", false);
    conferir_operacao("1.000000001", "0.000000001", "1.000000002", false);
    conferir_operacao("5", "-5", "0", false);
}

static void test_subtrair(void) {
    conferir_operacao("10", "3.25", "6.75", true);
    conferir_operacao("-5", "-2", "-3", true);
    conferir_operacao("-5", "2", "-7", true);
    conferir_operacao("2", "5", "-3", true);
    conferir_operacao("1000000000", "1", "999999999", true);
    conferir_operacao("5.125", "5.125", "0", true);
}

static void test_ponteiros_nulos_aritmetico(void) {
    BigFloat numero;
    assert(inicializar_bf(&numero));
    assert(string_para_bf(&numero, "5"));

    assert(bf_somar(NULL, &numero) == NULL);
    assert(bf_somar(&numero, NULL) == NULL);
    assert(bf_subtrair(NULL, &numero) == NULL);
    assert(bf_subtrair(&numero, NULL) == NULL);

    liberar_bf(&numero);
}

void test_modulo_bf_aritmetico(void) {
    test_somar();
    test_subtrair();
    test_ponteiros_nulos_aritmetico();
}
