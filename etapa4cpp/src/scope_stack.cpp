/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include <stack>
#include "../include/symbol_table.h"
#include "../include/scope_stack.h"

using namespace std;

/*
 * ScopeStack functions
 */

ScopeStack::ScopeStack()
{

}

ScopeStack::~ScopeStack()
{
    // TODO: clean up
}

void ScopeStack::push(SymbolTable *table)
{
    this->scopes.push(table);
}

void ScopeStack::pop()
{
    this->scopes.pop();
}

SymbolTableEntry *ScopeStack::LookUp(string name)
{
    stack <SymbolTable*> scopes;
    SymbolTable * top;
    SymbolTableEntry* entry;

    scopes = this->scopes; //copia local

    while(!scopes.empty()){ //enquanto a pilha não for vazia

        top = scopes.top(); //get topo da pilha
        entry = top->LookUp(name); //procura na hash o nome

        if (entry != NULL) { //se encontrou retorna
            return entry;
        }
        else{
            scopes.pop(); //desempilha
        }
    }

    return NULL; // não encontrou
}
