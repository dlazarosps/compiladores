/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstDeclareGlobalVariable.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstDeclareGlobalVariable::AstDeclareGlobalVariable(LexicalValue *identifier)
{
	this->astType = AST_TYPE_DECLARE_GLOBAL_VARIABLE;

	this->name = identifier->ValueToString();
	this->type = "int";
}

AstDeclareGlobalVariable::~AstDeclareGlobalVariable()
{

}

void AstDeclareGlobalVariable::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO check if already exists
	ScopeManager *scopeManager = semanticAnalyzer->GetScopeManager();
	SymbolTableEntry* entry = new SymbolTableEntry(this->name, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_GLOBAL);
	scopeManager->SetCurrentScopeToGlobal();
	scopeManager->InsertEntry(entry);
}

void AstDeclareGlobalVariable::GenerateCode(CodeGenerator* codeGenerator)
{
	// Does nothing
}
