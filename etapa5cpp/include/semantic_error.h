/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>
#include <vector>

using namespace std;

class SemanticError {
    private:
        int code;
        int line;
    public:
        SemanticError(int code, int line); // Constructor
        ~SemanticError(); // Destructor
        int GetCode();
        int GetLine();
        void Print();
};

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
