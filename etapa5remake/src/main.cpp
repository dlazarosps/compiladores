/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <iostream>
#include "../include/LexicalValue.h"
#include "../include/AbstractSyntaxTree.h"
#include "../include/SemanticAnalyzer.h"
#include "../include/CodeGenerator.h"
#include "../include/parser.tab.h" //arquivo gerado com bison -d parser.y

using namespace std;

AbstractSyntaxTree *arvore = NULL;
void descompila (AbstractSyntaxTree *arvore);
void libera (AbstractSyntaxTree *arvore);

int main(int argc, char **argv)
{
    int ret = yyparse();
    //descompila(arvore);

    SemanticAnalyzer *semantic = new SemanticAnalyzer(arvore);
    semantic->Analyze();
    //semantic->GetScopeManager()->Print();

    CodeGenerator *codeGenerator = new CodeGenerator(arvore, semantic->GetScopeManager());
    codeGenerator->Generate();
    codeGenerator->Print();

    libera(arvore);
    arvore = NULL;
    //yylex_destroy();
    return ret;
}
