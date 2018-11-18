/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "AstExpression.h"
#include "LexicalValue.h"
#include "CodeGenerator.h"

using namespace std;

class AstAssignVariable : public AbstractSyntaxTree
{
    protected:
        string name;
        AstExpression* valueContainer;
    public:
        AstAssignVariable(LexicalValue *identifier, AstExpression* val); // Constructor
        ~AstAssignVariable(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
