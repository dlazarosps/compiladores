/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
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

SymbolTableEntry::SymbolTableEntry(string name, string type, int size, int nature)
{
    this->name = name;
    this->type = type;
    this->nature = nature;

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
