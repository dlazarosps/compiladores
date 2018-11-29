/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "AstExpression.h"
#include "CodeGenerator.h"

using namespace std;

class AstIfElse : public AbstractSyntaxTree
{
    protected:
        AstExpression *expression;
        vector<AbstractSyntaxTree*> ifCommands;
        vector<AbstractSyntaxTree*> elseCommands;
    public:
        AstIfElse(AstExpression *expression, vector<AbstractSyntaxTree*> *ifCommands, vector<AbstractSyntaxTree*> *elseCommands); // Constructor
        ~AstIfElse(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
