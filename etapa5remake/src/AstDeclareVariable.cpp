/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstDeclareVariable.h"
#include "../include/LexicalValue.h"

using namespace std;

AstDeclareVariable::AstDeclareVariable(LexicalValue *identifier, AbstractSyntaxTree* val)
{
	this->astType = AST_TYPE_DECLARE_VARIABLE;

	this->name = identifier->ValueToString();
	this->type = "int";
	this->valueContainer = val;
}

AstDeclareVariable::~AstDeclareVariable()
{

}
