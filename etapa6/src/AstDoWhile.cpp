/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <vector>
#include "../include/AstDoWhile.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstDoWhile::AstDoWhile(bool testFirst, AstExpression *expression, vector<AbstractSyntaxTree*> *commands)
{
	this->astType = AST_TYPE_DO_WHILE;

	this->testFirst = testFirst;

	this->expression = expression;

	for (unsigned int i = 0; i < commands->size(); i++)
	{
		this->commands.push_back(commands->at(i));
	}
}

AstDoWhile::~AstDoWhile()
{

}

void AstDoWhile::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	this->expression->SemanticAnalysis(semanticAnalyzer);
	
	for (unsigned int i = 0; i < this->commands.size(); i++)
	{
		this->commands.at(i)->SemanticAnalysis(semanticAnalyzer);
	}
}

void AstDoWhile::GenerateCode(CodeGenerator* codeGenerator)
{
	string labelExpr = codeGenerator->CreateLabel();
	string labelBegin = codeGenerator->CreateLabel();
	string labelBeTrue = codeGenerator->CreateLabel();
	string labelEnd = codeGenerator->CreateLabel();

	if(this->testFirst)
	{
		// WHILE
		// Expr
		codeGenerator->AddInstruction(new InstructionILOC(labelExpr, "nop", "", "", ""));
		
		this->expression->GenerateCode(codeGenerator);
		string expressionRegister = this->expression->GetResultRegister();
		
		codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelBegin, "", ""));

		// Test Expr
		codeGenerator->AddInstruction(new InstructionILOC(labelBegin, "cbr", expressionRegister, labelBeTrue, labelEnd));

		codeGenerator->AddInstruction(new InstructionILOC(labelBeTrue, "nop", "", "", ""));
		// Loop commands
		for (unsigned int i = 0; i < this->commands.size(); i++)
		{
			this->commands.at(i)->GenerateCode(codeGenerator);
		}
		codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelExpr, "", "")); // return expr to test

		codeGenerator->AddInstruction(new InstructionILOC(labelEnd, "nop", "", "", "")); // out of loop
	}
	else
	{
		// DO WHILE
		
		codeGenerator->AddInstruction(new InstructionILOC(labelBeTrue, "nop", "", "", ""));
		// Loop commands
		for (unsigned int i = 0; i < this->commands.size(); i++)
		{
			this->commands.at(i)->GenerateCode(codeGenerator);
		}
		codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelExpr, "", ""));

		// Expr
		codeGenerator->AddInstruction(new InstructionILOC(labelExpr, "nop", "", "", ""));

		this->expression->GenerateCode(codeGenerator);
		string expressionRegister = this->expression->GetResultRegister();

		codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelBegin, "", ""));

		// Test Expr
		codeGenerator->AddInstruction(new InstructionILOC(labelBegin, "cbr", expressionRegister, labelBeTrue, labelEnd));

		codeGenerator->AddInstruction(new InstructionILOC(labelEnd, "nop", "", "", "")); // out of loop
	}

}
