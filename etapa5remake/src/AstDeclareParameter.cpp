/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstDeclareParameter.h"
#include "../include/LexicalValue.h"

using namespace std;

AstDeclareParameter::AstDeclareParameter(LexicalValue *identifier)
{
	this->astType = AST_TYPE_DECLARE_PARAMETER;

	this->name = identifier->ValueToString();
	this->type = "int";
}

AstDeclareParameter::~AstDeclareParameter()
{

}
