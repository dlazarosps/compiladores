/*
Função principal para realização da E4.

Este arquivo não pode ser modificado.
*/
#include <stdio.h>
#include "valor_lexico.h"
#include "ast.h"
#include "list.h"
#include "hash.h"
#include "semantic.h"
#include "parser.tab.h" //arquivo gerado com bison -d parser.y

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);

int main(int argc, char **argv)
{
    //Inicializa a tabela de símbolos global
    int ret = yyparse();
    libera(arvore);
    //libera a árvore de tabelas de símbolos
    arvore = NULL;
    //yylex_destroy();
    return ret;
}
