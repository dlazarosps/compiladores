/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstDeclareGlobalVariable.h"
#include "../include/LexicalValue.h"

using namespace std;

AstDeclareGlobalVariable::AstDeclareGlobalVariable(LexicalValue *identifier)
{
	this->astType = AST_TYPE_DECLARE_GLOBAL_VARIABLE;

	this->name = identifier->ValueToString();
	this->type = "int";
}

AstDeclareGlobalVariable::~AstDeclareGlobalVariable()
{

}
