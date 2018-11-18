/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

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
	//TODO
}
