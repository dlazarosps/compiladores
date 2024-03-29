/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include <stack>
#include <iostream>
#include "../include/SymbolTable.h"
#include "../include/ScopeManager.h"

using namespace std;

/*
 * ScopeStack functions
 */

ScopeManager::ScopeManager()
{
    this->globalScope = new SymbolTable("_GLOBAL_");
    this->SetCurrentScopeToGlobal();
}

ScopeManager::~ScopeManager()
{
    // TODO: clean up
}

bool ScopeManager::HasScope(string name)
{
    map<string, SymbolTable*>::const_iterator iter;

    if(this->globalScope->GetName().compare(name) == 0) {
        return 0;
    }

    iter = this->functionScopes.find(name);
    if (iter != this->functionScopes.end()) {
        return 0;
    }
    else {
        return -1;
    }
}

bool ScopeManager::SetCurrentScopeByName(string name)
{
    map<string, SymbolTable*>::const_iterator iter;

    if(this->globalScope->GetName().compare(name) == 0) {
        this->currentScope = this->globalScope;
        return 0;
    }

    iter = this->functionScopes.find(name);
    if (iter != this->functionScopes.end()) {
        this->currentScope = iter->second;
        return 0;
    }
    else {
        return -1;
    }
}

void ScopeManager::SetCurrentScopeToGlobal()
{
    this->currentScope = this->globalScope;
}

string ScopeManager::GetCurrentScopeName()
{
    return this->currentScope->GetName();
}

SymbolTable* ScopeManager::GetCurrentScope()
{
    return this->currentScope;
}

SymbolTable* ScopeManager::GetScopeByName(string name)
{
    map<string, SymbolTable*>::const_iterator iter;

    if(this->globalScope->GetName().compare(name) == 0) {
        return this->globalScope;
    }

    iter = this->functionScopes.find(name);
    if (iter != this->functionScopes.end()) {
        return iter->second;
    }
    else {
        return NULL;
    }
}

bool ScopeManager::AddFunctionScope(SymbolTable *functionTable)
{
    string functionName = functionTable->GetName();
    if(this->HasScope(functionName) == 0) {
        return -1;
    }

    functionTable->SetSize(28);
    this->functionScopes.insert(pair<string, SymbolTable*>(functionName, functionTable));

    return 0;
}

SymbolTableEntry* ScopeManager::LookUp(string name)
{
    SymbolTableEntry* entry;

    entry = this->currentScope->LookUp(name);
    if(entry != NULL) {
        return entry;
    }

    entry = this->globalScope->LookUp(name);
    if(entry != NULL) {
        return entry;
    }

    return NULL;
}

void ScopeManager::InsertEntry(SymbolTableEntry *entry)
{
    this->currentScope->Insert(entry);
}

void ScopeManager::Print()
{
    cout << "ScopeManager output:\n";

    this->globalScope->Print();

    for (std::map<string, SymbolTable*>::iterator it = this->functionScopes.begin(); it != this->functionScopes.end(); ++it)
    {
        it->second->Print();
    }
}
