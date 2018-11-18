/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstReturn.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstReturn::AstReturn(AstExpression* expression)
{
	this->astType = AST_TYPE_RETURN;

	this->expression = expression;
}

AstReturn::~AstReturn()
{

}

void AstReturn::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}

void AstReturn::GenerateCode(CodeGenerator* codeGenerator)
{
	// TODO Etapa 6
}
