/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>

using namespace std;

class InstructionILOC
{
    private:
    string label;
    string code;
    string arg1;
    string arg2;
    string arg3;

    public:
    InstructionILOC(string label, string code, string arg1, string arg2, string arg3);    // Constructor
    ~InstructionILOC();                                                     // Destructor
    string GetInstructionCode();
    string GetInstructionLabel();
    string GetArg1();
    string GetArg2();
    string GetArg3();
    void SetInstructionCode(string code);
    void SetInstructionLabel(string code);
    void SetArg1(string arg1);
    void SetArg2(string arg2);
    void SetArg3(string arg3);
    string GetILOC();
};
