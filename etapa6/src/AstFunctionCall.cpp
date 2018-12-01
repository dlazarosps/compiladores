/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstFunctionCall.h"
#include "../include/LexicalValue.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstFunctionCall::AstFunctionCall(LexicalValue *identifier, vector<AstExpression*> *params)
{
	this->astType = AST_TYPE_DECLARE_FUNCTION;

	this->name = identifier->ValueToString();
	this->type = "int";

	for (unsigned int i = 0; i < params->size(); i++)
	{
		this->parameters.push_back(params->at(i));
	}
}

AstFunctionCall::~AstFunctionCall()
{

}

void AstFunctionCall::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO check if declared

	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		this->parameters.at(i)->SemanticAnalysis(semanticAnalyzer);
	}
}

void AstFunctionCall::GenerateCode(CodeGenerator* codeGenerator)
{
	int deslocRA = 28;
	string targetFunctionLabel;
	string exprRegister;
	string returnRegister = codeGenerator->CreateRegister();
	string resultRegister = codeGenerator->CreateRegister();

	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		//gera código para o parametro
		this->parameters.at(i)->GenerateCode(codeGenerator);

		//empilha parametro no RA
		exprRegister = this->parameters.at(i)->GetResultRegister();
		codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", exprRegister, "rsp", to_string(deslocRA + (i * 4))));
	}

	//salva RSP e RFP em registradores
	codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", "rfp", "rsp", "8"));
	codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", "rsp", "rsp", "12"));

	// calcula endereço de retorno
	codeGenerator->AddInstruction(new InstructionILOC("", "addI", "rpc", "3", returnRegister));
	codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", returnRegister, "rsp", "0"));

	//pula para o label da função
	ScopeManager* scopeManager = codeGenerator->GetScopeManager();
	SymbolTable *funTable = scopeManager->GetScopeByName(this->name);
	targetFunctionLabel = funTable->GetLabel();
	codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", targetFunctionLabel, "", ""));

	//ponto de retorno, pega o valor de retorno e bota no result register
	codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", "rsp", "4", resultRegister));

	this->resultRegister = resultRegister;
}
