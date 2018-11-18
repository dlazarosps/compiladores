/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AbstractSyntaxTree.h"

using namespace std;

class AstExpression : public AbstractSyntaxTree
{
    protected:
        string resultRegister;
    public:
        AstExpression(); // Constructor
        ~AstExpression(); // Destructor
        string GetResultRegister(); // Holder the register that will contain the result from this operation
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
