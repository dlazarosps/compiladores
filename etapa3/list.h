/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */

#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "valor_lexico.h"

typedef struct ast_node AST;

typedef struct list_node
{
    AST *node;
    struct list_node *next;
} LIST;

LIST *listCreate();
void listPush(LIST *head, AST *node);
AST *listGet(LIST *head, int index);
int listSize(LIST *head);
LIST *listDelete(LIST *head);

#endif
