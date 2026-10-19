#include "bf_aritmetico.h"
#include "comparacao_bf.h"

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

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
        uint64_t valor = (uint64_t)origem->mantissa[contador] * fator + mantissa[indice];
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

static BigFloat *criar_resultado(limb_t *mantissa, size_t tamanho, long expoente, int sinal) {
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

/*SOMA & SUBTRAÇÃO------------------------------------------------------------*/

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

    return criar_resultado(mantissa, tamanho, expoente, sinal);
} 

BigFloat *bf_somar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois) {
    return operar(bigFloatUm, bigFloatDois, false);
}

BigFloat *bf_subtrair(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois) {
    return operar(bigFloatUm, bigFloatDois, true);
}

/*MULTIPLICAÇÃO---------------------------------------------------------------*/

static void remover_zero_esquerda(limb_t *valor, size_t *tamanho) {
    while (*tamanho > 0 && valor[*tamanho - 1] == 0) (*tamanho) -= 1;
}

static limb_t *multiplicar_magnitude(const limb_t *blocoUm, size_t tamanhoBlocoUm, const limb_t *blocoDois, size_t tamanhoBlocoDois, size_t *tamanhoResultado) {
    limb_t *resultado = calloc(tamanhoBlocoUm + tamanhoBlocoDois, sizeof(*resultado));
    if (resultado == NULL) return NULL;

    for (size_t contador = 0 ; contador < tamanhoBlocoUm ; contador += 1) {  
        uint64_t carry = 0;

        for (size_t contador2 = 0 ; contador2 < tamanhoBlocoDois ; contador2 += 1) {
            uint64_t produto = (
                (uint64_t)blocoUm[contador] * blocoDois[contador2] + resultado[contador + contador2] + carry
            );

            resultado[contador + contador2] = (limb_t)(produto % BF_BASE);
            carry = produto / BF_BASE;
        }
        resultado[contador + tamanhoBlocoDois] = (limb_t)carry;
    }

    *tamanhoResultado = tamanhoBlocoUm + tamanhoBlocoDois;
    remover_zero_esquerda(resultado, tamanhoResultado);
    return resultado;
}

static limb_t *multiplicar_por_limb(const limb_t *valor, size_t tamanho, limb_t multiplicador, size_t *tamanhoResultado) {
    limb_t *resultado = calloc(tamanho + 1, sizeof(*resultado));
    uint64_t carry = 0;

    if (resultado == NULL) return NULL;

    for (size_t contador = 0 ; contador < tamanho ; contador += 1) {
        uint64_t produto = (uint64_t)valor[contador] * multiplicador + carry;
        resultado[contador] = (limb_t)(produto % BF_BASE);
        carry = produto / BF_BASE;
    }
    resultado[tamanho] = (limb_t)carry;
    *tamanhoResultado = tamanho + (carry != 0);

    return resultado;
}

BigFloat *bf_multiplicar(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois) {
    if (
        !bf_verificar_bigfloat_valido(bigFloatUm) ||
        !bf_verificar_bigfloat_valido(bigFloatDois)
    ) return NULL;

    size_t tamanho = 0;
    limb_t *mantissa = multiplicar_magnitude(
        bigFloatUm->mantissa, bigFloatUm->tamanho,
        bigFloatDois->mantissa, bigFloatDois->tamanho,
        &tamanho
    );
    if (
        mantissa == NULL &&
        bigFloatUm->tamanho != 0 &&
        bigFloatDois->tamanho != 0
    ) return NULL;

    return criar_resultado(
        mantissa, tamanho,
        bigFloatUm->expoente + bigFloatDois->expoente,
        bigFloatUm->sinal * bigFloatDois->sinal
    );
}

/*DIVISÃO---------------------------------------------------------------------*/

static void subtrair_na_divisao(limb_t *valor, size_t tamanhoValor, const limb_t *subtraendo, size_t tamanhoSubtraendo) {
    int64_t emprestimo = 0;

    for (size_t contador = 0; contador < tamanhoValor; contador += 1) {
        limb_t parcela = contador < tamanhoSubtraendo ? subtraendo[contador] : 0;
        int64_t diferenca = (int64_t)valor[contador] - parcela - emprestimo;

        if (diferenca < 0) {
            diferenca += BF_BASE;
            emprestimo = 1;
        }
        else emprestimo = 0;

        valor[contador] = (limb_t)diferenca;
    }
}

static limb_t encontrar_digito_divisao(const limb_t *resto, size_t tamanhoResto, const limb_t *divisor, size_t tamanhoDivisor) {
    limb_t inferior = 0, superior = BF_BASE - 1;

    while (inferior <= superior) {
        limb_t candidato = inferior + (superior - inferior) / 2;
        size_t tamanhoProduto = 0;
        limb_t *produto = multiplicar_por_limb(divisor, tamanhoDivisor, candidato, &tamanhoProduto);
        int comparacao;

        if (produto == NULL) return 0;
        comparacao = comparar_magnitude(resto, tamanhoResto, produto, tamanhoProduto);

        if (comparacao >= 0) {
            inferior = candidato + 1;
        }
        else {
            if (candidato == 0) break;
            superior = candidato - 1;
        }
        free(produto);
    }

    return superior;
}

static bool dividir_magnitude(const limb_t *numerador, size_t tamanhoNumerador, const limb_t *divisor, size_t tamanhoDivisor, limb_t **quociente, size_t *tamanhoQuociente) {
    limb_t *resto = calloc(tamanhoNumerador + 1, sizeof(*resto)),
        *resultado = calloc(tamanhoNumerador + 1, sizeof(*resultado))
    ;
    if (resto == NULL || resultado == NULL) {
        free(resto);
        free(resultado);
        return false;
    }

    size_t tamanhoResto = 0;
    for (size_t indice = tamanhoNumerador ; indice > 0 ; indice -= 1) {
        size_t novoTamanho = tamanhoResto + 1;
        for (size_t contador = novoTamanho; contador > 1; contador -= 1) {
            resto[contador - 1] = resto[contador - 2];
        }
        resto[0] = numerador[indice - 1];
        tamanhoResto = novoTamanho;
        remover_zero_esquerda(resto, &tamanhoResto);

        size_t posicao = indice - 1;
        if (comparar_magnitude(resto, tamanhoResto, divisor, tamanhoDivisor) >= 0) {
            limb_t digito = encontrar_digito_divisao(resto, tamanhoResto, divisor, tamanhoDivisor);

            size_t tamanhoProduto = 0;
            limb_t *produto = multiplicar_por_limb(divisor, tamanhoDivisor, digito, &tamanhoProduto);
            if (produto == NULL) {
                free(resto);
                free(resultado);
                return false;
            }

            subtrair_na_divisao(resto, tamanhoResto, produto, tamanhoProduto);
            resultado[posicao] = digito;
            free(produto);
            remover_zero_esquerda(resto, &tamanhoResto);
        }
    }

    *tamanhoQuociente = tamanhoNumerador;
    remover_zero_esquerda(resultado, tamanhoQuociente);
    free(resto);
    *quociente = resultado;

    return true;
}

BigFloat *bf_dividir(const BigFloat *bigFloatUm, const BigFloat *bigFloatDois, size_t casasDecimais) {
    long escala;
    BigFloat numeradorEscalado;
    limb_t *numerador = NULL, *quociente = NULL;
    size_t tamanhoQuociente = 0, tamanhoNumerador = 0;

    if (!bf_verificar_bigfloat_valido(bigFloatUm) ||
        !bf_verificar_bigfloat_valido(bigFloatDois) ||
        bf_e_zero(bigFloatDois)) {
        return NULL;
    }

    if (casasDecimais > (size_t)LONG_MAX) return NULL;
    escala = (long)casasDecimais;
    if (
        bigFloatUm->expoente < bigFloatDois->expoente &&
        bigFloatDois->expoente - bigFloatUm->expoente > escala
    ) {
        escala = bigFloatDois->expoente - bigFloatUm->expoente;
    }
    if (escala > LONG_MAX / 2) return NULL;

    numeradorEscalado = *bigFloatUm;
    numeradorEscalado.expoente = 0;
    if (!deslocar_decimal(&numeradorEscalado, escala, &numerador, &tamanhoNumerador)) {
        return NULL;
    }

    if (!dividir_magnitude(
        numerador,
        tamanhoNumerador,
        bigFloatDois->mantissa,
        bigFloatDois->tamanho,
        &quociente,
        &tamanhoQuociente
    )) {
        free(numerador);
        return NULL;
    }
    free(numerador);

    return criar_resultado(
        quociente, tamanhoQuociente,
        escala + bigFloatUm->expoente - bigFloatDois->expoente,
        bigFloatUm->sinal * bigFloatDois->sinal
    );
}