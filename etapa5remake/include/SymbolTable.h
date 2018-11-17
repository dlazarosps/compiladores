/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include "SymbolTableEntry.h"

using namespace std;

class SymbolTable
{
    private:
        string name;
        map<string, SymbolTableEntry*> entries;
    public:
        SymbolTable(string name); // Constructor
        ~SymbolTable(); // Destructor
        void Insert(SymbolTableEntry *entry);
        SymbolTableEntry* LookUp(string name);
        void Update(SymbolTableEntry *entry);
        int GetSize();
        string GetName();
        void Print();
};
