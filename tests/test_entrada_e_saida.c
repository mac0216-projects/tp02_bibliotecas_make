#include "entrada_e_saida.h"
#include <assert.h>


void test_string_para_bf_numero_valido() {
  const char* str_valido = "-831568907164655817472466146198747988.64829661264829642619841294912841861";
  limb_t mantissa_numero_valido[] = {912841861, 619841294, 264829642, 864829661, 619874798, 747246614, 716465581, 83156890};

  BigFloat numero_valido_bf;
  inicializar_bf(&numero_valido_bf);

  assert(string_para_bf(&numero_valido_bf, str_valido) == true);
  assert(numero_valido_bf.sinal == -1);
  assert(numero_valido_bf.expoente == 35);
  assert(numero_valido_bf.tamanho == 8);
  assert(numero_valido_bf.capacidade == 16);

  for(size_t i = 0; i < numero_valido_bf.tamanho; i++) {
    assert(numero_valido_bf.mantissa[i] == mantissa_numero_valido[i]);
  }

  liberar_bf(&numero_valido_bf);
}

void test_string_para_bf_numero_invalido() {
  const char* str1_invalido = "-1invalido31568907164655817472466146198747988.64829661264829642619841294912841861";
  const char* str2_invalido = "315689071646-55817472466146198747988.64829661264829642619841294912841861";
  const char* str3_invalido = "315689071646.55817472466146198747988.64829661264829642619841294912841861";

  BigFloat n1_invalido_bf;
  BigFloat n2_invalido_bf;
  BigFloat n3_invalido_bf;

  inicializar_bf(&n1_invalido_bf);
  assert(string_para_bf(&n1_invalido_bf, str1_invalido) == false);
  liberar_bf(&n1_invalido_bf);

  inicializar_bf(&n2_invalido_bf);
  assert(string_para_bf(&n2_invalido_bf, str2_invalido) == false);
  liberar_bf(&n2_invalido_bf);

  inicializar_bf(&n3_invalido_bf);
  assert(string_para_bf(&n3_invalido_bf, str3_invalido) == false);
  liberar_bf(&n3_invalido_bf);

}

void test_modulo_entrada_e_saida() {
  test_string_para_bf_numero_valido();
  test_string_para_bf_numero_invalido();
}




