/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstDeclareFunction.h"
#include "../include/LexicalValue.h"

using namespace std;

AstDeclareFunction::AstDeclareFunction(LexicalValue *identifier, vector<AbstractSyntaxTree*> *params, vector<AbstractSyntaxTree*> *cmds)
{
	this->astType = AST_TYPE_DECLARE_FUNCTION;

	this->name = identifier->ValueToString();
	this->type = "int";

	for (unsigned int i = 0; i < params->size(); i++)
	{
		this->parameters.push_back(params->at(i));
	}

	for (unsigned int i = 0; i < cmds->size(); i++)
	{
		this->commands.push_back(cmds->at(i));
	}
}

AstDeclareFunction::~AstDeclareFunction()
{

}
