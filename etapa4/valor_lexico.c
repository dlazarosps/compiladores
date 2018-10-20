#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "valor_lexico.h"

extern int get_line_number();

TValorLexico GetValorLexico(int tipo, int tipo_valor, char *texto) {
    TValorLexico retorno;
    retorno.linha = get_line_number();
    retorno.tipo = tipo;
    if(tipo == TIPO_LITERAL) {
        retorno.tipo_valor = tipo_valor;
        switch(tipo_valor) {
            case VALOR_CHAR:
                retorno.valor_char = texto[0];
                retorno.size = UM_BYTE;
                break;
            case VALOR_STRING:
                retorno.valor_string = strdup(texto);
                retorno.size = UM_BYTE * strlen(texto);
                break;
            case VALOR_INT:
                retorno.valor_int = atoi(texto);
                retorno.size = QUATRO_BYTE;
                break;
            case VALOR_FLOAT:
                retorno.valor_float = atof(texto);
                retorno.size = OITO_BYTE;
                break;
            case VALOR_BOOL:
                if(strcmp("true", texto) == 0) {
                    retorno.valor_bool = 1;
                }
                else {
                    retorno.valor_bool = 0;
                }
                break;
                retorno.size = UM_BYTE;
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
        retorno.size = UNDEFINED; //TODO tratar vetores e tipos do usuário na AST (parser)
    }
    
    //Insere lexico na hash table
    if (tipo == TIPO_IDENTIFICADOR || tipo == TIPO_LITERAL) { //literal tb?
        TValorLexico * hash_lex = lexCopy(retorno);     //ponteiro do valor_lexico
        HASH hash = hashInsert(texto, hash_lex);        //insere na tabela global
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
