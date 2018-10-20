/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "hash.h"
#include "ast.h"
#include "list.h"

int checkAll(AST* root)
{
    int ret = 0;

    //TODO retorna no primeiro erro ?
    ret = setTypes(root);
    ret = checkUndeclared(); //hashfind
    ret = checkUse(root);

    return ret;
}

int setTypes(AST* node)
{
    int leafsize;
    AST* child;
    switch (node->type){

        case AST_PROGRAMA:
            fprintf(stdout, "AST_PROGRAMA");
            break;
        case AST_ELEMENTO:
            fprintf(stdout, "AST_ELEMENTO");
            break;
        case AST_OPTCONST:
            fprintf(stdout, "AST_OPTCONST");
            break;
        case AST_TIPOSIMPLES:
            fprintf(stdout, "AST_TIPOSIMPLES");
            break;
        case AST_TIPO:
            fprintf(stdout, "AST_TIPO");
            break;
        case AST_DECGLOBAL:
            
            //pega quantidade de folhas
            leafsize = listSize(node->lefts);
            //pega tipo
            child = listGet(node->leafs, (leafsize - 1)); //decglobal = id ... tipo ';'

            //para cada tamanho especifico atribui tamanho e tipo
            // node->valor_lexico->tipo_valor = get_natureza (child)
            // campo natureza ? (tipo !=  tipo_valor != natureza)
            // node->valor_lexico->size = set_size_lex ()

            break;
        case AST_DECTIPO:
            fprintf(stdout, "AST_DECTIPO");
            break;
        case AST_LISTATIPO:
            fprintf(stdout, "AST_LISTATIPO");
            break;
        case AST_CAMPOTIPO:
            fprintf(stdout, "AST_CAMPOTIPO");
            break;
        case AST_ENCAPS:
            fprintf(stdout, "AST_ENCAPS");
            break;
        case AST_DECFUNC:
            fprintf(stdout, "AST_DECFUNC");
            break;
        case AST_CABECALHOFUN:
            fprintf(stdout, "AST_CABECALHOFUN");
            break;
        case AST_LISTAFUN:
            fprintf(stdout, "AST_LISTAFUN");
            break;
        case AST_PARAMSFUNOREMPTY:
            fprintf(stdout, "AST_PARAMSFUNOREMPTY");
            break;
        case AST_PARAMSFUN:
            fprintf(stdout, "AST_PARAMSFUN");
            break;
        case AST_PARAMS:
            fprintf(stdout, "AST_PARAMS");
            break;
        case AST_CORPOFUN:
            fprintf(stdout, "AST_CORPOFUN");
            break;
        case AST_BLOCO:
            fprintf(stdout, "AST_BLOCO");
            break;
        case AST_LISTACOMANDOS:
            fprintf(stdout, "AST_LISTACOMANDOS");
            break;
        case AST_CMDSTERMINADOSPONTOVIRGULA:
            fprintf(stdout, "AST_CMDSTERMINADOSPONTOVIRGULA");
            break;
        case AST_CMDSTERMINADOSDOISPONTOS:
            fprintf(stdout, "AST_CMDSTERMINADOSDOISPONTOS");
            break;
        case AST_CMDSIMPLESFOR:
            fprintf(stdout, "AST_CMDSIMPLESFOR");
            break;
        case AST_CMDBLOCO:
            fprintf(stdout, "AST_CMDBLOCO");
            break;
        case AST_CMDDECVAR:
            fprintf(stdout, "AST_CMDDECVAR");
            break;
        case AST_DECVAR:
            fprintf(stdout, "AST_DECVAR");
            break;
        case AST_OPTINIT:
            fprintf(stdout, "AST_OPTINIT");
            break;
        case AST_CMDATR:
            fprintf(stdout, "AST_CMDATR");
            break;
        case AST_CMDFUNCCALL:
            fprintf(stdout, "AST_CMDFUNCCALL");
            break;
        case AST_CMDIO:
            fprintf(stdout, "AST_CMDIO");
            break;
        case AST_CMDIN:
            fprintf(stdout, "AST_CMDIN");
            break;
        case AST_CMDOUT:
            fprintf(stdout, "AST_CMDOUT");
            break;
        case AST_SHIFT:
            fprintf(stdout, "AST_SHIFT");
            break;
        case AST_SHIFTOP:
            fprintf(stdout, "AST_SHIFTOP");
            break;
        case AST_RBC:
            fprintf(stdout, "AST_RBC");
            break;
        case AST_FLUXO:
            fprintf(stdout, "AST_FLUXO");
            break;
        case AST_STMT:
            fprintf(stdout, "AST_STMT");
            break;
        case AST_IFST:
            fprintf(stdout, "AST_IFST");
            break;
        case AST_FOREACH:
            fprintf(stdout, "AST_FOREACH");
            break;
        case AST_FOR:
            fprintf(stdout, "AST_FOR");
            break;
        case AST_LISTAFOR:
            fprintf(stdout, "AST_LISTAFOR");
            break;
        case AST_WHILE:
            fprintf(stdout, "AST_WHILE");
            break;
        case AST_DOWHILE:
            fprintf(stdout, "AST_DOWHILE");
            break;
        case AST_SWITCH:
            fprintf(stdout, "AST_SWITCH");
            break;
        case AST_CMDPIPE:
            fprintf(stdout, "AST_CMDPIPE");
            break;
        case AST_PIPELIST:
            fprintf(stdout, "AST_PIPELIST");
            break;
        case AST_PIPEOP:
            fprintf(stdout, "AST_PIPEOP");
            break;
        case AST_LISTAEXPROREMPTY:
            fprintf(stdout, "AST_LISTAEXPROREMPTY");
            break;
        case AST_LISTAEXPR:
            fprintf(stdout, "AST_LISTAEXPR");
            break;
        case AST_VARIABLE:
            fprintf(stdout, "AST_VARIABLE");
            break;
        case AST_VARIABLEINDEX:
            fprintf(stdout, "AST_VARIABLEINDEX");
            break;
        case AST_VARIABLEATTRIBUTE:
            fprintf(stdout, "AST_VARIABLEATTRIBUTE");
            break;
        case AST_EXPRFUNCCALL:
            fprintf(stdout, "AST_EXPRFUNCCALL");
            break;
        case AST_EXPRPIPE:
            fprintf(stdout, "AST_EXPRPIPE");
            break;
        case AST_UNOP:
            fprintf(stdout, "AST_UNOP");
            break;
        case AST_UNARIO:
            fprintf(stdout, "AST_UNARIO");
            break;
        case AST_BIOP:
            fprintf(stdout, "AST_BIOP");
            break;
        case AST_BINARIO:
            fprintf(stdout, "AST_BINARIO");
            break;
        case AST_RELOP:
            fprintf(stdout, "AST_RELOP");
            break;
        case AST_TERNARIO:
            fprintf(stdout, "AST_TERNARIO");
            break;
        case AST_LITERAL:
            fprintf(stdout, "AST_LITERAL");
            break;
        case AST_LITERALNUM:
            fprintf(stdout, "AST_LITERALNUM");
            break;
        case AST_LITERALCHAR:
            fprintf(stdout, "AST_LITERALCHAR");
            break;
        case AST_LITERALBOOL:
            fprintf(stdout, "AST_LITERALBOOL");
            break;
        case AST_TERMINAL:
            fprintf(stdout, "AST_TERMINAL");
            break;
        case AST_CMDCASE:
            fprintf(stdout, "AST_CMDCASE");
            break;
        case AST_EXPR:
            fprintf(stdout, "AST_EXPR");
            break;
        case AST_EMPTY:
            fprintf(stdout, "AST_EMPTY");
            break;
        default:
            fprintf(stderr, "[ERROR] Node Type: %d", node->type);
            break;
    }

    //TODO recursão ?
    // nem todas folhas tem isso
    // mover para o switch
    for (i = 0; i < leafs; i++){
        setTypes((listGet(node->leafs, i));
    }

    return 0;
}