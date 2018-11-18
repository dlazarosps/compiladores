/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
#include <iostream>
#include <vector>
#include <string>
#include "../include/AbstractSyntaxTree.h"
#include "../include/ScopeManager.h"
#include "../include/InstructionILOC.h"
#include "../include/CodeGenerator.h"

using namespace std;

CodeGenerator::CodeGenerator(AbstractSyntaxTree* root, ScopeManager* scopeManager)
{
    this->registersUsed = 0;
    this->labelsUsed = 0;
    this->root = root;
    this->scopeManager = scopeManager;
}

CodeGenerator::~CodeGenerator()
{
    //TODO
}

void CodeGenerator::Generate()
{
    this->AddInstruction(new InstructionILOC("", "loadI", "1024", "", "rfp"));
    this->AddInstruction(new InstructionILOC("", "loadI", "1024", "", "rsp"));
    this->AddInstruction(new InstructionILOC("", "loadI", "512", "", "rbss"));
    //this->AddInstruction(new InstructionILOC("", "jumpI", ENDERECO_DA_MAIN, "", ""));

    root->GenerateCode(this);

    this->AddInstruction(new InstructionILOC("", "halt", "","",""));
}

string CodeGenerator::CreateRegister()
{
    string reg = "r" + to_string(this->registersUsed);
    this->registersUsed++;
    return reg;
}

string CodeGenerator::CreateLabel()
{
    string lab = "L" + to_string(this->labelsUsed);
    this->labelsUsed++;
    return lab;
}

void CodeGenerator::AddInstruction(InstructionILOC* instruction)
{
    this->instructions.push_back(instruction);
}

ScopeManager* CodeGenerator::GetScopeManager()
{
    return this->scopeManager;
}

void CodeGenerator::Print()
{
    for (unsigned int i = 0; i < this->instructions.size(); i++)
	{
		cout << this->instructions.at(i)->GetILOC() + "\n";
	}
}
