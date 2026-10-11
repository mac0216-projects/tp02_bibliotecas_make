#include "gerenciamento_de_memoria_bf.h"
#include <assert.h>

void teste_inicializar_bf() {
  BigFloat n1;
  inicializar_bf(&n1);

  assert(n1.capacidade == 1);
  assert(n1.tamanho == 0);
  assert(n1.sinal == 1);
  assert(n1.mantissa != NULL);

}

void teste_liberar_bf() {
  BigFloat n1;

  inicializar_bf(&n1);
  liberar_bf(&n1);

  assert(n1.capacidade == 0);
  assert(n1.tamanho == 0);
  assert(n1.sinal == 1);
  assert(n1.mantissa == NULL);

  liberar_bf(NULL);
}

int main() {
  printf("Iniciando testes de memoria...\n");

  teste_inicializar_bf();
  teste_liberar_bf();
  
  printf("Todos os testes de memoria passaram com sucesso!\n");
  return 0;
}