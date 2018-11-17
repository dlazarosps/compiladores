/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"

using namespace std;

class AstAssignVariable : public AbstractSyntaxTree
{
    protected:
        string name;
        AbstractSyntaxTree* valueContainer;
    public:
        AstAssignVariable(LexicalValue *identifier, AbstractSyntaxTree* val); // Constructor
        ~AstAssignVariable(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
};
