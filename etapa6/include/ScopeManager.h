/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include <string>
#include "SymbolTable.h"
#include "SymbolTableEntry.h"

using namespace std;

class ScopeManager
{
    private:
        map<string, SymbolTable*> functionScopes;
        SymbolTable* globalScope;
        SymbolTable* currentScope; // Can be global or a function scope

    public:
        ScopeManager(); // Constructor
        ~ScopeManager(); // Destructor
        bool AddFunctionScope(SymbolTable *functionTable);
        SymbolTableEntry *LookUp(string name); // Searches inside the current scope and then in the global scope
        bool HasScope(string name);
        bool SetCurrentScopeByName(string name);
        string GetCurrentScopeName();
        SymbolTable* GetCurrentScope();
        SymbolTable* GetScopeByName(string name);
        void SetCurrentScopeToGlobal();
        void InsertEntry(SymbolTableEntry *entry);
        void Print();
};
