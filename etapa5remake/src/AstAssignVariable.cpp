/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstAssignVariable.h"
#include "../include/LexicalValue.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTableEntry.h"

using namespace std;

AstAssignVariable::AstAssignVariable(LexicalValue *identifier, AbstractSyntaxTree* val)
{
	this->astType = AST_TYPE_ASSIGN_VARIABLE;

	this->name = identifier->ValueToString();
	this->valueContainer = val;
}

AstAssignVariable::~AstAssignVariable()
{

}

void AstAssignVariable::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}
