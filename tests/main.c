#include <stdio.h>

// --- PROTÓTIPOS: A lista de todos os testes do projeto ---

// Módulo 1: Memória
void test_modulo_gerenciamneto_de_memoria();

// Módulo 3: Comparações
void test_modulo_comparacao_bf();

// Módulo 4: Entrada e Saída
void test_modulo_entrada_e_saida();


int main() {
  printf("=======================================\n");
  printf(" INICIANDO BATERIA DE TESTES BIGFLOAT\n");
  printf("=======================================\n\n");

  printf("[1/3] Testando Gerenciamento de Memoria...\n");
  test_modulo_gerenciamneto_de_memoria();
  printf("      -> Memoria OK!\n\n");

  printf("[2/3] Testando Comparacoes...\n");
  test_modulo_comparacao_bf();
  printf("      -> Comparacoes OK!\n\n");

  printf("[3/3] Testando Entrada e Saida...\n");
  test_modulo_entrada_e_saida();
  printf("      -> Entrada e Saida OK!\n\n");

  printf("=======================================\n");
  printf(" TODOS OS TESTES PASSARAM COM SUCESSO! \n");
  printf("=======================================\n");

  return 0;
}