/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include "lexical_value.h"
#include "ast.h"
#include "symbol_table.h"
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
