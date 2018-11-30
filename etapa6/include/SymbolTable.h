/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include "SymbolTableEntry.h"

using namespace std;

class SymbolTable
{
    private:
        string name;
        string label;
        int size;
        map<string, SymbolTableEntry*> entries;
    public:
        SymbolTable(string name); // Constructor
        ~SymbolTable(); // Destructor
        void Insert(SymbolTableEntry *entry);
        SymbolTableEntry* LookUp(string name);
        void Update(SymbolTableEntry *entry);
        int GetEntriesSize();
        string GetName();
        void SetLabel(string label);
        string GetLabel();
        int GetSize();
        void SetSize(int value);
        void Print();
};
