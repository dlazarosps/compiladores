/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <vector>
#include "../include/AstIfElse.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstIfElse::AstIfElse(AstExpression *expression, vector<AbstractSyntaxTree*> *ifCommands, vector<AbstractSyntaxTree*> *elseCommands)
{
	this->astType = AST_TYPE_IF_ELSE;

	this->expression = expression;


	for (unsigned int i = 0; i < ifCommands->size(); i++)
	{
		this->ifCommands.push_back(ifCommands->at(i));
	}

	for (unsigned int i = 0; i < elseCommands->size(); i++)
	{
		this->elseCommands.push_back(elseCommands->at(i));
	}
}

AstIfElse::~AstIfElse()
{

}

void AstIfElse::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	this->expression->SemanticAnalysis(semanticAnalyzer);

	for (unsigned int i = 0; i < this->ifCommands.size(); i++)
	{
		this->ifCommands.at(i)->SemanticAnalysis(semanticAnalyzer);
	}

	for (unsigned int i = 0; i < this->elseCommands.size(); i++)
	{
		this->elseCommands.at(i)->SemanticAnalysis(semanticAnalyzer);
	}

}

void AstIfElse::GenerateCode(CodeGenerator* codeGenerator)
{
	this->expression->GenerateCode(codeGenerator);
	string expressionRegister = this->expression->GetResultRegister();
	
	string labelBeTrue = codeGenerator->CreateLabel();
	string labelBeFalse = codeGenerator->CreateLabel();
	string labelEnd = codeGenerator->CreateLabel();

	codeGenerator->AddInstruction(new InstructionILOC("", "cbr", expressionRegister, labelBeTrue, labelBeFalse));

	// IF
	codeGenerator->AddInstruction(new InstructionILOC(labelBeTrue, "nop", "", "", ""));
	
	// Loop if commands
	for (unsigned int i = 0; i < this->ifCommands.size(); i++)
	{
		this->ifCommands.at(i)->GenerateCode(codeGenerator);
	}
	codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelEnd, "", ""));


	// ELSE
	codeGenerator->AddInstruction(new InstructionILOC(labelBeFalse, "nop", "", "", ""));
	
	// Loop else commands
	for (unsigned int i = 0; i < this->elseCommands.size(); i++)
	{
		this->elseCommands.at(i)->GenerateCode(codeGenerator);
	}
	codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelEnd, "", ""));

	codeGenerator->AddInstruction(new InstructionILOC(labelEnd, "nop", "", "", ""));
}
