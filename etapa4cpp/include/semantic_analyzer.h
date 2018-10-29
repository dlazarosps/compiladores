/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <map>
#include <string>
#include <stack>
#include "ast.h"
#include "scope_stack.h"
#include "symbol_table.h"

using namespace std;

class SemanticAnalyzer
{
    private:
      int errorNumber;
      string lineError;

    public:
        SemanticAnalyzer(); // Constructor
        ~SemanticAnalyzer(); // Destructor
        int GetErrorNumber();
        void SetErrorNumber(int Err);
        string GetLineError();
        void SetLineError(int rowNumber, string rowText);
        void SetLineError(AbstractSyntaxTree *node);
        SemanticAnalyzer* CheckSemantic(AbstractSyntaxTree *node);
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

/*
 * Erros
 */
/* Verificação de declarações */
#define ERR_UNDECLARED 10 //identificador não declarado
#define ERR_DECLARED 11   //identificador já declarado

/* Uso correto de identificadores */
#define ERR_VARIABLE 20 //identificador deve ser utilizado como variável
#define ERR_VECTOR 21   //identificador deve ser utilizado como vetor
#define ERR_FUNCTION 22 //identificador deve ser utilizado como função
#define ERR_USER 23     //identificador deve ser utilizado como de usuário

/* Tipos e tamanho de dados */
#define ERR_WRONG_TYPE 30  //tipos incompatíveis
#define ERR_STRING_TO_X 31 //coerção impossível de var do tipo string
#define ERR_CHAR_TO_X 32   //coerção impossível de var do tipo char
#define ERR_USER_TO_X 33   //coerção impossível de var do tipo de usuário

/* Argumentos e parâmetros */
#define ERR_MISSING_ARGS 40    //faltam argumentos
#define ERR_EXCESS_ARGS 41     //sobram argumentos
#define ERR_WRONG_TYPE_ARGS 42 //argumentos incompatíveis

/* Verificação de tipos em comandos */
#define ERR_WRONG_PAR_INPUT 50  //parâmetro não é identificador
#define ERR_WRONG_PAR_OUTPUT 51 //parâmetro não é literal string ou expressão
#define ERR_WRONG_PAR_RETURN 52 //parâmetro não é expressão compatível com tipo do retorno
