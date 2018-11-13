/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <iostream>
#include "../include/lexical_value.h"
#include "../include/code_generator.h"
#include "../include/ast.h"
#include "../include/symbol_table.h"
#include "../include/semantic_analyzer.h"
#include "../include/parser.tab.h" //arquivo gerado com bison -d parser.y

using namespace std;

AbstractSyntaxTree *arvore = NULL;
void descompila (AbstractSyntaxTree *arvore);
void libera (AbstractSyntaxTree *arvore);

int main(int argc, char **argv)
{
    //Inicializa a tabela de símbolos global
    int ret = yyparse();
    //descompila(arvore);

    SemanticAnalyzer* analyzer = new SemanticAnalyzer(arvore);
    analyzer->Analyze();
    //analyzer->PrintScopes();

    ScopeStack *scopes = new ScopeStack();
    scopes->push(analyzer->GetGlobalScope());
    scopes->push(scopes->LookUp("main")->getAssociatedSymbolTable());

    CodeGenerator *coder = new CodeGenerator();
    coder->ParseAST(arvore, scopes);

    cout << coder->PrintOutput();

    libera(arvore);
    //libera a árvore de tabelas de símbolos
    arvore = NULL;
    //yylex_destroy();
    return ret;
}
