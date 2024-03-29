/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"
#include "CodeGenerator.h"

using namespace std;

class AstDeclareParameter : public AbstractSyntaxTree
{
    protected:
        string name;
        string type;
    public:
        AstDeclareParameter(LexicalValue *identifier); // Constructor
        ~AstDeclareParameter(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
