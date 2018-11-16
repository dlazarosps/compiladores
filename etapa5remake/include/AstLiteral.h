/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"

using namespace std;

class AstLiteral : public AbstractSyntaxTree
{
    protected:
        int value;
    public:
        AstLiteral(LexicalValue *lex); // Constructor
        ~AstLiteral(); // Destructor
};
