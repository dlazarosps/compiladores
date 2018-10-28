/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#pragma once

#include <vector>
#include "lexical_value.h"

using namespace std;

class AbstractSyntaxTree
{
    private:
        int type;
        LexicalValue* lexicalValue;
        vector<AbstractSyntaxTree*> leafs;
    public:
        AbstractSyntaxTree(int type, LexicalValue* lexicalValue); // Constructor
        ~AbstractSyntaxTree(); // Destructor
        void AddLeaf(AbstractSyntaxTree* node);
        int GetType();
        int GetLeafsSize();
        AbstractSyntaxTree * GetNodeLeaf(int index);
        LexicalValue* GetLexicalValue();
        void Descompilation();
        void Print(int nivel);
};

/*
 * Constantes Tipos de produções AST
 */
#define AST_PROGRAMA                        0
#define AST_ELEMENTO                        1
#define AST_OPTCONST                        2
#define AST_TIPOSIMPLES                     3
#define AST_TIPO                            4
#define AST_DECGLOBAL                       5
#define AST_DECTIPO                         6
#define AST_LISTATIPO                       7
#define AST_CAMPOTIPO                       8
#define AST_ENCAPS                          9
#define AST_DECFUNC                         10
#define AST_CABECALHOFUN                    11
#define AST_LISTAFUN                        12
#define AST_PARAMSFUNOREMPTY                13
#define AST_PARAMSFUN                       14
#define AST_PARAMS                          15
#define AST_CORPOFUN                        16
#define AST_BLOCO                           17
#define AST_LISTACOMANDOS                   18
#define AST_CMDSTERMINADOSPONTOVIRGULA      19
#define AST_CMDSTERMINADOSDOISPONTOS        20
#define AST_CMDSIMPLESFOR                   21
#define AST_CMDBLOCO                        22
#define AST_CMDDECVAR                       23
#define AST_DECVAR                          24
#define AST_OPTINIT                         25
#define AST_CMDATR                          26
#define AST_CMDFUNCCALL                     27
#define AST_CMDIO                           28
#define AST_CMDIN                           29
#define AST_CMDOUT                          30
#define AST_SHIFT                           31
#define AST_SHIFTOP                         32
#define AST_RBC                             33
#define AST_FLUXO                           34
#define AST_STMT                            35
#define AST_IFST                            36
#define AST_FOREACH                         37
#define AST_FOR                             38
#define AST_LISTAFOR                        39
#define AST_WHILE                           40
#define AST_DOWHILE                         41
#define AST_SWITCH                          42
#define AST_CMDPIPE                         43
#define AST_PIPELIST                        44
#define AST_PIPEOP                          45
#define AST_LISTAEXPROREMPTY                46
#define AST_LISTAEXPR                       47
#define AST_VARIABLE                        48
#define AST_VARIABLEINDEX                   49
#define AST_VARIABLEATTRIBUTE               50
#define AST_EXPRFUNCCALL                    51
#define AST_EXPRPIPE                        52
#define AST_UNOP                            53
#define AST_UNARIO                          54
#define AST_BIOP                            55
#define AST_BINARIO                         56
#define AST_RELOP                           57
#define AST_TERNARIO                        58
#define AST_LITERAL                         59
#define AST_LITERALNUM                      60
#define AST_LITERALCHAR                     61
#define AST_LITERALBOOL                     62
#define AST_PONTOVIRG                       63
#define AST_DOISPONTOS                      64
#define AST_TERMINAL                        65      //valores lexicos e caracteres reservados / especiais
#define AST_CMDCASE                         66
#define AST_EXPR                            67
#define AST_EMPTY                           68
