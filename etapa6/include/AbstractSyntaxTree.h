/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include "SemanticAnalyzer.h"
#include "CodeGenerator.h"

using namespace std;

class SemanticAnalyzer;

class AbstractSyntaxTree
{
    protected:
        int astType;
    public:
        AbstractSyntaxTree(); // Constructor
        virtual ~AbstractSyntaxTree(); // Destructor
        int GetAstType();
        virtual void SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer);
        virtual void GenerateCode(CodeGenerator* codeGenerator);
};

/*
 * Constantes Tipos de produções AST
 */
#define AST_TYPE_UNDEFINED -1
#define AST_TYPE_PROGRAM 0
#define AST_TYPE_DECLARE_GLOBAL_VARIABLE 1
#define AST_TYPE_DECLARE_FUNCTION 2
#define AST_TYPE_DECLARE_PARAMETER 3
#define AST_TYPE_DECLARE_VARIABLE 4
#define AST_TYPE_ASSIGN_VARIABLE 5
#define AST_TYPE_ACCESS_VARIABLE 6
#define AST_TYPE_LITERAL 7
#define AST_TYPE_UNARY_OPERATION 8
#define AST_TYPE_BINARY_OPERATION 9
#define AST_TYPE_RETURN 10
#define AST_TYPE_IF_ELSE 11
#define AST_TYPE_DO_WHILE 12
