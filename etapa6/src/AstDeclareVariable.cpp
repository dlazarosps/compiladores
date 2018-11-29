/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <string>
#include "../include/AstDeclareVariable.h"
#include "../include/AstExpression.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"
#include "../include/SymbolTableEntry.h"

using namespace std;

AstDeclareVariable::AstDeclareVariable(LexicalValue *identifier, AstExpression* val)
{
	this->astType = AST_TYPE_DECLARE_VARIABLE;

	this->name = identifier->ValueToString();
	this->type = "int";
	this->valueContainer = val;
}

AstDeclareVariable::~AstDeclareVariable()
{

}

void AstDeclareVariable::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO check if already exists
	ScopeManager *scopeManager = semanticAnalyzer->GetScopeManager();
	SymbolTableEntry* entry = new SymbolTableEntry(this->name, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_VAR);
	scopeManager->InsertEntry(entry);
}

void AstDeclareVariable::GenerateCode(CodeGenerator* codeGenerator)
{
	// If is declaring AND assigning a value to this variable
	if(this->valueContainer != NULL) {
		// Find the entry for this variable
		SymbolTableEntry *entry = codeGenerator->GetScopeManager()->LookUp(this->name);

		// Generate code to evaluate the expression on the right side
		this->valueContainer->GenerateCode(codeGenerator);

		// Get the register with the final value
		string result = this->valueContainer->GetResultRegister();

		// Get the memory offset of this variable
		int offset = entry->GetMemoryOffset();

		// Get the correct base register (frame pointer or data segment)
		string base;
		if(entry->GetNature() == NATUREZA_GLOBAL)
			base = "rbss";
		else
			base = "rfp";

		// Store the value from the result register in the right position
		codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", result, base, to_string(offset)));
	}
}
