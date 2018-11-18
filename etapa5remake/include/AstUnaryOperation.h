/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "AbstractSyntaxTree.h"
#include "LexicalValue.h"
#include "CodeGenerator.h"

using namespace std;

class AstUnaryOperation : public AbstractSyntaxTree
{
    protected:
        int operationType;
        AbstractSyntaxTree* expression;
    public:
        AstUnaryOperation(int operationType, AbstractSyntaxTree* expr); // Constructor
        ~AstUnaryOperation(); // Destructor
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};

#define UNARY_OPERATION_TYPE_UNDEFINED -1
#define UNARY_OPERATION_TYPE_POSITIVE 0
#define UNARY_OPERATION_TYPE_NEGATIVE 1
#define UNARY_OPERATION_TYPE_LOGICAL_NEGATION 2
