/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"

using namespace std;

class AstDeclareFunction : public AbstractSyntaxTree
{
    protected:
        string name;
        string type;
        vector<AbstractSyntaxTree*> parameters;
        vector<AbstractSyntaxTree*> commands;
    public:
        AstDeclareFunction(LexicalValue *identifier, vector<AbstractSyntaxTree*> *params, vector<AbstractSyntaxTree*> *cmds); // Constructor
        ~AstDeclareFunction(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
};
