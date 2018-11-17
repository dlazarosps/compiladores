/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "SemanticError.h"
#include "AbstractSyntaxTree.h"
#include "ScopeManager.h"

using namespace std;

class AbstractSyntaxTree;

class SemanticAnalyzer
{
    protected:
        AbstractSyntaxTree *root;
        ScopeManager *scopeManager;
        vector<SemanticError*> errors;
    public:
        SemanticAnalyzer(AbstractSyntaxTree *root); // Constructor
        ~SemanticAnalyzer(); // Destructor
        SemanticError* GetFirstError();
        bool HasErrors();
        bool Analyze();
        ScopeManager* GetScopeManager();
        void AddError(int code, int line, string text);
};
