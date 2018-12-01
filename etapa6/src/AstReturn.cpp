/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstReturn.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstReturn::AstReturn(AstExpression* expression)
{
	this->astType = AST_TYPE_RETURN;

	this->expression = expression;
}

AstReturn::~AstReturn()
{

}

void AstReturn::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	//TODO
}

void AstReturn::GenerateCode(CodeGenerator* codeGenerator)
{
	// Avalia a expressão de retorno
	this->expression->GenerateCode(codeGenerator);

	// Pega o registrador com o resultado da expressão de retorno
	string returnValueRegister = this->expression->GetResultRegister();

	// Registradores para guardar os ponteiros da RA
	string returnAddressRegister = codeGenerator->CreateRegister();
	string rspRegister = codeGenerator->CreateRegister();
	string rfpRegister = codeGenerator->CreateRegister();

	// Recupera os ponteiros do RA
	codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", "rfp", "0", returnAddressRegister));
	codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", returnValueRegister, "rfp", "4"));
	codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", "rfp", "8", rfpRegister));
	codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", "rfp", "12", rspRegister));

	// Atualiza os valores dos registradores do Stack Pointer e do Frame Pointer
	codeGenerator->AddInstruction(new InstructionILOC("", "i2i", rspRegister, "rsp", ""));
	codeGenerator->AddInstruction(new InstructionILOC("", "i2i", rfpRegister, "rfp", ""));

	// Salta para o endereço de retorno
	codeGenerator->AddInstruction(new InstructionILOC("", "jump", returnAddressRegister, "", ""));
}
