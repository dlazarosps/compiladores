/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstDeclareParameter.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstDeclareParameter::AstDeclareParameter(LexicalValue *identifier)
{
	this->astType = AST_TYPE_DECLARE_PARAMETER;

	this->name = identifier->ValueToString();
	this->type = "int";
}

AstDeclareParameter::~AstDeclareParameter()
{

}

void AstDeclareParameter::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO check if already exists
	ScopeManager *scopeManager = semanticAnalyzer->GetScopeManager();
	SymbolTableEntry* entry = new SymbolTableEntry(this->name, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_VAR);
	scopeManager->InsertEntry(entry);
}

void AstDeclareParameter::GenerateCode(CodeGenerator* codeGenerator)
{
	//TODO
}
