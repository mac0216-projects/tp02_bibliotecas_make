#include "comparacao_bf.h"

static int digito_em(const BigFloat *bf, long pos) {
    long k = pos + bf->expoente;
    if (k < 0 || (size_t)k >= bf->tamanho*9) {
        return 0;
    }

    limb_t bloco = bf->mantissa[(size_t)(k / 9)];
    size_t digito = (size_t)(k % 9);

    for (size_t i = 0; i < digito; i++) {
        bloco /= 10;
    }
    return (int)(bloco % 10);
}

int comparar_bf(const BigFloat *a, const BigFloat *b) {
    bool a_neg = bf_e_negativo(a);
    bool b_neg = bf_e_negativo(b);

    if (a_neg != b_neg) {
        return a_neg ? -1 : 1;
    }
    int cmp = comparar_modulo_bf(a, b);
    return a_neg ? -cmp : cmp;
}

int comparar_modulo_bf(const BigFloat *a, const BigFloat *b) {
    bool a_zero = bf_e_zero(a);
    bool b_zero = bf_e_zero(b);
    if (a_zero && b_zero) return 0;
    if (a_zero) return -1;
    if (b_zero) return 1;

    long topo_a = (long)(9 * a->tamanho) - 1 - a->expoente;
    long topo_b = (long)(9 * b->tamanho) - 1 - b->expoente;
    long topo = (topo_a > topo_b) ? topo_a : topo_b;
    long base = -((a->expoente > b->expoente) ? a->expoente : b->expoente);

    for (long p = topo; p >= base; p--) {
        int da = digito_em(a, p);
        int db = digito_em(b, p);
        if (da != db) return (da > db) ? 1 : -1;
    }
    return 0;
}

bool bf_e_zero(const BigFloat *bf) {
    for (size_t i = bf->tamanho; i > 0; i--) {
        if (bf->mantissa[i - 1] != 0) return false;
    }
    return true;
}

bool bf_e_negativo(const BigFloat *bf) {
    if (bf->sinal == -1 && !bf_e_zero(bf)) {
        return true;
    }
    return false;
}