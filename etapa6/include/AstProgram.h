/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include "AbstractSyntaxTree.h"
#include "CodeGenerator.h"

using namespace std;

class AstProgram : public AbstractSyntaxTree
{
    protected:
        vector<AbstractSyntaxTree*> elements;
    public:
        AstProgram(); // Constructor
        ~AstProgram(); // Destructor
        void addElement(AbstractSyntaxTree* element);
        void addElements(vector<AbstractSyntaxTree*> *listOfElements);
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};
