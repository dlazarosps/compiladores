/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <vector>
#include "../include/AbstractSyntaxTree.h"
#include "../include/SemanticAnalyzer.h"
#include "../include/ScopeManager.h"
#include "../include/SemanticError.h"

using namespace std;

SemanticAnalyzer::SemanticAnalyzer(AbstractSyntaxTree *root)
{
    this->root = root;
    this->scopeManager = new ScopeManager();
}

SemanticAnalyzer::~SemanticAnalyzer()
{
    //TODO
}

SemanticError* SemanticAnalyzer::GetFirstError()
{
    if(this->HasErrors())
        return this->errors.at(0);
    else
        return NULL;
}

bool SemanticAnalyzer::HasErrors()
{
    return (this->errors.size() > 0);
}

bool SemanticAnalyzer::Analyze()
{
    this->root->SemanticAnalysis(this);

    return this->HasErrors();
}

ScopeManager* SemanticAnalyzer::GetScopeManager()
{
    return this->scopeManager;
}

void SemanticAnalyzer::AddError(int code, int line, string text)
{
    this->errors.push_back(new SemanticError(code,line,text));
}
