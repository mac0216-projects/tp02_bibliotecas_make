#include <stdio.h>

 void test_modulo_gerenciamneto_de_memoria();
void test_modulo_comparacao_bf();
void test_modulo_entrada_e_saida();
void test_modulo_bf_mensagem();

typedef void (*FuncaoTeste)(void);

typedef struct {
  const char *texto;
  FuncaoTeste funcao;
} TesteModulo;

int main(void) {
  const TesteModulo testes[] = {
    {"Gerenciamento de Memoria", test_modulo_gerenciamneto_de_memoria},
    {"Comparacoes", test_modulo_comparacao_bf},
    {"Entrada e Saida", test_modulo_entrada_e_saida},
    {"Mensagens", test_modulo_bf_mensagem}
  };
  const size_t quantidade_testes = sizeof(testes) / sizeof(testes[0]);

  puts("");
  for (size_t i = 0; i < quantidade_testes; i++) {
    printf("[%zu/%zu] Testando %s ", i + 1, quantidade_testes,
           testes[i].texto);
    testes[i].funcao();
    printf("\033[32m%30s OK!\033[m\n", testes[i].texto);
  }
  return 0;
}