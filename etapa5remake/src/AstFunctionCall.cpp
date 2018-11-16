/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstFunctionCall.h"
#include "../include/LexicalValue.h"

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
