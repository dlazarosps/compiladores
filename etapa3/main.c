/*
Função principal para realização da E3.

Este arquivo não pode ser modificado.
*/
#include <stdio.h>
#include "valor_lexico.h"
#include "ast.h"
#include "list.h"
#include "parser.tab.h" //arquivo gerado com bison -d parser.y

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);

int main (int argc, char **argv)
{
  #if DEBUG
    TValorLexico x = {1, 1, 0, "x"};
    AST *element = astCreate(AST_TERMINAL, &x, NULL);
    LIST *leafs = listCreate();
    listPush(leafs, element);
    arvore = astCreate(AST_PROGRAMA, NULL, leafs);
    astPrint(arvore, 0);
    astDescomp(arvore);
    return 0;
  #else
    int ret = yyparse();
    descompila (arvore);
    libera(arvore);
    arvore = NULL;
    return ret;
  #endif

}
