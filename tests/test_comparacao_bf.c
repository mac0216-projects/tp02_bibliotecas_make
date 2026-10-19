#include "comparacao_bf.h"
#include "entrada_e_saida.h"
#include <assert.h>

/* Compara nos dois sentidos e confere o resultado. */
static void conferir(const char *sa, const char *sb, int esperado) {
  BigFloat a;
	BigFloat b;
	inicializar_bf(&a);
	inicializar_bf(&b);

	assert(string_para_bf(&a, sa) == true);
	assert(string_para_bf(&b, sb) == true);

	assert(comparar_bf(&a, &b) == esperado);
	assert(comparar_bf(&b, &a) == -esperado);

	liberar_bf(&a);
	liberar_bf(&b);
}

static void test_zero_e_negativo() {
	BigFloat n;
	inicializar_bf(&n);

	assert(string_para_bf(&n, "-0") == true);
	assert(bf_e_zero(&n) == true);
	assert(bf_e_negativo(&n) == false);       /* -0 é zero, não negativo */

	assert(string_para_bf(&n, "1000000000") == true);
	assert(bf_e_zero(&n) == false);           /* bloco 0 zerado, bloco 1 = 1 */

	assert(string_para_bf(&n, "-5") == true);
	assert(bf_e_negativo(&n) == true);

	liberar_bf(&n);
}

static void test_comparar_bf() {
	/* sinais */
	conferir("-5", "3", -1);
	conferir("-5", "-3", -1);

	/* decimais e expoentes diferentes */
	conferir("1.5", "1.50", 0);
	conferir("1.25", "1.5", -1);
	conferir("0.5", "100", -1);

	/* zeros */
	conferir("-0", "0", 0);
	conferir("0", "0.000", 0);
	conferir("0", "5", -1);

	/* fronteira de bloco */
	conferir("1000000000", "999999999", 1);
	conferir("999999999.999999999", "1000000000", -1);

	/* número grande, difere só no último dígito */
	conferir("831568907164655817472466146198747988.64829661264829642619841294912841861",
			 "831568907164655817472466146198747988.64829661264829642619841294912841862", -1);
}

static void test_ponteiros_nulos() {
	BigFloat n;
	inicializar_bf(&n);
	assert(string_para_bf(&n, "5") == true);

	assert(comparar_bf(NULL, &n) == BF_CMP_ERRO);
	assert(comparar_bf(&n, NULL) == BF_CMP_ERRO);
	assert(comparar_bf(NULL, NULL) == BF_CMP_ERRO);

	assert(comparar_modulo_bf(NULL, &n) == BF_CMP_ERRO);
	assert(comparar_modulo_bf(&n, NULL) == BF_CMP_ERRO);
	assert(comparar_modulo_bf(NULL, NULL) == BF_CMP_ERRO);

	assert(bf_e_zero(NULL) == false);
	assert(bf_e_negativo(NULL) == false);

	liberar_bf(&n);
}

static void test_bigfloat_invalido() {
	BigFloat n;
	inicializar_bf(&n);
	assert(string_para_bf(&n, "-5") == true);

	BigFloat invalido = n;
	invalido.mantissa = NULL;
	assert(comparar_bf(&n, &invalido) == BF_CMP_ERRO);
	assert(comparar_modulo_bf(&invalido, &n) == BF_CMP_ERRO);
	assert(bf_e_zero(&invalido) == false);
	assert(bf_e_negativo(&invalido) == false);

	invalido = n;
	invalido.tamanho = n.capacidade + 1;
	assert(comparar_bf(&invalido, &n) == BF_CMP_ERRO);
	assert(bf_e_zero(&invalido) == false);
	assert(bf_e_negativo(&invalido) == false);

	liberar_bf(&n);
}

void test_modulo_comparacao_bf() {
	test_zero_e_negativo();
	test_comparar_bf();
	test_ponteiros_nulos();
	test_bigfloat_invalido();
}