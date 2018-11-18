/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <vector>
#include "../include/AstIfElse.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstIfElse::AstIfElse(AstExpression *expression, vector<AbstractSyntaxTree*> *ifCommands, vector<AbstractSyntaxTree*> *elseCommands)
{
	this->astType = AST_TYPE_IF_ELSE;

	this->expression = expression;


	for (unsigned int i = 0; i < ifCommands->size(); i++)
	{
		this->ifCommands.push_back(ifCommands->at(i));
	}

	for (unsigned int i = 0; i < elseCommands->size(); i++)
	{
		this->elseCommands.push_back(elseCommands->at(i));
	}
}

AstIfElse::~AstIfElse()
{

}

void AstIfElse::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO
}

void AstIfElse::GenerateCode(CodeGenerator* codeGenerator)
{
	// TODO
}
