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

        case BF_MULTIPLICACAO:
            resultado = bf_multiplicar(&primeiro, &segundo);
            break;

        case BF_DIVISAO:
            resultado = bf_dividir(&primeiro, &segundo, 18);
            break;

        default:assert(false && "Operação aritmética não suportada neste teste.");
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

static void test_multiplicar(void) {
    conferir_operacao("12", "3", "36", BF_MULTIPLICACAO);
    conferir_operacao("-2.5", "4", "-10.0", BF_MULTIPLICACAO);
    conferir_operacao("1.25", "0.8", "1.000", BF_MULTIPLICACAO);
    conferir_operacao("1000000000", "1000000000", "1000000000000000000",
                      BF_MULTIPLICACAO);
}

static void test_dividir(void) {
    conferir_operacao("10", "4", "2.500000000000000000", BF_DIVISAO);
    conferir_operacao("1", "3", "0.333333333333333333", BF_DIVISAO);
    conferir_operacao("-1", "2", "-0.500000000000000000", BF_DIVISAO);
}

static void test_ponteiros_nulos_aritmetico(void) {
    BigFloat numero;
    assert(inicializar_bf(&numero));
    assert(string_para_bf(&numero, "5"));

    assert(bf_somar(NULL, &numero) == NULL);
    assert(bf_somar(&numero, NULL) == NULL);
    assert(bf_subtrair(NULL, &numero) == NULL);
    assert(bf_subtrair(&numero, NULL) == NULL);
    assert(bf_multiplicar(NULL, &numero) == NULL);
    assert(bf_multiplicar(&numero, NULL) == NULL);
    assert(bf_dividir(NULL, &numero, 18) == NULL);
    assert(bf_dividir(&numero, NULL, 18) == NULL);

    liberar_bf(&numero);
}

static void test_divisao_por_zero(void) {
    BigFloat numero;
    BigFloat zero;
    assert(inicializar_bf(&numero));
    assert(inicializar_bf(&zero));
    assert(string_para_bf(&numero, "10"));
    assert(string_para_bf(&zero, "0"));

    assert(bf_dividir(&numero, &zero, 18) == NULL);

    liberar_bf(&numero);
    liberar_bf(&zero);
}

void test_modulo_bf_aritmetico(void) {
    test_somar();
    test_subtrair();
    test_multiplicar();
    test_dividir();
    test_ponteiros_nulos_aritmetico();
    test_divisao_por_zero();
}
