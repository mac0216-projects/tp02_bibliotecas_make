#include "gerenciamento_de_memoria_bf.h"
#include "entrada_e_saida.h"

int main() {
  BigFloat meu_numero;
  const char* tmp = "-83156898747988.6482966126441861";

  if (!inicializar_bf(&meu_numero)) {
      printf("Falha ao inicializar o BigFloat.\n");
      return 1; 
  }

  if(!string_para_bf(&meu_numero, tmp)) {
    printf("String invalida!\n");
    return 1;
  }

  //FILE *saida = fopen("resultado.txt", "w"); //"w" = write
  FILE *saida = stdout;

  if (saida != NULL) {
        imprimir_bf(saida, &meu_numero);
        fclose(saida);
    }
  
  liberar_bf(&meu_numero);

  return 0;
}