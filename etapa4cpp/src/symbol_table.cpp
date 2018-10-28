/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include "../include/symbol_table.h"

using namespace std;

/*
 * SymbolTableEntry functions
 */

SymbolTableEntry::SymbolTableEntry(string name)
{
    this->name = name;
    // TODO: add the other fields
}

SymbolTableEntry::~SymbolTableEntry()
{
    // TODO: clean up
}

string SymbolTableEntry::getName()
{
    return this->name;
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
    this->entries.insert(pair<string, SymbolTableEntry*>(entry->getName(),entry));
}

SymbolTableEntry* SymbolTable::LookUp(string name)
{
    this->entries.find(name);
    map<string, SymbolTableEntry*>::const_iterator iter = this->entries.find(name);

    if(iter != this->entries.end()) {
        return iter->second;
    }
    else {
        return NULL;
    }
}
