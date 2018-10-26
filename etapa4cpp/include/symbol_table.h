/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include <string>

using namespace std;

class SymbolTableEntry
{
    private:
        string name; // identificador do simbolo
        // TODO: localização (linha e opcional coluna) da sua definição/declaração
        // TODO: natureza (literal, variável, função, etc)
        // TODO: tipo (qual o tipo de dado deste símbolo)
        // TODO: tamanho (derivado do tipo)
        // TODO: argumentos e seus tipos (no caso de funções)
        // TODO: campos e seus tipos (no caso do tipo for de usuário)
        // TODO: demais informações do valor do token pelo yylval (veja E3)
    public:
        SymbolTableEntry(string name); // Constructor
        ~SymbolTableEntry(); // Destructor
}

class SymbolTable
{
    private:
        map<string, SymbolTableEntry*> entries;
    public:
        SymbolTable(); // Constructor
        ~SymbolTable(); // Destructor
        void Insert(SymbolTableEntry *entry);
        SymbolTableEntry* LookUp(string name);
}
