/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include <iostream>
#include "../include/LexicalValue.h"
#include "../include/SymbolTable.h"
#include "../include/SymbolTableEntry.h"

SymbolTable::SymbolTable(string name)
{
    this->name = name;
    this->label = "";
    this->size = 0;
}

SymbolTable::~SymbolTable()
{
    // TODO: clean up
}

void SymbolTable::Insert(SymbolTableEntry *entry)
{
    int nature = entry->GetNature();
    if(nature == NATUREZA_GLOBAL || nature == NATUREZA_VAR) {
        entry->SetMemoryOffset(this->size);
        this->size += entry->GetSize();
    }
    this->entries.insert(pair<string, SymbolTableEntry*>(entry->GetName(),entry));
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

void SymbolTable::Update(SymbolTableEntry *entry)
{
    this->entries[entry->GetName()] = entry;
}

int SymbolTable::GetEntriesSize()
{
    return this->entries.size();
}

string SymbolTable::GetName()
{
    return this->name;
}

void SymbolTable::Print()
{
    cout << "\n> SymbolTable " + this->name + ":\n";

    for (std::map<string, SymbolTableEntry*>::iterator it = this->entries.begin(); it != this->entries.end(); ++it)
    {
        it->second->Print();
    }

    cout << "\n";
}

void SymbolTable::SetLabel(string label)
{
    this->label = label;
}

string SymbolTable::GetLabel()
{
    return this->label;
}

int SymbolTable::GetSize()
{
    return this->size;
}

int SymbolTable::SetSize(int value)
{
    this->size = value;
}
