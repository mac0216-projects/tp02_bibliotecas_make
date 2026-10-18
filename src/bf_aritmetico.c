#include "bf_aritmetico.h"
#include "comparacao_bf.h"

#include <stdint.h>
#include <stdlib.h>

static bool deslocar_decimal(const BigFloat *origem, long deslocamento, limb_t **resultado, size_t *tamanho) {
    size_t blocos = (size_t)(deslocamento / BF_DIGITOS_POR_LIMB);
    unsigned digitos = (unsigned)(deslocamento % BF_DIGITOS_POR_LIMB);
    size_t capacidade = origem->tamanho + blocos + (digitos != 0);
    limb_t *mantissa = calloc(capacidade + 1, sizeof(*mantissa));

    if (mantissa == NULL) return false;

    uint64_t fator = 1;
    for (unsigned contador = 0 ; contador < digitos ; contador += 1) fator *= 10;

    for (size_t contador = 0 ; contador < origem->tamanho ; contador += 1) {
        size_t indice = contador + blocos;
        uint64_t valor = (uint64_t)(origem->mantissa[contador] * fator + mantissa[indice]);
        mantissa[indice] = (limb_t)(valor % BF_BASE);
        mantissa[indice + 1] += (limb_t)(valor / BF_BASE);
    }

    *tamanho = capacidade + 1;
    while ((*tamanho > 0) && (mantissa[*tamanho - 1] == 0)) (*tamanho) -= 1;
    *resultado = mantissa;

    return true;
}

static int comparar_magnitude(const limb_t *bigFloatUm, size_t tamanhoBfUm, const limb_t *bigFloatDois, size_t tamanhoBfDois) {
    if (tamanhoBfUm != tamanhoBfDois) return (tamanhoBfUm > tamanhoBfDois) ? 1 : -1;

    for (size_t contador = tamanhoBfUm ; contador > 0 ; contador -= 1) {
        if (bigFloatUm[contador - 1] != bigFloatDois[contador - 1])
            return (bigFloatUm[contador - 1] > bigFloatDois[contador - 1]) ? 1 : -1;
    }

    return 0;
}

static limb_t *somar_magnitude(const limb_t *bigFloatUm, const limb_t *BigFloatDois, size_t tamanho, size_t *tamanhoResultado) {
    limb_t *resultado = calloc(tamanho + 1, sizeof(*resultado));
    uint64_t carry = 0;

    if (resultado == NULL) return NULL;

    for (size_t contador = 0 ; contador < tamanho ; contador += 1) {
        uint64_t soma = (uint64_t)bigFloatUm[contador] +
                        BigFloatDois[contador] + carry;
        resultado[contador] = (limb_t)(soma % BF_BASE);
        carry = soma / BF_BASE;
    }
    resultado[tamanho] = (limb_t)carry;
    *tamanhoResultado = tamanho + (carry != 0);

    return resultado;
}

static limb_t *subtrair_magnitude(const limb_t *maior, const limb_t *menor, size_t tamanho, size_t *tamanhoResultado) {
    limb_t *resultado = calloc(tamanho, sizeof(*resultado));
    int64_t emprestimo = 0;

    if (resultado == NULL) return NULL;

    for (size_t contador = 0 ; contador < tamanho ; contador += 1) {
        int64_t diferenca = (int64_t)maior[contador] -
                            menor[contador] - emprestimo;

        if (diferenca < 0) {
            diferenca += BF_BASE;
            emprestimo = 1;
        }
        else emprestimo = 0;

        resultado[contador] = (limb_t)diferenca;
    }
    *tamanhoResultado = tamanho;

    while ((*tamanhoResultado > 0) && (resultado[*tamanhoResultado - 1] == 0)) {
        (*tamanhoResultado) -= 1;
    }

    return resultado;
}

static BigFloat *operar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois, bool subtracao) {
    if (
        !bf_verificar_bigfloat_valido(bigFloatUm) ||
        !bf_verificar_bigfloat_valido(bigFloatDois)
    ) return NULL;

    long expoente = (bigFloatUm->expoente > bigFloatDois->expoente) ? bigFloatUm->expoente : bigFloatDois->expoente;
    limb_t *maior = NULL;
    limb_t *menor = NULL;
    size_t tamanhoMaior = 0;
    size_t tamanhoMenor = 0;
    int sinalBfDois = subtracao ? -bigFloatDois->sinal : bigFloatDois->sinal;

    if (
        !deslocar_decimal(bigFloatUm, expoente - bigFloatUm->expoente, &maior, &tamanhoMaior) ||
        !deslocar_decimal(bigFloatDois, expoente - bigFloatDois->expoente, &menor, &tamanhoMenor)
    ) {
        free(maior);
        free(menor);
        return NULL;
    }

    int comparacao = comparar_magnitude(maior, tamanhoMaior, menor, tamanhoMenor);
    limb_t *mantissa = NULL;
    size_t tamanho = 0;
    int sinal = bigFloatUm->sinal;

    if (bigFloatUm->sinal == sinalBfDois) {
        size_t limite = tamanhoMaior > tamanhoMenor ? tamanhoMaior : tamanhoMenor;
        limb_t *bfUmAlinhado = realloc(maior, (limite + 1) * sizeof(*maior));
        limb_t *bfDoisAlinhado = realloc(menor, (limite + 1) * sizeof(*menor));

        if (bfUmAlinhado == NULL || bfDoisAlinhado == NULL) {
            free(bfUmAlinhado != NULL ? bfUmAlinhado : maior);
            free(bfDoisAlinhado != NULL ? bfDoisAlinhado : menor);
            return NULL;
        }
        maior = bfUmAlinhado;
        menor = bfDoisAlinhado;

        for (size_t contador = tamanhoMaior; contador < limite + 1; contador++) maior[contador] = 0;
        for (size_t contador = tamanhoMenor; contador < limite + 1; contador++) menor[contador] = 0;
        mantissa = somar_magnitude(maior, menor, limite, &tamanho);
    }
    else if (comparacao == 0) {
        free(maior);
        free(menor);
        BigFloat *zero = calloc(1, sizeof(*zero));
        if (zero == NULL) return NULL;
        zero->sinal = 1;
        zero->expoente = expoente;
        return zero;
    }
    else if (comparacao > 0) mantissa = subtrair_magnitude(maior, menor, tamanhoMaior, &tamanho);
    else {
        mantissa = subtrair_magnitude(menor, maior, tamanhoMenor, &tamanho);
        sinal = sinalBfDois;
    }

    free(maior);
    free(menor);
    if (mantissa == NULL) return NULL;

    BigFloat *resultado = calloc(1, sizeof(*resultado));
    if (resultado == NULL) {
        free(mantissa);
        return NULL;
    }
    resultado->sinal = tamanho == 0 ? 1 : sinal;
    resultado->expoente = expoente;
    resultado->tamanho = tamanho;
    resultado->capacidade = tamanho + 1;
    resultado->mantissa = mantissa;

    return resultado;
}

BigFloat *bf_somar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois) {
    return operar(bigFloatUm, bigFloatDois, false);
}

BigFloat *bf_subtrair(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois) {
    return operar(bigFloatUm, bigFloatDois, true);
}

/*----------------------------------------------------------------------------*/