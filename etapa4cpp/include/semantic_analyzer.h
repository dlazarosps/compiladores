/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include <string>
#include <vector>
#include <stack>
#include "ast.h"
#include "semantic_error.h"
#include "scope_stack.h"
#include "symbol_table.h"

using namespace std;

class SemanticAnalyzer
{
    private:
        AbstractSyntaxTree* root;
        ScopeStack* scopeStack;
        vector<SemanticError*> errors;

    public:
        SemanticAnalyzer(AbstractSyntaxTree *root); // Constructor
        ~SemanticAnalyzer(); // Destructor

        void AddError(SemanticError* error);
        void ClearErrors();
        int GetNumberOfErrors();
        SemanticError* GetError(int index);
        SemanticError* GetFirstError();

        bool Analyze();
        bool AnalyzeNode(AbstractSyntaxTree *node);
        bool AnalyzeAstPrograma(AbstractSyntaxTree *node);
        bool AnalyzeAstElemento(AbstractSyntaxTree *node);
        bool AnalyzeAstDecGlobal(AbstractSyntaxTree *node);
        bool AnalyzeAstDecTipo(AbstractSyntaxTree *node);
        bool AnalyzeAstDecFunc(AbstractSyntaxTree *node);
        bool AnalyzeAstCabecalhoFun(AbstractSyntaxTree *node);
        int GetTypeFromAstTipo(AbstractSyntaxTree *node);
        string GetValueFromAstTipo(AbstractSyntaxTree *node);
        int GetSizeFromAstTipo(AbstractSyntaxTree *node);
        int GetTypeSize(string name);
};
