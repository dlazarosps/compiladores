/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <vector>
#include "../include/AstDeclareFunction.h"
#include "../include/LexicalValue.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstDeclareFunction::AstDeclareFunction(LexicalValue *identifier, vector<AbstractSyntaxTree*> *params, vector<AbstractSyntaxTree*> *cmds)
{
	this->astType = AST_TYPE_DECLARE_FUNCTION;

	this->name = identifier->ValueToString();
	this->type = "int";

	for (unsigned int i = 0; i < params->size(); i++)
	{
		this->parameters.push_back(params->at(i));
	}

	for (unsigned int i = 0; i < cmds->size(); i++)
	{
		this->commands.push_back(cmds->at(i));
	}
}

AstDeclareFunction::~AstDeclareFunction()
{

}

void AstDeclareFunction::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO check if already exists
	ScopeManager *scopeManager = semanticAnalyzer->GetScopeManager();
	SymbolTableEntry* entry = new SymbolTableEntry(this->name, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_FUN);
	scopeManager->SetCurrentScopeToGlobal();
	scopeManager->InsertEntry(entry);

	// TODO check if already exists
	scopeManager->AddFunctionScope(new SymbolTable(this->name));
	scopeManager->SetCurrentScopeByName(this->name);

	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		this->parameters.at(i)->SemanticAnalysis(semanticAnalyzer);
	}

	for (unsigned int i = 0; i < this->commands.size(); i++)
	{
		this->commands.at(i)->SemanticAnalysis(semanticAnalyzer);
	}

	scopeManager->SetCurrentScopeToGlobal();
}

void AstDeclareFunction::GenerateCode(CodeGenerator* codeGenerator)
{
	// Fetches the scope manager
	ScopeManager *scopeManager = codeGenerator->GetScopeManager();
	// Switches to this functions static scope
	scopeManager->SetCurrentScopeByName(this->name);
	// Generates a new label for this function
	string label = codeGenerator->CreateLabel();
	// Adds an instruction just to hold the label
	codeGenerator->AddInstruction(new InstructionILOC(label, "nop", "", "", ""));
	// Sets the label in the symbol table for future reference
	scopeManager->GetCurrentScope()->SetLabel(label);
	// Calls parameter declarations
	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		this->parameters.at(i)->GenerateCode(codeGenerator);
	}
	// Calls commands
	for (unsigned int i = 0; i < this->commands.size(); i++)
	{
		this->commands.at(i)->GenerateCode(codeGenerator);
	}

	// Se for a função main, deve encerrar o programa ao final dela
	if(this->name.compare("main") == 0) {
		codeGenerator->AddInstruction(new InstructionILOC("", "halt", "", "", ""));
	}
	// Switches back to the global static scope
	scopeManager->SetCurrentScopeToGlobal();
}
