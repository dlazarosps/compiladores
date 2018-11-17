/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstAccessVariable.h"
#include "../include/LexicalValue.h"
#include "../include/ScopeManager.h"

using namespace std;

AstAccessVariable::AstAccessVariable(LexicalValue *identifier)
{
	this->astType = AST_TYPE_ACCESS_VARIABLE;

	this->name = identifier->ValueToString();
}

AstAccessVariable::~AstAccessVariable()
{

}

void AstAccessVariable::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}
