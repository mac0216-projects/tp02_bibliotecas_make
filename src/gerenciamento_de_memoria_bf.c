#include "gerenciamento_de_memoria_bf.h"

BigFLoat inicializar_bf() {
  BigFLoat bf;

  bf.sinal = 1;
  bf.expoente = 0;
  bf.tamanho = 0;
  bf.capacidade = 1;
  bf.mantissa = malloc(bf.capacidade * sizeof(limb_t));

  if (bf.mantissa == NULL) {
    printf("Erro fatal: Falta de memória.\n");
    exit(1);
  }

  return bf; 
}
