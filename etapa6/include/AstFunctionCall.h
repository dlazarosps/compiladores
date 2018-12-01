/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "AstExpression.h"
#include "LexicalValue.h"
#include "CodeGenerator.h"

using namespace std;

class AstFunctionCall : public AstExpression
{
    protected:
        string name;
        string type;
        vector<AstExpression*> parameters;
    public:
        AstFunctionCall(LexicalValue *identifier, vector<AstExpression*> *params); // Constructor
        ~AstFunctionCall(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
