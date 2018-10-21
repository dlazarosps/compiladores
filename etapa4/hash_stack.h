/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#ifndef HASH_STACK_HEADER
#define HASH_STACK_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct hash_stack_node
{
    HASH *hash;
    struct hash_stack_node *next;
} HASHSTACK;

HASHSTACK *hashStackCreate(); //Cria uma pilha
HASHSTACK *hashStackPush(HASHSTACK *top, HASH *hash); //Empilha uma tabela de símbolos na pilha
int hashStackIsEmpty(HASHSTACK *top); //Retorna 1 se pilha vazia, 0 se não
HASHSTACK *hashStackDeleteTop(HASHSTACK *top); //Deleta o nodo no topo da pilha (e limpa a hash dentro dele)
HASH *hashStackGet(HASHSTACK *top); //Retorna a tabela de símbolos que estão no topo da pilha
HASHSTACK *hashStackDestroy(HASHSTACK *top); //Limpa e destrói a pilha, retornando NULL

#endif
