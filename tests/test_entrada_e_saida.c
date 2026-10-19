#include "entrada_e_saida.h"
#include <assert.h>
#include <string.h>

void validar_numero_valido(const char *entrada, int sinal_esperado, long expoente_esperado, size_t tamanho_esperado, size_t capacidade_esperada, const limb_t *mantissa_esperada) {
    BigFloat bf;
    inicializar_bf(&bf);

    // 1. A conversão DEVE retornar true
    assert(string_para_bf(&bf, entrada) == true);
    
    // 2. Os metadados devem bater com a matemática
    assert(bf.sinal == sinal_esperado);
    assert(bf.expoente == expoente_esperado);
    assert(bf.tamanho == tamanho_esperado);
    assert(bf.capacidade == capacidade_esperada);

    // 3. Os blocos da mantissa devem ser exatos
    for (size_t i = 0; i < bf.tamanho; i++) {
        assert(bf.mantissa[i] == mantissa_esperada[i]);
    }

    liberar_bf(&bf);
}

void validar_numero_invalido(const char *entrada) {
  BigFloat numero_invalido;


  inicializar_bf(&numero_invalido);
  assert(string_para_bf(&numero_invalido, entrada) == false);
  liberar_bf(&numero_invalido);
}

// cria um arquivo temporario vazio, escreve o numero no arquivo temporario(imprimir_bf) 
// e  depois ler o que está escrito e compara e faz o assest de comparação com o texto lido 
void validar_impressao(const char *entrada) {
  BigFloat bf;
  inicializar_bf(&bf);
  string_para_bf(&bf, entrada);

  FILE *arquivo_fantasma = tmpfile(); // cria um arquivo fantasma na memória RAM

  assert(arquivo_fantasma != NULL);

  imprimir_bf(arquivo_fantasma, &bf); // escreve o numero bf no arquivo temp
  rewind(arquivo_fantasma);

  char resultado_lido[2000];
  fscanf(arquivo_fantasma, "%s", resultado_lido); // passa o arquivo temporario para a string resultado_lido
  assert(strcmp(resultado_lido, entrada) == 0); // compara

  fclose(arquivo_fantasma);
  liberar_bf(&bf);
}

void test_string_para_bf_numero_valido() {    
    validar_numero_valido(
        "-831568907164655817472466146198747988.64829661264829642619841294912841861", 
        -1, 35, 8, 16, 
        (limb_t[]){912841861, 619841294, 264829642, 864829661, 619874798, 747246614, 716465581, 83156890}
    );

    validar_numero_valido(
        "123456789", 
        1, 0, 1, 2, 
        (limb_t[]){123456789}
    );

    validar_numero_valido(
        "-0.00125", 
        -1, 5, 1, 2, 
        (limb_t[]){125}
    );
    
    validar_numero_valido(
        "1000000005", 
        1, 0, 2, 4, 
        (limb_t[]){5, 1}
    );
}

void test_string_para_bf_numero_invalido() {
  validar_numero_invalido("-1invalido31568907164655817472466146198747988.64829661264829642619841294912841861");
  validar_numero_invalido("315689071646-55817472466146198747988.64829661264829642619841294912841861");
  validar_numero_invalido("315689071646.55817472466146198747988.64829661264829642619841294912841861");
  validar_numero_invalido("-871842787414891.");
}

void test_imprimir_bf() {
  validar_impressao("0");
  validar_impressao("1000000005");
  validar_impressao("999888777");
  validar_impressao("-123456789.00125");
  validar_impressao("0.000000000123");
  validar_impressao("-1.000000000");
  validar_impressao("123456789.123456789");
}

void test_modulo_entrada_e_saida() {
  test_string_para_bf_numero_valido();
  test_string_para_bf_numero_invalido();
  test_imprimir_bf();
}




