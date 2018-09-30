/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "ast.h"
#include "valor_lexico.h"

LIST *listCreate()
{
	LIST *head = NULL;
	head = malloc(sizeof(LIST));

	head->node = NULL;
	head->next = NULL;

	return head;
}

void listPush(LIST *head, AST *node)
{
	LIST *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(LIST));
    current->next->node = node;
    current->next->next = NULL;
}

LIST *listGet(LIST *head, int index)
{
	LIST *current = head;
	int currentIndex = 0;

	while(currentIndex < index && current != NULL) {
		current = current->next;
		currentIndex++;
	}

	return current;
}
