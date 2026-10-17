#include "entrada_e_saida.h"
#include <string.h>

bool string_para_bf(BigFloat *destino, const char *string) {
  if (string == NULL || strlen(string) == 0) return false;

  bool achou_ponto = false;
    for (size_t i = 0; i < strlen(string); i++) {
        char c = string[i];

        if (i == 0 && c == '-') continue;

        if (c == '.') {
            if (achou_ponto) return false;
            achou_ponto = true;
            continue;
        }

        if (c < '0' || c > '9') {
            return false;
        }
    }

  int sinal = 1;
  long expoente = 0;
  size_t tamanho = 0;
  bool e_inteiro = true;

  //  destino->sinal
  if (string[0] == '-') sinal = -1;
  destino->sinal = sinal;

  // destino->expoente
  for (long i = strlen(string) - 1; i >= 0; i--) {
    if (string[i] == '.') {
      e_inteiro = false;
      break;
    }

    expoente++;
  }

  if (e_inteiro) expoente = 0;
  destino->expoente = expoente;

  // destino->tamanho
  int qtd_nao_numero = 0;
  if (sinal == -1) qtd_nao_numero++;
  if (!e_inteiro) qtd_nao_numero++;

  //divisão inteira arredondando para cima(teto)
  tamanho = ((strlen(string) - qtd_nao_numero) + 9 - 1) / 9; 
  destino->tamanho = tamanho;
  destino->capacidade = 2 * tamanho;

  // destino->mantissa
  limb_t *nova_mantissa = realloc(destino->mantissa, destino->capacidade * sizeof(limb_t));
  
  if (nova_mantissa == NULL) return false; // Faltou RAM
  
  destino->mantissa = nova_mantissa;
  
  int bloco_atual = 0;
  uint32_t valor_bloco = 0;
  uint32_t multiplicador = 1;
  int digitos_lidos = 0;

  for (long i = strlen(string) - 1; i >= 0; i--) {
      char c = string[i];

      if (c == '.' || c == '-') {
          continue;
      }

      // Tabela ASCII: transformamos o caractere no número real (ex: '5' - '0' = 5)
      uint32_t digito = c - '0';

      valor_bloco = valor_bloco + (digito * multiplicador);
      multiplicador *= 10;
      digitos_lidos++;

      // Se já lemos 9 dígitos, o bloco encheu
      if (digitos_lidos == 9) {
          destino->mantissa[bloco_atual] = valor_bloco;
          bloco_atual++;
          
          // reset para começar o proximo bloco
          valor_bloco = 0;
          multiplicador = 1;
          digitos_lidos = 0;
      }
  }

  if (digitos_lidos > 0) {
      destino->mantissa[bloco_atual] = valor_bloco;
  }
  
  return true;
}

void imprimir_bf(FILE *stream, const BigFloat *bf) {
    // validação e caso zero
    if (bf == NULL || stream == NULL) {
        printf("Paramentros varios.\n");
        return;
    }

    if (bf->tamanho == 0) {
        fprintf(stream, "0\n");
        return;
    }
    // imprime o sinal
    if (bf->sinal == -1) {
        fprintf(stream, "-");
    }

    // tamanho exato apenas do primeiro bloco (o mais alto) ex: número o 21.234.567.890
    // terá mantissa[0] = 234567890 e mantissa[1] = 21, logo a mantissa[1](topo) tera 1 digito
    char buf_topo[12]; 
    int digitos_topo = sprintf(buf_topo, "%u", bf->mantissa[bf->tamanho - 1]);
    
    // total de dígitos do número inteiro = tamanho do bloco do topo + (outros blocos * 9)
    long total_digitos = digitos_topo + ((long)bf->tamanho - 1) * 9;

    // número puramente fracionário. ex: 0.00125, mantissa[0] = 125 (total de digitos = 3), 
    // mas o expoente bf->expoente = 5, logo 5 - 3 = 2, como 5>=3, imprime dois zeros depois do ponto 0.00
    if (bf->expoente >= total_digitos) {
        fprintf(stream, "0.");
        for (long i = 0; i < bf->expoente - total_digitos; i++) {
            fprintf(stream, "0");
        }
        
        // imprime os blocos restantes
        fprintf(stream, "%s", buf_topo);
        for (long i = bf->tamanho - 2; i >= 0; i--) {
            fprintf(stream, "%09u", bf->mantissa[i]);
        }
    } 
    // numero normal/não fracionario (o ponto cai no meio ou não existe)
    else {
        long posicao_do_ponto = total_digitos - bf->expoente;
        long posicao_atual = 0;

        // imprime o bloco do topo caractere por caractere
        for (int j = 0; buf_topo[j] != '\0'; j++) {
            if (posicao_atual == posicao_do_ponto && bf->expoente > 0) {
                fprintf(stream, ".");
            }
            fprintf(stream, "%c", buf_topo[j]);
            posicao_atual++;
        }

        // Imprime o resto dos blocos caractere por caractere
        for (long i = bf->tamanho - 2; i >= 0; i--) {
            char buf_bloco[10];
            sprintf(buf_bloco, "%09u", bf->mantissa[i]); // formata preenchendo com zeros
            
            for (int j = 0; buf_bloco[j] != '\0'; j++) {
                if (posicao_atual == posicao_do_ponto && bf->expoente > 0) {
                    fprintf(stream, ".");
                }
                fprintf(stream, "%c", buf_bloco[j]);
                posicao_atual++;
            }
        }
    }
    
    fprintf(stream, "\n");
}