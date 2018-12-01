/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <vector>
#include "../include/AstDeclareFunction.h"
#include "../include/LexicalValue.h"
#include "../include/ScopeManager.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"
#include "../include/CodeGenerator.h"

using namespace std;

AstDeclareFunction::AstDeclareFunction(LexicalValue *identifier, vector<AbstractSyntaxTree*> *params, vector<AbstractSyntaxTree*> *cmds)
{
	this->astType = AST_TYPE_DECLARE_FUNCTION;

	this->name = identifier->ValueToString();
	this->type = "int";

	for (unsigned int i = 0; i < params->size(); i++)
	{
		this->parameters.push_back(params->at(i));
	}

	for (unsigned int i = 0; i < cmds->size(); i++)
	{
		this->commands.push_back(cmds->at(i));
	}
}

AstDeclareFunction::~AstDeclareFunction()
{

}

void AstDeclareFunction::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	// TODO check if already exists
	ScopeManager *scopeManager = semanticAnalyzer->GetScopeManager();
	SymbolTableEntry* entry = new SymbolTableEntry(this->name, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_FUN);
	scopeManager->SetCurrentScopeToGlobal();
	scopeManager->InsertEntry(entry);

	// TODO check if already exists
	scopeManager->AddFunctionScope(new SymbolTable(this->name));
	scopeManager->SetCurrentScopeByName(this->name);

	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		this->parameters.at(i)->SemanticAnalysis(semanticAnalyzer);
	}

	for (unsigned int i = 0; i < this->commands.size(); i++)
	{
		this->commands.at(i)->SemanticAnalysis(semanticAnalyzer);
	}

	scopeManager->SetCurrentScopeToGlobal();
}

void AstDeclareFunction::GenerateCode(CodeGenerator* codeGenerator)
{
	/*
	 * RA
	 * 0 	: Endereço de retorno
	 * 4 	: Valor de retorno
	 * 8 	: RFP Origem
	 * 12 	: RSP Origem
	 * 16 	: Vínculo Estático
	 * 20 	: Vínculo Dinâmico
	 * 24 	: Estado da Máquina
	 * 28 	: Parâmetro 0
	 * ...
	 * X 	: (28 + (n-1) * 4) Parâmetro n
	 * Y+4 	: Local 0
	 * ...
	 * Y 	: (Y + (n-1) * 4) Local n
	 */

	int deslocRA = 24;
	string returnRegister = codeGenerator->CreateRegister();
	string rfpRegister = codeGenerator->CreateRegister();
	string rspRegister = codeGenerator->CreateRegister();

	// Fetches the scope manager
	ScopeManager *scopeManager = codeGenerator->GetScopeManager();
	// Switches to this functions static scope
	scopeManager->SetCurrentScopeByName(this->name);
	// Generates a new label for this function
	string label = codeGenerator->CreateLabel();
	// Adds an instruction just to hold the label
	codeGenerator->AddInstruction(new InstructionILOC(label, "nop", "", "", ""));
	// Sets the label in the symbol table for future reference
	scopeManager->GetCurrentScope()->SetLabel(label);

	//config RA
	if(this->name.compare("main") != 0) {

		//atualiza RFP com valor do RSP
		codeGenerator->AddInstruction(new InstructionILOC("", "i2i", "rsp", "rfp", ""));

		//adiciona deslocamento no RSP
		deslocRA += this->parameters.size() * 4;
		// deslocRA += this->commands.size() * 4; //TODO contar variaveis locais
		codeGenerator->AddInstruction(new InstructionILOC("", "addI", "rsp", to_string(deslocRA), "rsp"));

	}

	// Calls parameter declarations
	for (unsigned int i = 0; i < this->parameters.size(); i++)
	{
		this->parameters.at(i)->GenerateCode(codeGenerator);
	}
	// Calls commands
	for (unsigned int i = 0; i < this->commands.size(); i++)
	{
		this->commands.at(i)->GenerateCode(codeGenerator);
	}

	// Se for a função main, deve encerrar o programa ao final dela
	if(this->name.compare("main") == 0) {
		codeGenerator->AddInstruction(new InstructionILOC("", "halt", "", "", ""));
	}
	/*else{

		//carrega RSP e RFP antigos
		codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", "rfp", "0", returnRegister));
		codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", "rfp", "8", rfpRegister));
		codeGenerator->AddInstruction(new InstructionILOC("", "loadAI", "rfp", "12", rspRegister));

		codeGenerator->AddInstruction(new InstructionILOC("", "i2i", rfpRegister, "rfp", ""));
		codeGenerator->AddInstruction(new InstructionILOC("", "i2i", rspRegister, "rsp", ""));

		//pula para o endereço de retorno
		codeGenerator->AddInstruction(new InstructionILOC("", "jump", returnRegister, "", ""));

	}*/
	// Switches back to the global static scope
	scopeManager->SetCurrentScopeToGlobal();
}
