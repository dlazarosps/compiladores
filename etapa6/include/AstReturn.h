/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include "AbstractSyntaxTree.h"
#include "AstExpression.h"
#include "CodeGenerator.h"

using namespace std;

class AstReturn : public AbstractSyntaxTree
{
    protected:
        AstExpression* expression;
    public:
        AstReturn(AstExpression* expression); // Constructor
        ~AstReturn(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
