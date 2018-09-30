/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_LEAF 15

#include <stdio.h>
#include <stdlib.h>

/* 
 * TOKENS 
 */
#define TK_PR_INT          256
#define TK_PR_FLOAT        257
#define TK_PR_BOOL         258
#define TK_PR_CHAR         259
#define TK_PR_STRING       260
#define TK_PR_IF           261
#define TK_PR_THEN         262
#define TK_PR_ELSE         263
#define TK_PR_WHILE        264
#define TK_PR_DO           265
#define TK_PR_INPUT        266
#define TK_PR_OUTPUT       267
#define TK_PR_RETURN       268
#define TK_PR_CONST        269
#define TK_PR_STATIC       270
#define TK_PR_FOREACH      271
#define TK_PR_FOR          272
#define TK_PR_SWITCH       273
#define TK_PR_CASE         274
#define TK_PR_BREAK        275
#define TK_PR_CONTINUE     276
#define TK_PR_CLASS        277
#define TK_PR_PRIVATE      278
#define TK_PR_PUBLIC       279
#define TK_PR_PROTECTED    280
#define TK_OC_LE           281
#define TK_OC_GE           282
#define TK_OC_EQ           283
#define TK_OC_NE           284
#define TK_OC_AND          285
#define TK_OC_OR           286
#define TK_OC_SL           287
#define TK_OC_SR           288
#define TK_OC_FORWARD_PIPE 289
#define TK_OC_BASH_PIPE    290
#define TK_LIT_INT         291
#define TK_LIT_FLOAT       292
#define TK_LIT_FALSE       293
#define TK_LIT_TRUE        294
#define TK_LIT_CHAR        295
#define TK_LIT_STRING      296
#define TK_IDENTIFICADOR   297
#define TOKEN_ERRO         298

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

typedef struct valor_lexico
{
    int linha;
    int tipo;
    void *valor;
} VALOR_LEXICO;

/*
 * Struct AST 
 */
typedef struct ast_node
{
    int type;
	VALOR_LEXICO valor_lexico;
	struct ast_node *leafs[MAX_LEAF];
}AST;

AST *astCreate(int type, VALOR_LEXICO lex, AST leafs[]);
void astDelete(AST parent, AST child);
void astPrint(AST *node, int nivel);
void astDescomp(AST *node);

#endif