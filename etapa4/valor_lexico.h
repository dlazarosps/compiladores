#ifndef VALOR_LEXICO_H
#define VALOR_LEXICO_H

#define TIPO_PALAVRA_RESERVADA 0
#define TIPO_CARACTER_ESPECIAL 1
#define TIPO_OPERADOR_COMPOSTO 2
#define TIPO_IDENTIFICADOR 3
#define TIPO_LITERAL 4

#define VALOR_STRING 0
#define VALOR_CHAR 1
#define VALOR_INT 2
#define VALOR_FLOAT 3
#define VALOR_BOOL 4

#define UM_BYTE 1
#define QUATRO_BYTE 4
#define OITO_BYTE 8
#define UNDEFINED -1


typedef struct tipo_valor_lexico {
    int linha;
    int tipo;
    int tipo_valor;
    int size;
    union {
        char *valor_string;
        char valor_char;
        int valor_int;
        float valor_float;
        int valor_bool;
    };
} TValorLexico;

TValorLexico GetValorLexico(int tipo, int tipo_literal, char *texto);
TValorLexico *lexCopy(TValorLexico lex);

#endif
