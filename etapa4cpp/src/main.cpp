/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include "../include/lexical_value.h"
#include "../include/ast.h"
#include "../include/symbol_table.h"
#include "../include/parser.tab.h" //arquivo gerado com bison -d parser.y

AbstractSyntaxTree *arvore = NULL;
void descompila (AbstractSyntaxTree *arvore);
void libera (AbstractSyntaxTree *arvore);

int main(int argc, char **argv)
{
    //Inicializa a tabela de símbolos global
    int ret = yyparse();
    descompila(arvore);
    libera(arvore);
    //libera a árvore de tabelas de símbolos
    arvore = NULL;
    //yylex_destroy();
    return ret;
}
