/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include <vector>
#include "../include/AbstractSyntaxTree.h"
#include "../include/ScopeManager.h"
#include "../include/InstructionILOC.h"
#include "../include/CodeGenerator.h"

using namespace std;

class CodeGenerator
{
    private:
        int registersUsed;
        int labelsUsed;
        vector<InstructionILOC*> instructions;
        AbstractSyntaxTree* root;
        ScopeManager* scopeManager;

    public:
        CodeGenerator(AbstractSyntaxTree* root, ScopeManager* scopeManager);
        ~CodeGenerator();
        void Generate();
        string CreateRegister();
        string CreateLabel();
        void AddInstruction(InstructionILOC* instruction);
        ScopeManager* GetScopeManager();
        void Print();
};
