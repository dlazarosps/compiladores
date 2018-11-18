/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AstExpression.h"
#include "LexicalValue.h"

using namespace std;

class AstAccessVariable : public AstExpression
{
    protected:
        string name;
    public:
        AstAccessVariable(LexicalValue *identifier); // Constructor
        ~AstAccessVariable(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
