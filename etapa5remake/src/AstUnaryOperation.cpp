/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstUnaryOperation.h"
#include "../include/LexicalValue.h"

using namespace std;

AstUnaryOperation::AstUnaryOperation(int operationType, AbstractSyntaxTree* expr)
{
	this->astType = AST_TYPE_UNARY_OPERATION;

	this->operationType = operationType;

	this->expression = expr;
}

AstUnaryOperation::~AstUnaryOperation()
{

}
