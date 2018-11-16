/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstAssignVariable.h"
#include "../include/LexicalValue.h"

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
