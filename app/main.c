#include "gerenciamento_de_memoria_bf.h"

int main() {
  BigFLoat meu_numero_inicial = inicializar_bf();

  printf("Capacidade: %zu\n", meu_numero_inicial.capacidade);
  printf("Endereço da mantissa: %p\n", meu_numero_inicial.mantissa);
  printf("Mantissa: %u\n", meu_numero_inicial.mantissa[0]);



  return 0;
}