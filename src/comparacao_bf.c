#include "comparacao_bf.h"

static bool bf_valido(const BigFloat *bf) {
    if (bf == NULL) return false;
    if (bf->tamanho > bf->capacidade) return false;
    if (bf->tamanho > 0 && bf->mantissa == NULL) return false;
    return true;
}

static int posicao_digito_bf(const BigFloat *bf, long pos) {
    long k = pos + bf->expoente;
    if (k < 0 || (size_t)k >= bf->tamanho * 9) {
        return 0;
    }

    limb_t bloco = bf->mantissa[(size_t)(k / 9)];
    size_t posicao = (size_t)(k % 9);

    for (size_t i = 0; i < posicao; i++) {
        bloco /= 10;
    }
    return (int)(bloco % 10);
}

int comparar_bf(const BigFloat *bf1, const BigFloat *bf2) {
    if (!bf_valido(bf1) || !bf_valido(bf2)) return BF_CMP_ERRO;

    bool bf1_neg = bf_e_negativo(bf1);
    bool bf2_neg = bf_e_negativo(bf2);

    if (bf1_neg != bf2_neg) {
        return bf1_neg ? -1 : 1;
    }
    int cmp = comparar_modulo_bf(bf1, bf2);
    return bf1_neg ? -cmp : cmp;
}

int comparar_modulo_bf(const BigFloat *bf1, const BigFloat *bf2) {
    if (!bf_valido(bf1) || !bf_valido(bf2)) return BF_CMP_ERRO;

    bool bf1_zero = bf_e_zero(bf1);
    bool bf2_zero = bf_e_zero(bf2);
    if (bf1_zero && bf2_zero) return 0;
    if (bf1_zero) return -1;
    if (bf2_zero) return 1;

    long topo_bf1 = (long)(9 * bf1->tamanho) - 1 - bf1->expoente;
    long topo_bf2 = (long)(9 * bf2->tamanho) - 1 - bf2->expoente;
    long topo = (topo_bf1 > topo_bf2) ? topo_bf1 : topo_bf2;
    long base = -((bf1->expoente > bf2->expoente) ? bf1->expoente : bf2->expoente);

    for (long p = topo; p >= base; p--) {
        int digito_bf1 = posicao_digito_bf(bf1, p);
        int digito_bf2 = posicao_digito_bf(bf2, p);
        if (digito_bf1 != digito_bf2) return (digito_bf1 > digito_bf2) ? 1 : -1;
    }
    return 0;
}

bool bf_e_zero(const BigFloat *bf) {
    if (!bf_valido(bf)) return false;

    for (size_t i = bf->tamanho; i > 0; i--) {
        if (bf->mantissa[i - 1] != 0) return false;
    }
    return true;
}

bool bf_e_negativo(const BigFloat *bf) {
    if (!bf_valido(bf)) return false;
    
    if (bf->sinal == -1 && !bf_e_zero(bf)) {
        return true;
    }
    return false;
}