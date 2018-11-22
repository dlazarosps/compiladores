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
	// Generate a new register to put the result of this binary operation
	this->resultRegister = codeGenerator->CreateRegister();

	// Test Short Circuit AND/OR
	if ((this->operationType != BINARY_OPERATION_TYPE_AND) && (this->operationType != BINARY_OPERATION_TYPE_OR))
	{
		// Aritimetic & Relational

		// Generate code to evaluate the expressions
		this->leftExpression->GenerateCode(codeGenerator);
		this->rightExpression->GenerateCode(codeGenerator);

		// Get the registers with the final values
		string leftExpressionRegister = this->leftExpression->GetResultRegister();
		string rightExpressionRegister = this->rightExpression->GetResultRegister();

		switch (this->operationType)
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
		case BINARY_OPERATION_TYPE_BIT_AND:
			codeGenerator->AddInstruction(new InstructionILOC("", "and", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
			break;
		case BINARY_OPERATION_TYPE_BIT_OR:
			codeGenerator->AddInstruction(new InstructionILOC("", "or", leftExpressionRegister, rightExpressionRegister, this->resultRegister));
			break;
		}
	}
	else
	{
		// AND & OR Short Circuit

		// Generates a new label for this
		string labelLeft = codeGenerator->CreateLabel();
		string labelCompare = codeGenerator->CreateLabel();
		string labelRight = codeGenerator->CreateLabel();
		string labelBeTrue = codeGenerator->CreateLabel();
		string labelBeFalse = codeGenerator->CreateLabel();
		string labelEnd = codeGenerator->CreateLabel();
		string labelEndEnd = codeGenerator->CreateLabel();

		// Generate code to evaluate the expressions
		// Adds an instruction just to hold the label

		// leftExpression
		codeGenerator->AddInstruction(new InstructionILOC(labelLeft, "nop", "", "", ""));
		this->leftExpression->GenerateCode(codeGenerator);
		codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelCompare, "", ""));

		// rightExpression
		codeGenerator->AddInstruction(new InstructionILOC(labelRight, "nop", "", "", ""));
		this->rightExpression->GenerateCode(codeGenerator);
		codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelEnd, "", ""));

		// Get the registers with the final values
		string leftExpressionRegister = this->leftExpression->GetResultRegister();
		string rightExpressionRegister = this->rightExpression->GetResultRegister();

		if (this->operationType == BINARY_OPERATION_TYPE_AND)
		{
			// AND
			// leftRegister ? beTrue : beFalse
			codeGenerator->AddInstruction(new InstructionILOC(labelCompare, "cbr", leftExpressionRegister, labelBeTrue, labelBeFalse));

			//beTrue :: jump Right
			codeGenerator->AddInstruction(new InstructionILOC(labelBeTrue, "jumpI", labelRight, "", ""));

			//beFalse ::  resultRegister == Left
			codeGenerator->AddInstruction(new InstructionILOC(labelBeFalse, "i2i", leftExpressionRegister, this->resultRegister, ""));

			codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelEndEnd, "", ""));

			//RightReturn ::  resultRegister == Right
			codeGenerator->AddInstruction(new InstructionILOC(labelEnd, "i2i", rightExpressionRegister, this->resultRegister, ""));

		}
		else
		{
			// OR
			// leftRegister ? beTrue : beFalse
			codeGenerator->AddInstruction(new InstructionILOC(labelCompare, "cbr", leftExpressionRegister, labelBeTrue, labelBeFalse));

			//beFalse :: jump Right
			codeGenerator->AddInstruction(new InstructionILOC(labelBeFalse, "jumpI", labelRight, "", ""));

			//beTrue ::  resultRegister == Left
			codeGenerator->AddInstruction(new InstructionILOC(labelBeTrue, "i2i", leftExpressionRegister, this->resultRegister, ""));

			codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelEndEnd, "", ""));

			//RightReturn ::  resultRegister == Right
			codeGenerator->AddInstruction(new InstructionILOC(labelEnd, "i2i", rightExpressionRegister, this->resultRegister, ""));
		}

	}

}
