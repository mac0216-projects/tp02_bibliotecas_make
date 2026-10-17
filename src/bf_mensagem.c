#include "bf_mensagem.h"

static const char *const BF_ERROR_ARRAY[BF_CONTADOR_MACRO_MENSAGEM] = {
    #define X(bf_macro_mensagem, bf_mensagem_texto) [bf_macro_mensagem] = bf_mensagem_texto,
        BF_MACRO_LISTA_MENSAGEM(X)
    #undef X
};

/*----------------------------------------------------------------------------*/

const char *bf_buscar_mensagem_macro(BfMensagemEnum BF_MACRO_MENSAGEM) {
    if(
        (BF_MACRO_MENSAGEM >= BF_CONTADOR_MACRO_MENSAGEM) ||
        (BF_MACRO_MENSAGEM < 0)
    ) return "Código de erro inválido.";
    
    return BF_ERROR_ARRAY[BF_MACRO_MENSAGEM];
}

/*----------------------------------------------------------------------------*/

void bf_mensagem_debug(BfMensagemEnum BF_MACRO_MENSAGEM, BfMensagemTipoEnum BF_TIPO_MENSAGEM, const char *mensagemUsuario) {
    #ifdef BF_DEBUG
        short int corMensagem = 0;
        char *mensagemMacro = bf_buscar_mensagem_macro(BF_MACRO_MENSAGEM);

        switch(BF_TIPO_MENSAGEM) {
            case BF_OK:

                break;
            case BF_ERROR:
            case BF_WARNING:
            case BF_INFO:
            default:
                break;
        }

        printf("\033[%dm%s: %s\033[0m\n", corMensagem, mensagemMacro, mensagemUsuario);
    #endif
}