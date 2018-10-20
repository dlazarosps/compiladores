/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 999 //TODO dinamico ?

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "list.h"
#include "valor_lexico.h"

typedef struct hash_node
{
    char * text;
    TValorLexico *valor_lexico; // {linha, size, tipo, tipo_valor, union}
    struct hash_node *next; //encademento
} HASH;

// HASH* table[HASH_SIZE];
HASH* table[HASH_SIZE] = {NULL}; //auto init

// void hashInit();
void hashPrint();
int hashIndex(char * id);
HASH hashFind(char * id);
HASH hashInsert(char *texto, TValorLexico *lex);

#endif
