/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include "AstExpression.h"
#include "CodeGenerator.h"

using namespace std;

class AstBinaryOperation : public AstExpression
{
    protected:
        int operationType;
        AbstractSyntaxTree* leftExpression;
        AbstractSyntaxTree* rightExpression;
    public:
        AstBinaryOperation(AbstractSyntaxTree* leftExpression, int operationType, AbstractSyntaxTree* rightExpression); // Constructor
        ~AstBinaryOperation(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};

#define BINARY_OPERATION_TYPE_UNDEFINED -1
#define BINARY_OPERATION_TYPE_SUM 0
#define BINARY_OPERATION_TYPE_SUBTRACT 1
#define BINARY_OPERATION_TYPE_DIVIDE 2
#define BINARY_OPERATION_TYPE_MULTIPLY 3
#define BINARY_OPERATION_TYPE_POWER 4
#define BINARY_OPERATION_TYPE_LESS_THAN 5
#define BINARY_OPERATION_TYPE_GREATER_THAN 6
#define BINARY_OPERATION_TYPE_LE 7
#define BINARY_OPERATION_TYPE_GE 8
#define BINARY_OPERATION_TYPE_EQ 9
#define BINARY_OPERATION_TYPE_NE 10
#define BINARY_OPERATION_TYPE_AND 11
#define BINARY_OPERATION_TYPE_OR 12
