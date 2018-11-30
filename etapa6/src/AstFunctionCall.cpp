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
	/* ETAPA 6
		[OK]	Salva RSP e RFP da função chamadora

		[TODO]	Empilha parametros
				PREENCHE dados do RA
				1 load + 1 store para cada parametro

		[?]		calcula o endereço de retorno
				precisa avaliar todos os parametros
				e somar com as instruções de controle

		[OK]	salva endereço de retorno em REGISTRADOR

		[TODO]	JUMP label function
				esse label precisa ficar salvo na HASH para poder carregar em qualquer chamada de função
				ele é gerado na DECFUN

		[OK]	retorna para depois do JUMP
				valor calculado

		[?]		carrega valor de retorno 
	*/

	int endReturn = 1;
	string labelFun;
	string returnRegister = codeGenerator->CreateRegister();

	//TODO empilha parametros no RA
	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		this->parameters.at(i)->GenerateCode(codeGenerator);
	}

	// calcula endereço de retorno
	//TODO CALCULO
	codeGenerator->AddInstruction(new InstructionILOC("", "addI", "rpc", to_string(endReturn), returnRegister));
	codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", returnRegister, "rfp", "0"));
	
	//salva RSP e RFP em registradores
	codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", "rfp", "rsp", "8"));
	codeGenerator->AddInstruction(new InstructionILOC("", "storeAI", "rsp", "rsp", "12"));

	//pula para o label da função
	ScopeManager* scopeManager = codeGenerator->GetScopeManager();
	SymbolTable *funTable = scopeManager->GetScopeByName(this->name);
	labelFun = funTable->GetLabel();
	codeGenerator->AddInstruction(new InstructionILOC("", "jumpI", labelFun, "", ""));

	//ponto de retorno
	codeGenerator->AddInstruction(new InstructionILOC("", "nop", "", "", ""));

	//o valor de retorno tem q ser salvo em algum lugar ?
}
