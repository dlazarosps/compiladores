/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <string>
#include "../include/AstAccessVariable.h"
#include "../include/LexicalValue.h"
#include "../include/ScopeManager.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstAccessVariable::AstAccessVariable(LexicalValue *identifier)
{
	this->astType = AST_TYPE_ACCESS_VARIABLE;

	this->name = identifier->ValueToString();
}

AstAccessVariable::~AstAccessVariable()
{

}

void AstAccessVariable::SemanticAnalysis(SemanticAnalyzer *semanticAnalyzer)
{
	//TODO
}

void AstAccessVariable::GenerateCode(CodeGenerator* codeGenerator)
{
	// Find the entry for this variable
	SymbolTableEntry *entry = codeGenerator->GetScopeManager()->LookUp(this->name);

	// Get the memory offset of this variable
	int offset = entry->GetMemoryOffset();

	// Get the correct base register (frame pointer or data segment)
	string base;
	if(entry->GetNature() == NATUREZA_GLOBAL)
		base = "rbss";
	else
		base = "rfp";

	// Creates a new register and sets the result register to it
	this->resultRegister = codeGenerator->CreateRegister();

	// Loadss the literal into the register
	codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", base, to_string(offset), this->resultRegister));
}
