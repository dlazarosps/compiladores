/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstBinaryOperation.h"
#include "../include/LexicalValue.h"

using namespace std;

AstBinaryOperation::AstBinaryOperation(AbstractSyntaxTree* leftExpression, int operationType, AbstractSyntaxTree* rightExpression)
{
	this->astType = AST_TYPE_BINARY_OPERATION;

	this->operationType = operationType;

	this->leftExpression = leftExpression;
	this->rightExpression = rightExpression;
}

AstBinaryOperation::~AstBinaryOperation()
{

}
