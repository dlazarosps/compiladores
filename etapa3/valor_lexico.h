#ifndef VALOR_LEXICO_DEF
#define VALOR_LEXICO_DEF

typedef struct st_tipo_valor_lexico {
    int linha;
    int tipo;
    void *valor;
} tipo_valor_lexico;

tipo_valor_lexico PalavraReservada() {
    tipo_valor_lexico retorno;
    retorno.linha = get_line_number();
    retorno.tipo = TIPO_PALAVRA_RESERVADA;
    retorno.valor = "ab";
    return retorno;
}

#endif
