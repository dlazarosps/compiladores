/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */

#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "valor_lexico.h"

/*
 * Struct AST
 */
typedef struct list_node
{
    AST *node;
    struct list_node *next;
} LIST;

LIST *listCreate();
void listPush(LIST *head, AST *node);
LIST *listGet(LIST *head, int index);

#endif
