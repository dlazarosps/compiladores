/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstAssignVariable.h"
#include "../include/LexicalValue.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstAssignVariable::AstAssignVariable(LexicalValue *identifier, AstExpression* val)
{
	this->astType = AST_TYPE_ASSIGN_VARIABLE;

	this->name = identifier->ValueToString();
	this->valueContainer = val;
}

AstAssignVariable::~AstAssignVariable()
{

}

void AstAssignVariable::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}

void AstAssignVariable::GenerateCode(CodeGenerator* codeGenerator)
{
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
