/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"

using namespace std;

class AstFunctionCall : public AbstractSyntaxTree
{
    protected:
        string name;
        string type;
        vector<AbstractSyntaxTree*> parameters;
    public:
        AstFunctionCall(LexicalValue *identifier, vector<AbstractSyntaxTree*> *params); // Constructor
        ~AstFunctionCall(); // Destructor
};
