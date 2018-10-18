#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "valor_lexico.h"

extern int get_line_number();

TValorLexico GetValorLexico(int tipo, int tipo_valor, char *texto) {
    TValorLexico retorno;
    retorno.linha = get_line_number();
    retorno.tipo = tipo;
    if(tipo_valor == TIPO_LITERAL) {
        retorno.tipo_valor = tipo_valor;
        //TODO size of tipo_valor
        switch(tipo_valor) {
            case VALOR_CHAR:
                retorno.valor_char = texto[0];
                break;
            case VALOR_STRING:
                retorno.valor_string = strdup(texto);
                break;
            case VALOR_INT:
                retorno.valor_int = atoi(texto);
                break;
            case VALOR_FLOAT:
                retorno.valor_float = atof(texto);
                break;
            case VALOR_BOOL:
                if(strcmp("true", texto) == 0) {
                    retorno.valor_bool = 1;
                }
                else {
                    retorno.valor_bool = 0;
                }
                break;
            default:
                retorno.tipo_valor = VALOR_STRING;
                retorno.valor_string = strdup(texto);
                printf("Unexpected value type for literal");
                break;
        }
    }
    else {
        retorno.tipo_valor = VALOR_STRING;
        retorno.valor_string = strdup(texto);
    }
    return retorno;
}

TValorLexico *lexCopy(TValorLexico lex)
{
    TValorLexico *ret = NULL;
    ret = malloc(sizeof(TValorLexico));
    memcpy(ret, &lex, sizeof(TValorLexico));
    return ret;
}
