/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstUnaryOperation.h"
#include "../include/AstExpression.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstUnaryOperation::AstUnaryOperation(int operationType, AstExpression* expr)
{
	this->astType = AST_TYPE_UNARY_OPERATION;

	this->operationType = operationType;

	this->expression = expr;
}

AstUnaryOperation::~AstUnaryOperation()
{

}

void AstUnaryOperation::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}

void AstUnaryOperation::GenerateCode(CodeGenerator* codeGenerator)
{
	// Generate code to evaluate the expression
	this->expression->GenerateCode(codeGenerator);

	// Get the register with the final value
	string expressionRegister = this->expression->GetResultRegister();

	// Generate a new register to put the result of this unary operation
	this->resultRegister = codeGenerator->CreateRegister();

	// Variables for the negation operation
	string regNegation;
	string labelBeTrue;
	string labelEnd;

	switch(this->operationType)
	{
		case UNARY_OPERATION_TYPE_POSITIVE:
			// Simply loads the same value into the new register
			codeGenerator->AddInstruction(new InstructionILOC("", "load", expressionRegister, "", this->resultRegister));
		break;
		case UNARY_OPERATION_TYPE_NEGATIVE:
			// Loads 0 into the new register and then subtracts the value from the expression
			codeGenerator->AddInstruction(new InstructionILOC("", "loadI", "0", "", this->resultRegister));
			codeGenerator->AddInstruction(new InstructionILOC("", "sub", this->resultRegister, expressionRegister, this->resultRegister));
		break;
		case UNARY_OPERATION_TYPE_LOGICAL_NEGATION:
			regNegation = codeGenerator->CreateRegister();
			labelBeTrue = codeGenerator->CreateLabel();
			labelEnd = codeGenerator->CreateLabel();
			// Negates the value of the expression
			codeGenerator->AddInstruction(new InstructionILOC("", "loadI", "0", "", this->resultRegister));
			codeGenerator->AddInstruction(new InstructionILOC("", "cmp_EQ", expressionRegister, this->resultRegister, regNegation));
			codeGenerator->AddInstruction(new InstructionILOC("", "cbr", regNegation, labelBeTrue, labelEnd));
			codeGenerator->AddInstruction(new InstructionILOC(labelBeTrue, "loadI", "1", "", this->resultRegister));
			codeGenerator->AddInstruction(new InstructionILOC(labelEnd, "nop", "", "", ""));
		break;
	}
}
