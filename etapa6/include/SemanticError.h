/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <string>

using namespace std;

class SemanticError {
    private:
        int code;
        int line;
        string text;
    public:
        SemanticError(int code, int line, string text); // Constructor
        ~SemanticError(); // Destructor
        int GetCode();
        int GetLine();
        string GetText();
        string GetFullText();
};
