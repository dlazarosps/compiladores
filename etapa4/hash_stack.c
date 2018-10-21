/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "hash_stack.h"

//Cria uma pilha
HASHSTACK *hashStackCreate()
{
	HASHSTACK *top = NULL;
	top = malloc(sizeof(HASHSTACK));

	top->hash = NULL;
	top->next = NULL;

	return top;
}

//Empilha uma tabela de símbolos na pilha
HASHSTACK *hashStackPush(HASHSTACK *top, HASH *hash)
{
	HASHSTACK *newTop = malloc(sizeof(HASHSTACK));

	newTop->hash = hash;
	newTop->next = top;

	return newTop;
}

//Retorna 1 se pilha vazia, 0 se não
int hashStackIsEmpty(HASHSTACK *top)
{
	if(top->next == NULL)
		return 1;
	else
		return 0;
}

//Deleta o nodo no topo da pilha (e limpa a hash dentro dele)
HASHSTACK *hashStackDeleteTop(HASHSTACK *top)
{
	if(hashStackIsEmpty(top) == 1)
		return top;

	HASHSTACK *newTop = top->next;

	//TODO: destroy the hash
	//hashDestroy(top->hash);

	return newTop;
}

//Retorna a tabela de símbolos que estão no topo da pilha
HASH *hashStackGet(HASHSTACK *top)
{
	return top->hash;
}

//Limpa e destrói a pilha, retornando NULL
HASHSTACK *hashStackDestroy(HASHSTACK *top)
{
	HASHSTACK *next;
	while(top != NULL) {
		next = top->next;
		//TODO: destroy the hash
		//hashDestroy(top->hash);
		free(top);
		top = next;
	}
	return NULL;
}
