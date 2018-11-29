/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AbstractSyntaxTree.h"
#include "../include/CodeGenerator.h"

using namespace std;

AbstractSyntaxTree::AbstractSyntaxTree()
{
	this->astType = AST_TYPE_UNDEFINED;
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{

}

int AbstractSyntaxTree::GetAstType()
{
	return this->astType;
}

void AbstractSyntaxTree::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{

}

void AbstractSyntaxTree::GenerateCode(CodeGenerator* codeGenerator)
{

}
