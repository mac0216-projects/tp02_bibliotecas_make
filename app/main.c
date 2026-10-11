#include "gerenciamento_de_memoria_bf.h"
#include "entrada_e_saida.h"

int main() {
  BigFloat meu_numero;

  if (!inicializar_bf(&meu_numero)) {
      printf("Falha ao inicializar o BigFloat.\n");
      return 1; 
  }

  FILE *arquivo = fopen("test01-numero_valido.in", "r");
  if (arquivo == NULL) {
      printf("Erro: Nao foi possivel abrir o test01-numero_valido.in\n");
      liberar_bf(&meu_numero);
      return 1;
  }

  char buffer[10000];

  if (fscanf(arquivo, "%9999s", buffer) != 1) {
        printf("Erro: Arquivo vazio ou falha na leitura.\n");
        fclose(arquivo);
        liberar_bf(&meu_numero);
        return 1;
  }

  fclose(arquivo);

  if(!string_para_bf(&meu_numero, buffer)) {
    printf("String invalida!\n");
    return 1;
  }

  printf("sianl: %d\n", meu_numero.sinal);
  printf("expoente: %ld\n", meu_numero.expoente);
  printf("tamanho: %lu\n", meu_numero.tamanho);     
  printf("capacidade: %lu\n", meu_numero.capacidade);
  for(size_t i = 0; i < meu_numero.tamanho; i++) {
    printf("mantissa[%lu]: %u\n", i, meu_numero.mantissa[i]);
  }
  
  liberar_bf(&meu_numero);

  return 0;
}