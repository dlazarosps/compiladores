/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include <string>
//#include <tuple>
#include <vector>
#include <stack>
#include <list>
#include "ast.h"
#include "semantic_analyzer.h"
#include "semantic_error.h"
#include "scope_stack.h"
#include "symbol_table.h"

using namespace std;

class InstructionILOC
{
    private:
    string label;
    string code;
    string arg1;
    string arg2;
    string arg3;
    // tuple<int, string> arg1;
    // tuple<int, string> arg2;
    // tuple<int, string> arg3;

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


class ControlILOC
{
    private:
    int registers;
    int labels;
    int globalPositionMem;
    int pilhaPositionMem;

    public:
    ControlILOC();
    ~ControlILOC();
    int LastRegisterNumber();
    int LastLabelNumber();
    int LastGlobalPositionMem();
    int LastPilhaPositionMem();
    int GetGlobalPositionMem();
    int GetPilhaPositionMem();
    string GetRegister();
    string GetLabel();
};

class CodeGenerator
{
    private:
    ControlILOC *control;
    list <InstructionILOC*> instructions;

    public:
    CodeGenerator();
    ~CodeGenerator();

    //LIST
    /*
    InstructionILOC Front();
    InstructionILOC Back();
    void PushFront(InstructionILOC intr);
    void PushBack(InstructionILOC intr);
    void PopFront();
    void PopBack();
    */

    void ParseAST(AbstractSyntaxTree *node, ScopeStack *hash, string label = "");
    string avalExpr(AbstractSyntaxTree *node, ScopeStack *hash, string label = "");
    string GetOperator(string opSymbol);
    string PrintOutput();
};

/*
 * Tipo de argumento (?)
 */
#define ARG_REG 0
#define ARG_CONST 1
#define ARG_LABEL 2