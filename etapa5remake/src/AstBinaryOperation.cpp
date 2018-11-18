/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstBinaryOperation.h"
#include "../include/AstExpression.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstBinaryOperation::AstBinaryOperation(AstExpression* leftExpression, int operationType, AstExpression* rightExpression)
{
	this->astType = AST_TYPE_BINARY_OPERATION;

	this->operationType = operationType;

	this->leftExpression = leftExpression;
	this->rightExpression = rightExpression;
}

AstBinaryOperation::~AstBinaryOperation()
{

}

void AstBinaryOperation::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}

void AstBinaryOperation::GenerateCode(CodeGenerator* codeGenerator)
{
	// Generate code to evaluate the expressions
	this->leftExpression->GenerateCode(codeGenerator);
	this->rightExpression->GenerateCode(codeGenerator);

	// Get the registers with the final values
	string leftExpressionRegister = this->leftExpression->GetResultRegister();
	string rightExpressionRegister = this->rightExpression->GetResultRegister();

	// Generate a new register to put the result of this binary operation
	this->resultRegister = codeGenerator->CreateRegister();

	switch(this->operationType)
	{
		case BINARY_OPERATION_TYPE_SUM:
			codeGenerator->AddInstruction(new InstructionILOC("", "add", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_SUBTRACT:
			codeGenerator->AddInstruction(new InstructionILOC("", "sub", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_DIVIDE:
			codeGenerator->AddInstruction(new InstructionILOC("", "div", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_MULTIPLY:
			codeGenerator->AddInstruction(new InstructionILOC("", "mult", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_POWER:
			//TODO
		break;
		case BINARY_OPERATION_TYPE_LESS_THAN:
			codeGenerator->AddInstruction(new InstructionILOC("", "cmp_LT", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_GREATER_THAN:
			codeGenerator->AddInstruction(new InstructionILOC("", "cmp_GT", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_LE:
			codeGenerator->AddInstruction(new InstructionILOC("", "cmp_LE", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_GE:
			codeGenerator->AddInstruction(new InstructionILOC("", "cmp_GE", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_EQ:
			codeGenerator->AddInstruction(new InstructionILOC("", "cmp_EQ", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_NE:
			codeGenerator->AddInstruction(new InstructionILOC("", "cmp_NE", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_AND:
			codeGenerator->AddInstruction(new InstructionILOC("", "and", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
		case BINARY_OPERATION_TYPE_OR:
			codeGenerator->AddInstruction(new InstructionILOC("", "or", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
		break;
	}
}
