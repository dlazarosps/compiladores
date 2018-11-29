/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AstExpression.h"
#include "LexicalValue.h"

using namespace std;

class AstLiteral : public AstExpression
{
    protected:
        int value;
    public:
        AstLiteral(LexicalValue *lex); // Constructor
        ~AstLiteral(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
