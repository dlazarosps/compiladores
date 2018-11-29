/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */
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
    // Generate the code for the program
    root->GenerateCode(this);

    // Make the first line of code jump to the beginning of the 'main' function
    SymbolTable *mainTable = this->scopeManager->GetScopeByName("main");
    string mainLabel;
    if(mainTable != NULL) {
        mainLabel = mainTable->GetLabel();
        this->instructions.insert(this->instructions.begin(), new InstructionILOC("", "jumpI", mainLabel, "", ""));
    }
    else {
        cout << "\nErro! Main não encontrada!\n"; // TODO tratar melhor isso
    }

    // Position the pointers nicely according to the sizes of the segments
    int sizeOfCodeSegment = this->instructions.size() + 3; // +3 because o the 3 instructions below
    int sizeOfDataSegment = this->scopeManager->GetScopeByName("_GLOBAL_")->GetSize();

    this->instructions.insert(this->instructions.begin(), new InstructionILOC("", "loadI", to_string(sizeOfCodeSegment+1+sizeOfDataSegment+1), "", "rfp"));
    this->instructions.insert(this->instructions.begin(), new InstructionILOC("", "loadI", to_string(sizeOfCodeSegment+1+sizeOfDataSegment+1), "", "rsp"));
    this->instructions.insert(this->instructions.begin(), new InstructionILOC("", "loadI", to_string(sizeOfCodeSegment+1), "", "rbss"));
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
