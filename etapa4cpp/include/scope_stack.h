/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include <string>
#include <stack>
#include "symbol_table.h"

using namespace std;

class ScopeStack
{
    private:
      stack <SymbolTable*> scopes;

    public:
        ScopeStack(); // Constructor
        ~ScopeStack(); // Destructor
        void push(SymbolTable *table);
        void pop();
        SymbolTableEntry *LookUp(string name);
};
