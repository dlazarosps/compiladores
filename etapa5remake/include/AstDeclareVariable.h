/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"

using namespace std;

class AstDeclareVariable : public AbstractSyntaxTree
{
    protected:
        string name;
        string type;
        AbstractSyntaxTree* valueContainer;
    public:
        AstDeclareVariable(LexicalValue *identifier, AbstractSyntaxTree* val); // Constructor
        ~AstDeclareVariable(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
};
