#include "gerenciamento_de_memoria_bf.h"

int main() {
  BigFloat meu_numero;

  if (!inicializar_bf(&meu_numero)) {
      printf("Falha ao inicializar o BigFloat.\n");
      return 1; 
  }

  return 0;
}