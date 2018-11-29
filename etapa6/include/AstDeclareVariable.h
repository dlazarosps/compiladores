/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AbstractSyntaxTree.h"
#include "AstExpression.h"
#include "LexicalValue.h"
#include "CodeGenerator.h"

using namespace std;

class AstDeclareVariable : public AbstractSyntaxTree
{
    protected:
        string name;
        string type;
        AstExpression* valueContainer;
    public:
        AstDeclareVariable(LexicalValue *identifier, AstExpression* val); // Constructor
        ~AstDeclareVariable(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
