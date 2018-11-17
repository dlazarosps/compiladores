/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"

using namespace std;

class AstDeclareGlobalVariable : public AbstractSyntaxTree
{
    protected:
        string name;
        string type;
    public:
        AstDeclareGlobalVariable(LexicalValue *identifier); // Constructor
        ~AstDeclareGlobalVariable(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
};
