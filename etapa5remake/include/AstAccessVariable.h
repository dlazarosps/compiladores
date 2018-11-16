/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"

using namespace std;

class AstAccessVariable : public AbstractSyntaxTree
{
    protected:
        string name;
    public:
        AstAccessVariable(LexicalValue *identifier); // Constructor
        ~AstAccessVariable(); // Destructor
};
