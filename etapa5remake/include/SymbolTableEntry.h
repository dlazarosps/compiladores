/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include <string>
#include "SymbolTable.h"

using namespace std;

class SymbolTableEntry
{
    private:
        string name; // identificador do simbolo
        int nature; // natureza (literal, variável, função, etc)
        int type; // (qual o tipo de dado deste símbolo)
        int size; //(derivado do tipo)
        int memoryOffset;
    public:
        SymbolTableEntry(string name, int type, int size, int natureza); // Constructor
        ~SymbolTableEntry(); // Destructor
        string GetName();
        int GetSize();
        int GetNature();
        int GetMemoryOffset();
        void SetMemoryOffset(int offset);
        void Print();
};

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

/*
 * Tipo
 */
#define SYMBOL_TYPE_INT 1
#define SYMBOL_TYPE_FLOAT 2
#define SYMBOL_TYPE_STRING 3
#define SYMBOL_TYPE_CHAR 4
#define SYMBOL_TYPE_BOOL 5
#define SYMBOL_TYPE_USER 6
