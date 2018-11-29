/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "AstExpression.h"
#include "CodeGenerator.h"

using namespace std;

class AstDoWhile : public AbstractSyntaxTree
{
    protected:
        bool testFirst; // Is true if the expression comes first (while). Is false if the expresion comes after (do while)
        AstExpression *expression;
        vector<AbstractSyntaxTree*> commands;
    public:
        AstDoWhile(bool testFirst, AstExpression *expression, vector<AbstractSyntaxTree*> *commands); // Constructor
        ~AstDoWhile(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
