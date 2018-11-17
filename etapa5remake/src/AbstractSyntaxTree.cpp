/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AbstractSyntaxTree.h"

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
