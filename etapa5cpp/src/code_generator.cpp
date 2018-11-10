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
    else if (this->code.find("L") != std::string::npos)
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

/*
 * Control ILOC 
 */
ControlILOC::ControlILOC()
{
    this->registers = 0;
    this->labels = 0;
    this->globalPositionMem = 0;
    this->pilhaPositionMem = 0;
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
    int memPosition, deslocMem, leafSize;
    string arg1, arg2, arg3, reg1, reg2, lab1, lab2;

    switch (node->GetType())
    {
        case AST_PROGRAMA:
            this->ParseAST(node->GetLeaf(0), hash);

            //lista temporaria insert FRONT
            //instruções de inicialização
            instr = new InstructionILOC("", "loadI", "1024", "", "rfp" );
            instrList.push_front(instr);

            instr = new InstructionILOC("", "loadI", "1024", "", "rsp");
            instrList.push_front(instr);

            instr = new InstructionILOC("", "loadI", "0", "", "rbss");
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
            // TODO tranferir para dentro da HASH (semantic_analizer)
            /*
            // TK_IDENTIFICADOR tipo ';'
            entry = hash->LookUp(node->GetLeaf(0)->GetLexicalValue()->ValueToString());
            // get Mem Position
            memPosition = this->control->GetGlobalPositionMem();
            entry->SetMemPosition(memPosition);
            // insert mem position in hash TK_ID
            hash->Top()->Update(entry); //TODO update into STACK ???
            */
            break; 
        case AST_DECFUNC:
            //ETAPA 6

            //Instruções de RA etc
            //this->ParseAST(node->GetLeaf(0), hash);

            //Instruções do corpo da função
            this->ParseAST(node->GetLeaf(1), hash);
            break;
        /* //ETAPA 6
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
        */
        case AST_CORPOFUN:
            this->ParseAST(node->GetLeaf(0), hash); //avalia bloco
            break;
        case AST_BLOCO:
            this->ParseAST(node->GetLeaf(1), hash); //lista de comandos
            break;
        case AST_LISTACOMANDOS:
            //TESTA se tem folhas
            if(node->GetLeafsSize() > 1){
                this->ParseAST(node->GetLeaf(0), hash);
                this->ParseAST(node->GetLeaf(1), hash);
            }
            break;
        case AST_CMDSTERMINADOSPONTOVIRGULA:
            this->ParseAST(node->GetLeaf(0), hash);
            break;
        case AST_CMDBLOCO:
            this->ParseAST(node->GetLeaf(0), hash);
            break;
        case AST_CMDDECVAR:
            leafSize = node->GetLeafsSize();
            this->ParseAST(node->GetLeaf(leafSize-1), hash);
            break;
        case AST_DECVAR: // tipoSimples TK_IDENTIFICADOR TK_OC_LE variable
            entry = hash->LookUp(node->GetLeaf(1)->GetLexicalValue()->ValueToString());
            // TODO setMemPosition para dentro da HASH (semantic_analizer)
            memPosition = entry->GetMemPosition();
            reg1 = (entry->GetNature() == NATUREZA_GLOBAL) ? "rbss" : "rfp";

            //se tem atribuição de valor
            if(node->GetLeafsSize() == 4){
                //TODO subrotina
                // LITERAL
                if(node->GetLeaf(3)->GetType() == AST_LITERAL){
                    //valor a ser inserido
                    arg1 = this->control->GetRegister();
                    string value = node->GetLeaf(3)->GetLeaf(0)->GetLexicalValue()->ValueToString();
                    instr = new InstructionILOC("", "loadI", value, "", arg1);
                    instrList.push_front(instr);
                }
                else{
                    //VARIABLE
                    //pega posição de memoria onde variavel está salva
                    entry = hash->LookUp(node->GetLeaf(3)->GetLeaf(0)->GetLexicalValue()->ValueToString());
                    deslocMem = entry->GetMemPosition();
                    //valor a ser inserido
                    arg1 = this->control->GetRegister();
                    //registrador arg1 recebe valor armazenado na posição mem rfp + deslocamento

                    reg2 = (entry->GetNature() == NATUREZA_GLOBAL) ? "rbss" : "rfp";
                    instr = new InstructionILOC("", "loadAI", reg2, to_string(deslocMem), arg1);
                    instrList.push_front(instr);

                }

                //salva valor arg1
                //rpf + deslocamento (memPosition) recebe valor armazenado arg1
                //TODO diferenciar registrador especial local de global (rfp / rbss)
                instr = new InstructionILOC("", "storeAI", arg1, reg1, to_string(memPosition));
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
            deslocMem = entry->GetMemPosition();
            reg1 = (entry->GetNature() == NATUREZA_GLOBAL) ? "rbss" : "rfp";

            //salva valor arg1 em reg1 + deslocamento
            instr = new InstructionILOC("", "storeAI", arg1, reg1, to_string(deslocMem));
            instrList.push_front(instr);

            //concat lista temporaria na lista de instruções BACK
            this->instructions.insert(this->instructions.end(), instrList.begin(), instrList.end());

            break;
       /* //Etapa 6
        case AST_CMDFUNCCALL:
            cout << "AST_CMDFUNCCALL";
            break;
        case AST_RBC:
            cout << "AST_RBC";
            break;
        */

       //IF COM CURTO CIRCUITO
        case AST_STMT:
            cout << "AST_STMT";
            break;
        case AST_IFST:
            cout << "AST_IFST";
            break;

        //WHILE COM CURTO CIRCUITO
        case AST_WHILE:
            cout << "AST_WHILE";
            break;
        case AST_DOWHILE:
            cout << "AST_DOWHILE";
            break;
        
        /* //etapa 6 callfun
        case AST_LISTAEXPR:
            cout << "AST_LISTAEXPR";
            break;

        case AST_EXPRFUNCCALL:
            cout << "AST_EXPRFUNCCALL";
            break;
        */
        case AST_EXPR:

            //TODO check expr sozinha no código OU sempre vinculada algum comando ?        
            if(node->GetLeafsSize() == 1){
                this->avalExpr(node->GetLeaf(0), hash);
            }
            else{ 
                // ( expr )
                this->avalExpr(node->GetLeaf(1), hash);
            }
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
    int deslocMem, leaf;
    string arg1, arg2, arg3;
    string regResultReturn;
    string value;

    //gera label para inicio da avaliacao
    //string labelBegin = this->control->GetLabel();
    //pula para inicio da avaliacao
    //instr = new InstructionILOC("jumpI", labelBegin, "", "");
    //instrList.push_front(instr);

    leaf = (node->GetLeafsSize() == 1) ? 0 : 1;

    switch (node->GetLeaf(leaf)->GetType())
    {
        case AST_VARIABLE:
            //VARIABLE
            //pega posição de memoria onde variavel está salva
            entry = hash->LookUp(node->GetLeaf(0)->GetLeaf(0)->GetLexicalValue()->ValueToString());
            deslocMem = entry->GetMemPosition();
            arg1 = this->control->GetRegister();
            instr = new InstructionILOC("", "loadAI", "rfp", to_string(deslocMem), arg1);
            instrList.push_front(instr);
            regResultReturn = arg1;
            break;
        case AST_LITERAL:
            //carrega literal no registrador
            arg1 = this->control->GetRegister();
            value = node->GetLeaf(0)->GetLeaf(0)->GetLexicalValue()->ValueToString();
            instr = new InstructionILOC("", "loadI", value, "", arg1);
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
            instr = new InstructionILOC("", value, arg1, arg2, arg3);
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