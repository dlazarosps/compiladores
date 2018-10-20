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

int checkUndeclared()
{
    int i, 
    HASH* hash_node
    
    //percorre toda a tabela hash
    for(i = 0; i < HASH_SIZE; i++){
        for (hash_node = tabela_hash[i]; hash_node; hash_node = node->next){
            //tipo identificador tem q ser trocado para AST no settypes
            //caso contrario não foi declarada
            if (node->type == TIPO_IDENTIFICADOR){ 
                fprintf(stderr, "ERRO semantico: variavel '%s' nao foi declarada.\n", hash_node->text);
                return ERR_UNDECLARED;
            }
        }
    }
    return 0;
}

int setTypes(AST* node)
{
    int leafsize;
    AST* child;

    //pega quantidade de folhas
    leafsize = listSize(node->lefts);

    //para cada tipo de construção gramatical aplica atribuição de tipo e tamanho
    switch (node->type){    
        case AST_TIPO:
            fprintf(stdout, "AST_TIPO");
            //tipo do usuário precisa ter sido declarado ?
            break;
        case AST_DECGLOBAL:
            //pega tipo
            child = listGet(node->leafs, (leafsize - 1)); //decglobal = id ... tipo ';'

            // atribui tamanho e tipo
            // node->valor_lexico->tipo_valor = get_natureza (child)
            // campo natureza ? (tipo !=  tipo_valor != natureza)
            // node->valor_lexico->size = set_size_lex ()
            // troca tipo lex de TIPO_IDENTIFICADOR => AST_DECGLOBAL ?
            break;
        case AST_DECTIPO:
            //TODO check TK_ID dectipo
            break;
        case AST_CAMPOTIPO:
            //TODO check TK_ID cabecalhofun
            break;
        case AST_CABECALHOFUN:
            //TODO check TK_ID cabecalhofun
            //count parms ?
            break;
        case AST_PARAMS:
            //TODO check TK_ID params
            break;            
        case AST_DECVAR:
            //TODO atribuir tipo a decvar
            break;
        case AST_CMDFUNCCALL:
            //TODO check TK_ID callfun
            break;
        case AST_FOREACH:
            //TODO verificar TK_ID foreach
            break;
        case AST_VARIABLE:
            //TODO atribuir tipo da variável
            break;
        case AST_VARIABLEATTRIBUTE:
            //TODO atribuir tipo do atributo
            break;

        case AST_LITERAL:
            // já teve tipo atribuido no getlexico (scanner)
        
        // NOPs não tem tipo / TK_ID
        case AST_LISTATIPO:
        case AST_ENCAPS:
        case AST_DECFUNC:
        case AST_LISTAFUN:
        case AST_PARAMSFUNOREMPTY:
        case AST_PARAMSFUN:
        case AST_CORPOFUN:
        case AST_BLOCO:
        case AST_LISTACOMANDOS:
        case AST_CMDSTERMINADOSPONTOVIRGULA:
        case AST_CMDSTERMINADOSDOISPONTOS:
        case AST_CMDBLOCO:
        case AST_CMDSIMPLESFOR:
        case AST_CMDDECVAR:
        case AST_OPTINIT:
        case AST_CMDATR:
        case AST_CMDIO:
        case AST_CMDIN:
        case AST_CMDOUT:
        case AST_SHIFT:
        case AST_SHIFTOP:
        case AST_RBC:
        case AST_FLUXO:
        case AST_STMT:
        case AST_IFST:
        case AST_FOR:
        case AST_LISTAFOR:
        case AST_WHILE:
        case AST_DOWHILE:
        case AST_SWITCH:
        case AST_CMDPIPE:
        case AST_PIPELIST:
        case AST_PIPEOP:
        case AST_LISTAEXPROREMPTY:
        case AST_LISTAEXPR:
        case AST_UNOP:
        case AST_VARIABLEINDEX:
        case AST_EXPRFUNCCALL:
        case AST_EXPRPIPE:
        case AST_UNARIO:
        case AST_BIOP:
        case AST_BINARIO:
        case AST_RELOP:
        case AST_TERNARIO:
        case AST_CMDCASE:
        case AST_EXPR:
        case AST_EMPTY:
        case AST_PROGRAMA:
        case AST_ELEMENTO:
        case AST_TIPOSIMPLES:
        default:
            fprintf(stderr, "[ERROR] Node Type: %d", node->type);
            break;
    }

    //TODO recursão ?
    // nem todas folhas tem isso
    // mover para o switch ?
    int i;
    for (i = 0; i < leafsize; i++){
        setTypes((listGet(node->leafs, i));
    }

    return 0;
}