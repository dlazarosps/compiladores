/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstAccessVariable.h"
#include "../include/LexicalValue.h"
#include "../include/ScopeManager.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstExpression::AstExpression()
{
	this->astType = AST_TYPE_UNDEFINED;
}

AstExpression::~AstExpression()
{

}

string AstExpression::GetResultRegister()
{
	return this->resultRegister;
}

void AstExpression::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{

}

void AstExpression::GenerateCode(CodeGenerator* codeGenerator)
{

}
