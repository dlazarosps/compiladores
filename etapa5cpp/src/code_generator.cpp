/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <stack>
#include "../include/code_generator.h"
#include "../include/semantic_analyzer.h"
#include "../include/semantic_error.h"
#include "../include/parser.tab.h"
#include "../include/ast.h"
#include "../include/scope_stack.h"
#include "../include/symbol_table.h"

using namespace std;

/*
 * InstructionILOC functions
 */

InstructionILOC::InstructionILOC(string code, string arg1, string arg2, string arg3)
{
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
    if (this->code.find("load") != std::string::npos){ 
    //Intruções de LOAD :: code arg1,arg2 => arg3
        //indireto/deslocamento usando arg2
        if ((this->code.find("AI") != std::string::npos) || (this->code.find("A0") != std::string::npos)){
            return this->code + " " + this->arg1 + ", " + this->arg2 + " => " + this->arg3;
        }   
        else{
            //TODO check loadI
            // loadI c1 => r2
            // SE loadI for mapeado para  c1 == arg1 & r2 == arg3 vai funcionar
            return this->code + " " + this->arg1 + " => " + this->arg3;
        }

    }
    else if(this->code.find("store") != std::string::npos){
    //Intruções de STORE :: code arg1 => arg2,arg3
        //indireto/deslocamento usando arg3
        if ((this->code.find("AI") != std::string::npos) || (this->code.find("A0") != std::string::npos)){
            return this->code + " " + this->arg1 + " => " + this->arg2 + ", " + this->arg3;
        }
        else{
            return this->code + " " + this->arg1 + " => " + this->arg2;
        }
    }
    else if(this->code.find("2") != std::string::npos){
    //Intruções de COPY :: code arg1 => arg2
        return this->code + " " + this->arg1 + " => " + this->arg2;
    }
    else if(this->code.find("jump") != std::string::npos){
    //Instrução JUMP
        return this->code + " -> " + this->arg1;
    }
    else if(this->code.find("cbr") != std::string::npos){
    //Instrução CBR
        return this->code + " " + this->arg1 + " -> " + this->arg2 + ", " + this->arg3;
    }
    else if(this->code.find("cmp") != std::string::npos){
    //Instrução CMP :: code arg1, arg2 => arg3
        return this->code + " " + this->arg1 + ", " + this->arg2 + " -> " + this->arg3;
    }
    else if(this->code.find("nop") != std::string::npos){
    //Instrução NOP
        return this->code;
    }
    else{
    //Instruções ARTIMÉTICAS / SHIFTS / BOOL :: code arg1, arg2 => arg3
        return this->code + " " + this->arg1 + ", " + this->arg2 + " => " + this->arg3;
    }
}
