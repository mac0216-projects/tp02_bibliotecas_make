#include "gerenciamento_de_memoria_bf.h"

bool inicializar_bf(BigFloat *bf) {
  if (bf == NULL) return false;

  bf->sinal = 1;
  bf->expoente = 0;
  bf->tamanho = 0;
  bf->capacidade = 1;
  bf->mantissa = malloc(bf->capacidade * sizeof(limb_t));

  if (bf->mantissa == NULL) {
        return false;
    }

  return true; 
}

void liberar_bf(BigFloat *bf) {
  if (bf == NULL) {
    return;
  }

  free(bf->mantissa);
  bf->mantissa = NULL;
  bf->capacidade = 0;
  bf->tamanho = 0;
}