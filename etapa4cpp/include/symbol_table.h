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
        int natureza; // natureza (literal, variável, função, etc)
        int tipo; // (qual o tipo de dado deste símbolo)
        int tamanho; //(derivado do tipo)
        // TODO: argumentos e seus tipos (no caso de funções)
        // TODO: campos e seus tipos (no caso do tipo for de usuário)
        // TODO: demais informações do valor do token pelo yylval (veja E3)
    public:
        SymbolTableEntry(string name, int type, int size, int natureza); // Constructor
        ~SymbolTableEntry(); // Destructor
        string getName();
};

class SymbolTable
{
    private:
        map<string, SymbolTableEntry*> entries;
    public:
        SymbolTable(); // Constructor
        ~SymbolTable(); // Destructor
        void Insert(SymbolTableEntry *entry);
        SymbolTableEntry* LookUp(string name);
};

/*
 * Tipo
 */
#define SYMBOL_TYPE_INT 1
#define SYMBOL_TYPE_FLOAT 2
#define SYMBOL_TYPE_STRING 3
#define SYMBOL_TYPE_CHAR 4
#define SYMBOL_TYPE_BOOL 5
#define SYMBOL_TYPE_USER 6

/*
 * Natureza
 */
#define NATUREZA_LITERAL_INT 1
#define NATUREZA_LITERAL_FLOAT 2
#define NATUREZA_LITERAL_CHAR 3
#define NATUREZA_LITERAL_STRING 4
#define NATUREZA_LITERAL_BOOL 5
#define NATUREZA_IDENTIFICADOR 6
#define NATUREZA_GLOBAL 7
#define NATUREZA_FUN 8
#define NATUREZA_TIPO 9
#define NATUREZA_VAR 10
#define NATUREZA_VEC 11

/*
 * Tamanho
 */
#define UM_BYTE 1
#define QUATRO_BYTE 4
#define OITO_BYTE 8
#define UNDEFINED -1
