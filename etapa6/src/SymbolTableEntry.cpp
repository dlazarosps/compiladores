/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include <iostream>
#include "../include/LexicalValue.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"

SymbolTableEntry::SymbolTableEntry(string name, int type, int size, int nature)
{
    this->name = name;
    this->type = type;
    this->size = size;
    this->nature = nature;
    this->memoryOffset = 0;

    /*switch (type)
    {
        case VALOR_CHAR:
            this->size = UM_BYTE * size;
            break;
        case VALOR_STRING:
            this->size = UM_BYTE * size;
            break;
        case VALOR_INT:
            this->size = QUATRO_BYTE * size;
            break;
        case VALOR_FLOAT:
            this->size = OITO_BYTE * size;
            break;
        case VALOR_BOOL:
            this->size = UM_BYTE * size;

        default:
            this->size = UNDEFINED;
            break;
    }*/

    // TODO: add the other fields
}

SymbolTableEntry::~SymbolTableEntry()
{
    // TODO: clean up
}

string SymbolTableEntry::GetName()
{
    return this->name;
}

int SymbolTableEntry::GetSize()
{
    return this->size;
}

int SymbolTableEntry::GetNature()
{
    return this->nature;
}

int SymbolTableEntry::GetMemoryOffset()
{
    return this->memoryOffset;
}

void SymbolTableEntry::SetMemoryOffset(int offset)
{
    this->memoryOffset = offset;
}

void SymbolTableEntry::Print()
{
    cout << "---> " + this->name + ", type: " + to_string(this->type) + ", size: " + to_string(this->size) + ", nature: " + to_string(this->nature) + "\n";
}
