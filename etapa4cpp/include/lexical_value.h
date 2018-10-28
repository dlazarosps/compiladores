/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>

using namespace std;

union LexicalValueUnion {
    string* stringValue;
    char charValue;
    int intValue;
    float floatValue;
    int boolValue;
};

// TODO: add a template here?
class LexicalValue
{
    private:
        int line;
        int type;
        int valueType;
        LexicalValueUnion value;
    public:
        LexicalValue(int line, int type, int valueType, char* value); // Constructor
        ~LexicalValue(); // Destructor
        string ValueToString();
        int GetLine();
        int GetType();
        int GetValueType();
        LexicalValueUnion GetValue();
};

#define TIPO_PALAVRA_RESERVADA 0
#define TIPO_CARACTER_ESPECIAL 1
#define TIPO_OPERADOR_COMPOSTO 2
#define TIPO_IDENTIFICADOR 3
#define TIPO_LITERAL 4

#define VALOR_STRING 0
#define VALOR_CHAR 1
#define VALOR_INT 2
#define VALOR_FLOAT 3
#define VALOR_BOOL 4
