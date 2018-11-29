/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AstExpression.h"
#include "LexicalValue.h"
#include "CodeGenerator.h"

using namespace std;

class AstUnaryOperation : public AstExpression
{
    protected:
        int operationType;
        AstExpression* expression;
    public:
        AstUnaryOperation(int operationType, AstExpression* expr); // Constructor
        ~AstUnaryOperation(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};

#define UNARY_OPERATION_TYPE_UNDEFINED -1
#define UNARY_OPERATION_TYPE_POSITIVE 0
#define UNARY_OPERATION_TYPE_NEGATIVE 1
#define UNARY_OPERATION_TYPE_LOGICAL_NEGATION 2
