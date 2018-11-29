/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */
#include <string>
#include "../include/InstructionILOC.h"

using namespace std;

InstructionILOC::InstructionILOC(string label, string code, string arg1, string arg2, string arg3)
{
    this->label = label;
    this->code = code;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->arg3 = arg3;
}

InstructionILOC::~InstructionILOC()
{
    // TODO: clean up
}

string InstructionILOC::GetInstructionCode()
{
    return this->code;
}

string InstructionILOC::GetInstructionLabel()
{
    return this->label;
}

string InstructionILOC::GetArg1()
{
    return this->arg1;
}

string InstructionILOC::GetArg2()
{
    return this->arg2;
}

string InstructionILOC::GetArg3()
{
    return this->arg3;
}

void InstructionILOC::SetInstructionCode(string code)
{
    this->code = code;
}

void InstructionILOC::SetInstructionLabel(string label)
{
    this->label = label;
}

void InstructionILOC::SetArg1(string arg1)
{
    this->arg1 = arg1;
}

void InstructionILOC::SetArg2(string arg2)
{
    this->arg2 = arg2;
}

void InstructionILOC::SetArg3(string arg3)
{
    this->arg3 = arg3;
}

string InstructionILOC::GetILOC()
{
    string instrILOC;

    instrILOC = (!this->label.empty()) ? this->label + ":" : "";

    if (this->code.find("load") != std::string::npos){
    //Intruções de LOAD :: code arg1,arg2 => arg3
        //indireto/deslocamento usando arg2
        if ((this->code.find("AI") != std::string::npos) || (this->code.find("A0") != std::string::npos)){
            instrILOC += this->code + " " + this->arg1 + ", " + this->arg2 + " => " + this->arg3;
        }
        else{
            //TODO check loadI
            // loadI c1 => r2
            // SE loadI for mapeado para  c1 == arg1 & r2 == arg3 vai funcionar
            instrILOC += this->code + " " + this->arg1 + " => " + this->arg3;
        }

    }
    else if(this->code.find("store") != std::string::npos){
    //Intruções de STORE :: code arg1 => arg2,arg3
        //indireto/deslocamento usando arg3
        if ((this->code.find("AI") != std::string::npos) || (this->code.find("A0") != std::string::npos)){
            instrILOC += this->code + " " + this->arg1 + " => " + this->arg2 + ", " + this->arg3;
        }
        else{
            instrILOC += this->code + " " + this->arg1 + " => " + this->arg2;
        }
    }
    else if(this->code.find("2") != std::string::npos){
    //Intruções de COPY :: code arg1 => arg2
        instrILOC += this->code + " " + this->arg1 + " => " + this->arg2;
    }
    else if(this->code.find("jump") != std::string::npos){
    //Instrução JUMP
        instrILOC += this->code + " -> " + this->arg1;
    }
    else if(this->code.find("cbr") != std::string::npos){
    //Instrução CBR
        instrILOC += this->code + " " + this->arg1 + " -> " + this->arg2 + ", " + this->arg3;
    }
    else if(this->code.find("cmp") != std::string::npos){
    //Instrução CMP :: code arg1, arg2 => arg3
        instrILOC += this->code + " " + this->arg1 + ", " + this->arg2 + " -> " + this->arg3;
    }
    else if(this->code.find("nop") != std::string::npos){
    //Instrução NOP
        instrILOC += this->code;
    }
    else if (this->code.find("halt") != std::string::npos)
    {
        //Instrução rotulo
        instrILOC += this->code;
    }
    else{
    //Instruções ARTIMÉTICAS / SHIFTS / BOOL :: code arg1, arg2 => arg3
        instrILOC += this->code + " " + this->arg1 + ", " + this->arg2 + " => " + this->arg3;
    }

    return instrILOC;
}
