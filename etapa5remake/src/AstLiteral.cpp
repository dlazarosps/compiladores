/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <string>
#include "../include/AstLiteral.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstLiteral::AstLiteral(LexicalValue *lex)
{
	this->astType = AST_TYPE_LITERAL;

	this->value = lex->GetValue().intValue;
}

AstLiteral::~AstLiteral()
{

}

void AstLiteral::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}

void AstLiteral::GenerateCode(CodeGenerator* codeGenerator)
{
	// Creates a new register and sets the result register to it
	this->resultRegister = codeGenerator->CreateRegister();

	// Loades the literal into the register
	codeGenerator->AddInstruction(new InstructionILOC("", "loadI", to_string(this->value), "", this->resultRegister));
}
