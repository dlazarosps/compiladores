/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexical_value.h"

using namespace std;

LexicalValue::LexicalValue(int line, int type, int valueType, char *text)
{
    this->line = line;
    this->type = type;
    if(this->type == TIPO_LITERAL) {
        this->valueType = valueType;
        switch(valueType) {
            case VALOR_CHAR:
                this->value.charValue = text[0];
                break;
            case VALOR_STRING:
                this->value.stringValue = strdup(text);
                break;
            case VALOR_INT:
                this->value.intValue = atoi(text);
                break;
            case VALOR_FLOAT:
                this->value.floatValue = atof(text);
                break;
            case VALOR_BOOL:
                if(strcmp("true", text) == 0) {
                    this->value.boolValue = 1;
                }
                else {
                    this->value.boolValue = 0;
                }
                break;
            default:
                this->valueType = VALOR_STRING;
                this->value.stringValue = strdup(text);
                // TODO: include exception
                printf("Unexpected value type for literal");
                break;
        }
    }
    else {
        this->valueType = VALOR_STRING;
        this->value.stringValue = strdup(text);
    }
}

LexicalValue::~LexicalValue()
{
    // TODO: destrutor dessa classe
}

char* LexicalValue::ValueToString()
{
    char *str;

    switch (this->valueType)
    {
        case VALOR_CHAR:
            str = to_string(this->value.charValue);
            break;
        case VALOR_STRING:
            str = to_string(this->value.stringValue);
            break;
        case VALOR_INT:
            str = to_string(this->value.intValue);
            break;
        case VALOR_FLOAT:
            str = to_string(this->value.floatValue);
            break;
        case VALOR_BOOL:
            if(this->value.boolValue == 0)
                str = "true";
            else
                str = "false";
            break;
        default:
            // TODO: exception
            // fprintf(stderr, "[ERROR] tipo valor: %d", ast->valor_lexico->tipo_valor);
            str = "ERROR";
            break;
    }

    return str;
}

int LexicalValue::GetLine()
{
    return this->line;
}

int LexicalValue::GetType()
{
    return this->type;
}

int LexicalValue::GetValueType()
{
    return this->valueType;
}

LexicalValueUnion LexicalValue::GetValue()
{
    return this->value;
}
