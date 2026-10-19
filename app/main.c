#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento_de_memoria_bf.h"
#include "entrada_e_saida.h"
#include "comparacao_bf.h"
#include "bf_aritmetico.h"

int main() {
    // 1. Declaração das variáveis de entrada na Stack
    BigFloat numero_a, numero_b;
    const char* str_a = "-83156898747988.6482966126441861";
    const char* str_b = "12345678901234.55";

    // 2. Inicialização segura
    if (!inicializar_bf(&numero_a) || !inicializar_bf(&numero_b)) {
        printf("Falha ao inicializar os BigFloats.\n");
        return 1;
    }

    // 3. Injeção e validação de dados (Fail-Fast)
    if (!string_para_bf(&numero_a, str_a) || !string_para_bf(&numero_b, str_b)) {
        printf("String invalida!\n");
        liberar_bf(&numero_a);
        liberar_bf(&numero_b);
        return 1;
    }

    // 4. Comparação e Processamento Aritmético
    int cmp = comparar_bf(&numero_a, &numero_b);
    if (cmp != BF_CMP_ERRO) {
        printf("Comparacao (A vs B): %d\n", cmp);
    }

    BigFloat *resultado_soma = bf_somar(&numero_a, &numero_b);
    if (resultado_soma == NULL) {
        printf("Erro ao realizar a soma.\n");
        liberar_bf(&numero_a);
        liberar_bf(&numero_b);
        return 1;
    }

    // 5. Exportação de dados (Terminal e Arquivo)
    printf("Resultado no terminal: ");
    imprimir_bf(stdout, resultado_soma);

    FILE *saida = fopen("resultado.txt", "w"); // "w" = write
    if (saida != NULL) {
        imprimir_bf(saida, resultado_soma);
        fclose(saida);
    }

    // 6. Liberação de memória
    liberar_bf(&numero_a);
    liberar_bf(&numero_b);
    
    // Para resultados alocados pelas funções aritméticas, libera-se a mantissa e a struct:
    liberar_bf(resultado_soma);
    free(resultado_soma);

    return 0;
}