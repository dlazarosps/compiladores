/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include "symbol_table.h"

using namespace std;

/*
 * SymbolTableEntry functions
 */

SymbolTableEntry::SymbolTableEntry(string name, int type, int size, int natureza)
{
    this->name = name;
    this->tipo = type;
    this->natureza = natureza;

    switch (type)
    {
        case VALOR_CHAR:
            this->tamanho = UM_BYTE * size;
            break;
        case VALOR_STRING:
            this->tamanho = UM_BYTE * size;
            break;
        case VALOR_INT:
            this->tamanho = QUATRO_BYTE * size;
            break;
        case VALOR_FLOAT:
            this->tamanho = OITO_BYTE * size;
            break;
        case VALOR_BOOL:
            this->tamanho = UM_BYTE * size;
    
        default:
            this->tamanho = UNDEFINED;
            break;
    }

    // TODO: add the other fields
}

SymbolTableEntry::~SymbolTableEntry()
{
    // TODO: clean up
}

/*
 * SymbolTable functions
 */

SymbolTable::SymbolTable()
{

}

SymbolTable::~SymbolTable()
{
    // TODO: clean up
}

void SymbolTable::Insert(SymbolTableEntry *entry)
{
    this->entries.insert(pair<string, SymbolTableEntry*>(entry->name,entry));
}

SymbolTableEntry* SymbolTable::LookUp(string name)
{
    this.entries.find(name);
    map<string, SymbolTableEntry*>::const_iterator iter = this->entries.find(name);

    if(iter != this->entries.end()) {
        return iter->second;
    }
    else {
        return NULL;
    }
}
