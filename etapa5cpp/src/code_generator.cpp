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

/*
 * Control ILOC 
 */
ControlILOC::ControlILOC()
{
    this->registers = 0;
    this->labels = 0;
    this->globalPositionMem = 0;
    this->pilhaPositionMem = 1024;
}

ControlILOC::~ControlILOC()
{
    //TODO DESTROY
    //this->registers = 0;
    //this->labels = 0;
}

string ControlILOC::GetRegister()
{
    string output = "r" + this->registers;
    this->registers++;
    return output;
}

string ControlILOC::GetLabel()
{
    string output = "L" + this->labels;
    this->labels++;
    return output;
}

int ControlILOC::LastRegisterNumber()
{
    return this->registers;
}

int ControlILOC::LastLabelNumber()
{
    return this->labels;
}

int ControlILOC::LastGlobalPositionMem()
{
    return this->globalPositionMem;
}

int ControlILOC::LastPilhaPositionMem()
{
    return this->pilhaPositionMem;
}

int ControlILOC::GetGlobalPositionMem()
{
    this->globalPositionMem += 4; //INT SIZE
    return this->globalPositionMem;
}

int ControlILOC::GetPilhaPositionMem()
{
    this->pilhaPositionMem += 4; //INT SIZE
    return this->pilhaPositionMem;
}

/*
 * Code Generator 
 */
CodeGenerator::CodeGenerator()
{
    this->control = new ControlILOC();
}

CodeGenerator::~CodeGenerator()
{
    //DESTROY
}
//LIST
/*
InstructionILOC CodeGenerator::Front()
{
    return this->instructions.front();
}

InstructionILOC CodeGenerator::Back()
{
    return this->instructions.back();
}

void CodeGenerator::PushFront(InstructionILOC instr)
{
    this->instructions.push_front(instr);
}

void CodeGenerator::PushBack(InstructionILOC instr)
{
    this->instructions.push_back(instr);
}

void CodeGenerator::PopFront()
{
    this->instructions.pop_front();
}

void CodeGenerator::PopBack()
{
    this->instructions.pop_back();
}
*/

string CodeGenerator::PrintOutput()
{
    string output = "";
    list <InstructionILOC*> instrList = this->instructions; //copia da lista
    instrList.reverse(); // inverte lista

    // concatena elementos da lista no output
    for(auto instr : instrList){

        output += instr->GetILOC() + "\n";
    }

    return output;
}

void CodeGenerator::ParseAST(AbstractSyntaxTree *node, ScopeStack *hash){

    InstructionILOC *instr;
    list <InstructionILOC*> instrList;
    SymbolTableEntry* entry;
    int memPosition;
    string arg1, arg2, arg3;

    switch (node->GetType())
    {
        case AST_PROGRAMA:
            this->ParseAST(node->GetLeaf(0), hash);

            //lista temporaria insert FRONT
            //instruções de inicialização
            instr = new InstructionILOC("loadI", "1024", "", "rfp" );
            instrList.push_front(instr);

            instr = new InstructionILOC("loadI", "1024", "", "rsp");
            instrList.push_front(instr);

            instr = new InstructionILOC("loadI", "0", "", "rbss");
            instrList.push_front(instr);

            //concat lista temporaria na lista de instruções BACK
            this->instructions.insert(this->instructions.end(), instrList.begin(), instrList.end());        
            break;
        case AST_ELEMENTO:
            this->ParseAST(node->GetLeaf(0), hash);
            if(node->GetLeafsSize() > 1)
                this->ParseAST(node->GetLeaf(1), hash);
            break;
        case AST_DECGLOBAL:
            // TK_IDENTIFICADOR tipo ';'
            entry = hash->LookUp(node->GetLeaf(0)->GetLexicalValue()->ValueToString());
            // get Mem Position
            memPosition = this->control->GetGlobalPositionMem();
            entry->SetMemPosition(memPosition);
            // insert mem position in hash TK_ID
            hash->Top()->Update(entry); //TODO update into STACK ???
            break;
        /*
        case AST_DECFUNC:
            cout << "AST_DECFUNC";
            break;
        case AST_CABECALHOFUN:
            cout << "AST_CABECALHOFUN";
            break;
        case AST_LISTAFUN:
            cout << "AST_LISTAFUN";
            break;
        case AST_PARAMSFUNOREMPTY:
            cout << "AST_PARAMSFUNOREMPTY";
            break;
        case AST_PARAMSFUN:
            cout << "AST_PARAMSFUN";
            break;
        case AST_PARAMS:
            cout << "AST_PARAMS";
            break;
        case AST_CORPOFUN:
            cout << "AST_CORPOFUN";
            break;
        case AST_BLOCO:
            cout << "AST_BLOCO";
            break;
        case AST_LISTACOMANDOS:
            cout << "AST_LISTACOMANDOS";
            break;
        case AST_CMDSTERMINADOSPONTOVIRGULA:
            cout << "AST_CMDSTERMINADOSPONTOVIRGULA";
            break;
        case AST_CMDSTERMINADOSDOISPONTOS:
            cout << "AST_CMDSTERMINADOSDOISPONTOS";
            break;
        case AST_CMDSIMPLESFOR:
            cout << "AST_CMDSIMPLESFOR";
            break;
        case AST_CMDBLOCO:
            cout << "AST_CMDBLOCO";
            break;
        */
        case AST_CMDDECVAR:
            int leafSize = node->GetLeafsSize();
            this->ParseAST(node->GetLeaf(leafSize-1), hash);
            break;
        case AST_DECVAR:
            // tipoSimples TK_IDENTIFICADOR TK_OC_LE variable
            entry = hash->LookUp(node->GetLeaf(1)->GetLexicalValue()->ValueToString());
            
            // get Mem Position
            memPosition = this->control->GetPilhaPositionMem();
            entry->SetMemPosition(memPosition);
            
            // insert mem position in hash TK_ID
            hash->Top()->Update(entry); //TODO update into STACK ???

            //se tem atribuição de valor
            if(node->GetLeafsSize() == 4){
                //TODO subrotina
                // LITERAL
                if(node->GetLeaf(3)->GetType == AST_LITERAL){
                    //valor a ser inserido
                    arg1 = this->control->GetRegister();
                    string value = node->GetLeaf(3)->GetLeaf(0)->GetLexicalValue()->ValueToString();
                    instr = new InstructionILOC("loadI", value, "", arg1);
                    instrList.push_front(instr);
                }
                else{
                    //VARIABLE
                    //pega posição de memoria onde variavel está salva
                    entry = hash->LookUp(node->GetLeaf(3)->GetLeaf(0)->GetLexicalValue()->ValueToString());
                    int varMemPosition = entry->GetMemPosition();
                    //valor a ser inserido
                    arg1 = this->control->GetRegister();
                    instr = new InstructionILOC("loadI", to_string(varMemPosition), "", arg1);
                    instrList.push_front(instr);
                }

                //posição memoria
                arg2 = this->control->GetRegister();
                instr = new InstructionILOC("loadI", to_string(memPosition), "", arg2);
                instrList.push_front(instr);

                //salva valor arg1 em arg2
                instr = new InstructionILOC("store", arg1, arg2, "");
                instrList.push_front(instr);

                //concat lista temporaria na lista de instruções BACK
                this->instructions.insert(this->instructions.end(), instrList.begin(), instrList.end());
            }
            break;
        case AST_CMDATR:
            
            // TODO avalia expr de atribuição     
            arg1 = this->avalExpr(node->GetLeaf(2), hash);
            //arg1 = result of expr ???
            // retorna um registrador 
                        
            //VARIABLE
            //pega posição de memoria onde variavel está salva
            entry = hash->LookUp(node->GetLeaf(0)->GetLeaf(0)->GetLexicalValue()->ValueToString());
            int varMemPosition = entry->GetMemPosition();

            arg2 = this->control->GetRegister();
            instr = new InstructionILOC("loadI", to_string(varMemPosition), "", arg2);
            instrList.push_front(instr);

            //salva valor arg1 em arg2
            instr = new InstructionILOC("store", arg1, arg2, "");
            instrList.push_front(instr);

            //concat lista temporaria na lista de instruções BACK
            this->instructions.insert(this->instructions.end(), instrList.begin(), instrList.end());

            break;
        case AST_CMDFUNCCALL:
            cout << "AST_CMDFUNCCALL";
            break;
        case AST_CMDIO:
            cout << "AST_CMDIO";
            break;
        case AST_CMDIN:
            cout << "AST_CMDIN";
            break;
        case AST_CMDOUT:
            cout << "AST_CMDOUT";
            break;
        case AST_SHIFT:
            cout << "AST_SHIFT";
            break;
        case AST_SHIFTOP:
            cout << "AST_SHIFTOP";
            break;
        case AST_RBC:
            cout << "AST_RBC";
            break;
        case AST_FLUXO:
            cout << "AST_FLUXO";
            break;
        case AST_STMT:
            cout << "AST_STMT";
            break;
        case AST_IFST:
            cout << "AST_IFST";
            break;
        case AST_FOREACH:
            cout << "AST_FOREACH";
            break;
        case AST_FOR:
            cout << "AST_FOR";
            break;
        case AST_LISTAFOR:
            cout << "AST_LISTAFOR";
            break;
        case AST_WHILE:
            cout << "AST_WHILE";
            break;
        case AST_DOWHILE:
            cout << "AST_DOWHILE";
            break;
        case AST_SWITCH:
            cout << "AST_SWITCH";
            break;
        case AST_CMDPIPE:
            cout << "AST_CMDPIPE";
            break;
        case AST_PIPELIST:
            cout << "AST_PIPELIST";
            break;
        case AST_PIPEOP:
            cout << "AST_PIPEOP";
            break;
        case AST_LISTAEXPROREMPTY:
            cout << "AST_LISTAEXPROREMPTY";
            break;
        case AST_LISTAEXPR:
            cout << "AST_LISTAEXPR";
            break;
        case AST_VARIABLE:
            cout << "AST_VARIABLE";
            break;
        case AST_VARIABLEINDEX:
            cout << "AST_VARIABLEINDEX";
            break;
        case AST_VARIABLEATTRIBUTE:
            cout << "AST_VARIABLEATTRIBUTE";
            break;
        case AST_EXPRFUNCCALL:
            cout << "AST_EXPRFUNCCALL";
            break;
        case AST_EXPRPIPE:
            cout << "AST_EXPRPIPE";
            break;
        case AST_UNOP:
            cout << "AST_UNOP";
            break;
        case AST_UNARIO:
            cout << "AST_UNARIO";
            break;
        case AST_BIOP:
            cout << "AST_BIOP";
            break;
        case AST_BINARIO:
            cout << "AST_BINARIO";
            break;
        case AST_RELOP:
            cout << "AST_RELOP";
            break;
        case AST_TERNARIO:
            cout << "AST_TERNARIO";
            break;
        case AST_LITERAL:
            cout << "AST_LITERAL";
            break;
        case AST_LITERALNUM:
            cout << "AST_LITERALNUM";
            break;
        case AST_LITERALCHAR:
            cout << "AST_LITERALCHAR";
            break;
        case AST_LITERALBOOL:
            cout << "AST_LITERALBOOL";
            break;
        case AST_TERMINAL:
            cout << "AST_TERMINAL";
            break;
        case AST_CMDCASE:
            cout << "AST_CMDCASE";
            break;
        case AST_EXPR:
            cout << "AST_EXPR";
            break;
        case AST_EMPTY:
            cout << "AST_EMPTY";
            break;
        default:
            cerr << "[ERROR] Node Type: " << node->GetType() << "\n";
            break;
    }
}

string CodeGenerator::avalExpr(AbstractSyntaxTree *node, ScopeStack *hash)
{
    InstructionILOC *instr;
    list<InstructionILOC *> instrList;
    SymbolTableEntry *entry;
    int memPosition, varMemPosition;
    string arg1, arg2, arg3;
    string regResultReturn;
    string value;

    //gera label para inicio da avaliacao
    //string labelBegin = this->control->GetLabel();
    //pula para inicio da avaliacao
    //instr = new InstructionILOC("jumpI", labelBegin, "", "");
    //instrList.push_front(instr);

    
    switch (node->GetLeaf(0)->GetType())
    {
        case AST_VARIABLE:
            //VARIABLE
            //pega posição de memoria onde variavel está salva
            entry = hash->LookUp(node->GetLeaf(0)->GetLeaf(0)->GetLexicalValue()->ValueToString());
            varMemPosition = entry->GetMemPosition();
            arg1 = this->control->GetRegister();
            instr = new InstructionILOC("loadI", to_string(varMemPosition), "", arg1);
            instrList.push_front(instr);
            regResultReturn = arg1;
            break;
        case AST_LITERAL:
            //carrega literal no registrador
            arg1 = this->control->GetRegister();
            value = node->GetLeaf(0)->GetLeaf(0)->GetLexicalValue()->ValueToString();
            instr = new InstructionILOC("loadI", value, "", arg1);
            instrList.push_front(instr);
            regResultReturn = arg1;
            break;
        case AST_BINARIO:
            //avalia expr L
            arg1 = this->avalExpr(node->GetLeaf(0), hash);
            //avalia expr R
            arg2 = this->avalExpr(node->GetLeaf(2), hash);

            arg3 = this->control->GetRegister();
            
            //get op
            if (node->GetLeaf(1)->GetLeaf(0)->GetLeafsSize() == 0){
                //artimetica
                value = this->GetOperator(node->GetLeaf(1)->GetLeaf(0)->GetLexicalValue()->ValueToString());
            }
            else{ 
                //relacional
                value = this->GetOperator(node->GetLeaf(1)->GetLeaf(0)->GetLeaf(0)->GetLexicalValue()->ValueToString());
            }
            //gera instrução arg1 op arg2 = arg3
            instr = new InstructionILOC(value, arg1, arg2, arg3);
            instrList.push_front(instr);
            regResultReturn = arg3;

        default:
            break;
    }

    //concat lista temporaria na lista de instruções BACK
    this->instructions.insert(this->instructions.end(), instrList.begin(), instrList.end());

    return regResultReturn;
}

string CodeGenerator::GetOperator(string opSymbol)
{
    if(opSymbol.compare("+")){
        return "add";
    }
    else if (opSymbol.compare("/")){
        return "div";
    }
    else if(opSymbol.compare("*")){
        return "mult";
    }
    else if (opSymbol.compare("-"))
    {
        return "sub";
    }
    else if (opSymbol.compare(">"))
    {
        return "cmp_GT";
    }
    else if (opSymbol.compare("<"))
    {
        return "cmp_LT";
    }
    else if (opSymbol.compare("<=")){
        return "cmp_LE";
    }
    else if(opSymbol.compare(">=")){
        return "cmp_GE";
    }
    else if (opSymbol.compare("=="))
    {
        return "cmp_EQ";
    }
    else if (opSymbol.compare("!="))
    {
        return "cmp_NE";
    }
    else if (opSymbol.compare("&&"))
    {
        return "and";
    }
    else if (opSymbol.compare("||"))
    {
        return "or";
    }
    else if (opSymbol.compare("<<"))
    {
        return "lshift";
    }
    else if (opSymbol.compare(">>"))
    {
        return "rshift";
    }
    else{
        return "nop";
    }
}