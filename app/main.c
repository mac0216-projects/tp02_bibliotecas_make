#include "gerenciamento_de_memoria_bf.h"

int main() {
  BigFLoat n1 = inicializar_bf();

  printf("Capacidade: %zu\n", n1.capacidade);
  printf("Endereço da mantissa: %p\n", n1.mantissa);
  printf("Mantissa: %u\n", n1.mantissa[0]);

  liberar_bf(&n1);

  return 0;
}