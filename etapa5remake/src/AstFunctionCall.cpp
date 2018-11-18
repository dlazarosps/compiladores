/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstFunctionCall.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstFunctionCall::AstFunctionCall(LexicalValue *identifier, vector<AbstractSyntaxTree*> *params)
{
	this->astType = AST_TYPE_DECLARE_FUNCTION;

	this->name = identifier->ValueToString();
	this->type = "int";

	for (unsigned int i = 0; i < params->size(); i++)
	{
		this->parameters.push_back(params->at(i));
	}
}

AstFunctionCall::~AstFunctionCall()
{

}

void AstFunctionCall::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO check if declared

	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		this->parameters.at(i)->SemanticAnalysis(semanticAnalyzer);
	}
}

void AstFunctionCall::GenerateCode(CodeGenerator* codeGenerator)
{
	//TODO
}
