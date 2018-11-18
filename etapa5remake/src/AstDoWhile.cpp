/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <vector>
#include "../include/AstDoWhile.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstDoWhile::AstDoWhile(bool testFirst, AstExpression *expression, vector<AbstractSyntaxTree*> *commands)
{
	this->astType = AST_TYPE_DO_WHILE;

	this->testFirst = testFirst;

	this->expression = expression;

	for (unsigned int i = 0; i < commands->size(); i++)
	{
		this->commands.push_back(commands->at(i));
	}
}

AstDoWhile::~AstDoWhile()
{

}

void AstDoWhile::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO
}

void AstDoWhile::GenerateCode(CodeGenerator* codeGenerator)
{
	// TODO
}
