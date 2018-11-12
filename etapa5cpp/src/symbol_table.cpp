/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include <iostream>
#include "../include/lexical_value.h"
#include "../include/symbol_table.h"

using namespace std;

/*
 * SymbolTableEntryField functions
 */
SymbolTableEntryField::SymbolTableEntryField(string name, string type)
{
    this->name = name;
    this->type = type;
}

SymbolTableEntryField::~SymbolTableEntryField()
{

}

string SymbolTableEntryField::GetName()
{
    return this->name;
}

string SymbolTableEntryField::GetType()
{
    return this->type;
}

/*
 * SymbolTableEntry functions
 */

SymbolTableEntry::SymbolTableEntry(string name, int type, int size, int nature, int memPosition)
{
    this->name = name;
    this->type = type;
    this->nature = nature;
    this->memPosition = memPosition;

    this->associatedSymbolTable = NULL;

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

void SymbolTableEntry::AddField(string name, string type)
{
    this->fields.push_back(new SymbolTableEntryField(name, type));
}

int SymbolTableEntry::FieldsSize()
{
    return this->fields.size();
}

SymbolTableEntryField* SymbolTableEntry::GetField(string name)
{
    SymbolTableEntryField *field;
    for (unsigned int i = 0; i < this->fields.size(); i++) {
        field = this->fields.at(i);
        if(name.compare(field->GetName())==0)
            return field;
    }
    return NULL;
}

SymbolTableEntryField* SymbolTableEntry::GetFieldAt(int index)
{
    if(index < this->FieldsSize()) {
        return this->fields.at(index);
    }
    else {
        return NULL;
    }
}

int SymbolTableEntry::GetMemPosition()
{
    return this->memPosition;
}

void SymbolTableEntry::SetMemPosition(int position)
{
    this->memPosition = position;
}

SymbolTable* SymbolTableEntry::getAssociatedSymbolTable()
{
    return this->associatedSymbolTable;
}

void SymbolTableEntry::setAssociatedSymbolTable(SymbolTable* table)
{
    this->associatedSymbolTable = table;
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

int SymbolTable::GetSize()
{
    return this->entries.size();
}

void SymbolTable::Print()
{
    for (std::map<string, SymbolTableEntry*>::iterator it = this->entries.begin(); it != this->entries.end(); ++it)
    {
        it->second->Print();
    }
}

void SymbolTableEntry::Print()
{
    cout << "Nome: " << this->name << "\n";
    cout << "Natureza: ";
    switch(this->nature) {
        case NATUREZA_FUN:
            cout << "Função";
            break;
        case NATUREZA_VAR:
            cout << "Variável";
            break;
        case NATUREZA_GLOBAL:
            cout << "Variável global";
            break;
        default:
            cout << "Erro";
            break;
    }
    cout << "\n";
    cout << "Deslocamento: " << this->memPosition << "\n";
    if(this->associatedSymbolTable != NULL) {
        cout << "--- Início do escopo associado ---\n\n";
        this->associatedSymbolTable->Print();
        cout << "--- Final do escopo associado ---\n";
    }
    cout << "\n";
}
