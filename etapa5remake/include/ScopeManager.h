/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

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
        int AddFunctionScope(SymbolTable *functionTable); // Retorna 0 se inseriu certo, retorna -1 se já existe
        SymbolTableEntry *LookUp(string name); // Searches inside the current scope and then in the global scope
        int HasScope(string name); // Returns 0 if OK, -1 if scope does not exist
        int SetCurrentScope(string name); // Returns 0 if OK, -1 if scope does not exist
        string GetCurrentScope();
        void SetCurrentScopeToGlobal();
        void InsertEntry(SymbolTableEntry *entry);
        void Print();
};
