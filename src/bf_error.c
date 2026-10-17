#include "bf_error.h"

static const char *const BF_ERROR_ARRAY[BF_ERROR_ENUM_COUNT] = {
    #define X(bf_macro_erro, bf_mensagem_erro) [bf_macro_erro] = bf_mensagem_erro,
        BF_ERRORS_LIST(X)
    #undef X
};

const char *bf_mensagem_erro(BFErrorEnum BF_ERROR_MACRO) {
    if(BF_ERROR_MACRO >= BF_ERROR_ENUM_COUNT || BF_ERROR_MACRO < 0) return "Código de erro inválido.";

    return BF_ERROR_ARRAY[BF_ERROR_MACRO];
}