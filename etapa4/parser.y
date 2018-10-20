/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
%{
#include <stdio.h>
#include <stdlib.h>
#include "valor_lexico.h"
#include "ast.h"
#include "list.h"
#include "hash.h"
int yylex(void);
int yyerror (char const *s);
extern int get_line_number();
extern void *arvore;

extern void descompila (void *arvore) {
    astDescomp(arvore);
    fprintf(stdout, "\n");
}
extern void libera (void *arvore) {
    //astPrint(arvore, 0);
    astDelete(arvore);
}
%}

%define parse.error verbose

%union {
    TValorLexico valor_lexico;
	AST *node_AST;
}

%token <valor_lexico> TK_PR_INT
%token <valor_lexico> TK_PR_FLOAT
%token <valor_lexico> TK_PR_BOOL
%token <valor_lexico> TK_PR_CHAR
%token <valor_lexico> TK_PR_STRING
%token <valor_lexico> TK_PR_IF
%token <valor_lexico> TK_PR_THEN
%token <valor_lexico> TK_PR_ELSE
%token <valor_lexico> TK_PR_WHILE
%token <valor_lexico> TK_PR_DO
%token <valor_lexico> TK_PR_INPUT
%token <valor_lexico> TK_PR_OUTPUT
%token <valor_lexico> TK_PR_RETURN
%token <valor_lexico> TK_PR_CONST
%token <valor_lexico> TK_PR_STATIC
%token <valor_lexico> TK_PR_FOREACH
%token <valor_lexico> TK_PR_FOR
%token <valor_lexico> TK_PR_SWITCH
%token <valor_lexico> TK_PR_CASE
%token <valor_lexico> TK_PR_BREAK
%token <valor_lexico> TK_PR_CONTINUE
%token <valor_lexico> TK_PR_CLASS
%token <valor_lexico> TK_PR_PRIVATE
%token <valor_lexico> TK_PR_PUBLIC
%token <valor_lexico> TK_PR_PROTECTED
%token <valor_lexico> TK_OC_LE
%token <valor_lexico> TK_OC_GE
%token <valor_lexico> TK_OC_EQ
%token <valor_lexico> TK_OC_NE
%token <valor_lexico> TK_OC_AND
%token <valor_lexico> TK_OC_OR
%token <valor_lexico> TK_OC_SL
%token <valor_lexico> TK_OC_SR
%token <valor_lexico> TK_OC_FORWARD_PIPE
%token <valor_lexico> TK_OC_BASH_PIPE
%token TOKEN_ERRO
%token <valor_lexico> TK_LIT_INT
%token <valor_lexico> TK_LIT_FLOAT
%token <valor_lexico> TK_LIT_FALSE
%token <valor_lexico> TK_LIT_TRUE
%token <valor_lexico> TK_LIT_CHAR
%token <valor_lexico> TK_LIT_STRING
%token <valor_lexico> TK_IDENTIFICADOR

//Tipos Gramatica
%type<node_AST> programa
%type<node_AST> elemento
%type<node_AST> tipoSimples
%type<node_AST> tipo
%type<node_AST> decGlobal
%type<node_AST> decTipo
%type<node_AST> listaTipo
%type<node_AST> campoTipo
%type<node_AST> encaps
%type<node_AST> decFunc
%type<node_AST> cabecalhoFun
%type<node_AST> listaFun
%type<node_AST> paramsFun
%type<node_AST> params
%type<node_AST> corpoFun
%type<node_AST> bloco
%type<node_AST> listaComandos
%type<node_AST> cmdsTerminadosPontoVirgula
%type<node_AST> cmdsTerminadosDoisPontos
%type<node_AST> cmdSimplesFor
%type<node_AST> cmdCase
%type<node_AST> cmdDecVar
%type<node_AST> decVar
%type<node_AST> expr
%type<node_AST> cmdAtr
%type<node_AST> cmdFuncCall
%type<node_AST> cmdIO
%type<node_AST> cmdin
%type<node_AST> cmdout
%type<node_AST> listaExpr
%type<node_AST> variable
%type<node_AST> variableIndex
%type<node_AST> variableAttribute
%type<node_AST> literal
%type<node_AST> exprFuncCall
%type<node_AST> cmdPipe
%type<node_AST> pipeList
%type<node_AST> pipeOp
%type<node_AST> shift
%type<node_AST> shiftOp
%type<node_AST> rbc
%type<node_AST> ifst
%type<node_AST> stmt
%type<node_AST> foreach
%type<node_AST> for
%type<node_AST> listaFor
%type<node_AST> while
%type<node_AST> dowhile
%type<node_AST> switch
%type<node_AST> cmdBloco
%type<node_AST> exprPipe
%type<node_AST> unOp
%type<node_AST> unario
%type<node_AST> biOp
%type<node_AST> relOp
%type<node_AST> binario
%type<node_AST> ternario

// precedencia de operadores
%left '&' '?' '%' '|' '^'
%left '<' '>' '!' TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE TK_OC_AND TK_OC_OR
%left '+' '-'
%left '*' '/' TK_OC_SL TK_OC_SR
%right '[' ']'
%right '(' ')'
%left UNARY_OP
%left BINARY_OP
%left TERNARY_OP

//ambiguidade IF ELSE
%nonassoc TK_PR_THEN
%nonassoc TK_PR_ELSE

//resolve conflito do tipo definido por usuário
%right TK_IDENTIFICADOR

%%

programa: elemento
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_PROGRAMA, NULL, leafs);
         arvore = $$;}
    | %empty
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_EMPTY, NULL, NULL));
         $$ = astCreate(AST_PROGRAMA, NULL, leafs);
         arvore = $$;}
    ;

elemento: elemento decGlobal
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    | decGlobal
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    | elemento decTipo
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    | decTipo
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    | elemento decFunc
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    | decFunc
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    ;

tipoSimples: TK_PR_INT
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_TIPOSIMPLES, NULL, leafs);}
 	| TK_PR_FLOAT
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_TIPOSIMPLES, NULL, leafs);}
 	| TK_PR_BOOL
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_TIPOSIMPLES, NULL, leafs);}
 	| TK_PR_CHAR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_TIPOSIMPLES, NULL, leafs);}
 	| TK_PR_STRING
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_TIPOSIMPLES, NULL, leafs);}
    ;

tipo: tipoSimples
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_TIPO, NULL, leafs);}
	| TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_TIPO, NULL, leafs);}
    ;

/*
 * Declaração de variáveis globais
 */

decGlobal: TK_IDENTIFICADOR TK_PR_STATIC tipo ';'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);}
	| TK_IDENTIFICADOR '[' TK_LIT_INT ']' TK_PR_STATIC tipo ';'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($5), NULL));
         listPush(leafs, $6);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>7), NULL));
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);}
	| TK_IDENTIFICADOR tipo ';'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);}
	| TK_IDENTIFICADOR '[' TK_LIT_INT ']' tipo ';'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, $5);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>6), NULL));
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);}
    ;

/*
* Declaração de tipos
*/

decTipo: TK_PR_CLASS TK_IDENTIFICADOR '[' listaTipo ']' ';'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         listPush(leafs, $4);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>5), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>6), NULL));
         $$ = astCreate(AST_DECTIPO, NULL, leafs);}
    ;

listaTipo: campoTipo
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_LISTATIPO, NULL, leafs);}
	| listaTipo ':' campoTipo
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_LISTATIPO, NULL, leafs);}
    ;

campoTipo: encaps tipoSimples TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         $$ = astCreate(AST_CAMPOTIPO, NULL, leafs);}
    | tipoSimples TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_CAMPOTIPO, NULL, leafs);}
    ;

encaps: TK_PR_PROTECTED
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_ENCAPS, NULL, leafs);}
	| TK_PR_PRIVATE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_ENCAPS, NULL, leafs);}
	| TK_PR_PUBLIC
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_ENCAPS, NULL, leafs);}
    ;

/*
 * Declaração de funções
 */

decFunc: cabecalhoFun corpoFun
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         $$ = astCreate(AST_ENCAPS, NULL, leafs);}
    ;

cabecalhoFun: TK_PR_STATIC tipoSimples TK_IDENTIFICADOR listaFun
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, $4);
         $$ = astCreate(AST_CABECALHOFUN, NULL, leafs);}
	| tipo TK_IDENTIFICADOR listaFun
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_CABECALHOFUN, NULL, leafs);}
	| TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, $4);
         $$ = astCreate(AST_CABECALHOFUN, NULL, leafs);}
	| TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_CABECALHOFUN, NULL, leafs);}
    ;

listaFun: '(' paramsFun ')'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_LISTAFUN, NULL, leafs);}
    | '(' ')'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         $$ = astCreate(AST_LISTAFUN, NULL, leafs);}
    ;

paramsFun: params
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_PARAMSFUN, NULL, leafs);}
	| paramsFun ',' params
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_PARAMSFUN, NULL, leafs);}
    ;

params: TK_PR_CONST tipo TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         $$ = astCreate(AST_PARAMS, NULL, leafs);}
    | tipo TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_PARAMS, NULL, leafs);}
    ;

corpoFun: bloco
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CORPOFUN, NULL, leafs);}
    ;

bloco: '{' listaComandos '}'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_BLOCO, NULL, leafs);}
    ;

listaComandos: listaComandos cmdsTerminadosPontoVirgula ';'
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_LISTACOMANDOS, NULL, leafs);}
	| listaComandos cmdsTerminadosDoisPontos ':'
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_LISTACOMANDOS, NULL, leafs);}
	| %empty
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_EMPTY, NULL, NULL));
         $$ = astCreate(AST_LISTACOMANDOS, NULL, leafs);}
    ;

cmdsTerminadosPontoVirgula: cmdDecVar
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| cmdAtr
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| cmdFuncCall
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| cmdIO
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| cmdPipe
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| shift
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| rbc
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| dowhile
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| cmdBloco
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| ifst
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| foreach
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| for
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| while
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
	| switch
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSPONTOVIRGULA, NULL, leafs);}
    ;

cmdsTerminadosDoisPontos: cmdCase
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSDOISPONTOS, NULL, leafs);}
    ;

cmdSimplesFor: cmdDecVar
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
	| cmdAtr
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
	| shift
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
	| rbc
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
    | ifst
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
    | foreach
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
    | for
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
    | while
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
    | dowhile
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
    | switch
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSIMPLESFOR, NULL, leafs);}
    ;

/*
 * Comando case
 */

cmdCase: TK_PR_CASE TK_LIT_INT
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_CMDCASE, NULL, leafs);}
    ;

/*
 * Comando simples de bloco
 */

cmdBloco: bloco
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDBLOCO, NULL, leafs);}
    ;

/*
 * Comando de declaração de variáveis
 */

cmdDecVar: TK_PR_STATIC TK_PR_CONST decVar
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_CMDDECVAR, NULL, leafs);}
 	| TK_PR_STATIC decVar
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         $$ = astCreate(AST_CMDDECVAR, NULL, leafs);}
 	| TK_PR_CONST decVar
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         $$ = astCreate(AST_CMDDECVAR, NULL, leafs);}
	| decVar
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDDECVAR, NULL, leafs);}
    ;

decVar: tipoSimples TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_DECVAR, NULL, leafs);}
    | tipoSimples TK_IDENTIFICADOR TK_OC_LE variable
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, $4);
         $$ = astCreate(AST_DECVAR, NULL, leafs);}
    | tipoSimples TK_IDENTIFICADOR TK_OC_LE literal
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, $4);
         $$ = astCreate(AST_DECVAR, NULL, leafs);}
	| TK_IDENTIFICADOR TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_DECVAR, NULL, leafs);}
    ;

/*
 * Comando de atribuição
 */

cmdAtr: variable '=' expr
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_CMDATR, NULL, leafs);}
    ;

/*
 * Comando de chamada de função
 */

cmdFuncCall: TK_IDENTIFICADOR '(' listaExpr ')'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         $$ = astCreate(AST_CMDFUNCCALL, NULL, leafs);}
    | TK_IDENTIFICADOR '(' ')'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_CMDFUNCCALL, NULL, leafs);}
    ;

/*
 * Comando de I/O
 */

cmdIO: cmdin
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDIO, NULL, leafs);}
	| cmdout
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDIO, NULL, leafs);}
    ;

cmdin: TK_PR_INPUT expr
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         $$ = astCreate(AST_CMDIN, NULL, leafs);}
    ;

cmdout: TK_PR_OUTPUT listaExpr
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         $$ = astCreate(AST_CMDOUT, NULL, leafs);}
    ;

/*
 * Comando pipe
 */

cmdPipe: cmdFuncCall pipeOp pipeList
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         listPush(leafs, $3);
         $$ = astCreate(AST_CMDPIPE, NULL, leafs);}
    ;

pipeList: cmdFuncCall
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_PIPELIST, NULL, leafs);}
	| cmdFuncCall pipeOp pipeList
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         listPush(leafs, $3);
         $$ = astCreate(AST_PIPELIST, NULL, leafs);}
    ;

pipeOp: TK_OC_FORWARD_PIPE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_PIPEOP, NULL, leafs);}
	| TK_OC_BASH_PIPE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_PIPEOP, NULL, leafs);}
    ;

/*
*  Comando Shift
*/

shift: variable shiftOp expr
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         listPush(leafs, $3);
         $$ = astCreate(AST_SHIFT, NULL, leafs);}
    ;

shiftOp: TK_OC_SL
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_SHIFTOP, NULL, leafs);}
	| TK_OC_SR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_SHIFTOP, NULL, leafs);}
    ;

/*
* Comandos Return Break Continue
*/

rbc: TK_PR_RETURN expr
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         $$ = astCreate(AST_RBC, NULL, leafs);}
	| TK_PR_BREAK
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RBC, NULL, leafs);}
	| TK_PR_CONTINUE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RBC, NULL, leafs);}
    ;

/*
 * Comando if
 */

ifst: TK_PR_IF '(' expr ')' TK_PR_THEN stmt %prec TK_PR_THEN
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($5), NULL));
         listPush(leafs, $6);
         $$ = astCreate(AST_IFST, NULL, leafs);}
	| TK_PR_IF '(' expr ')' TK_PR_THEN stmt TK_PR_ELSE stmt
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($5), NULL));
         listPush(leafs, $6);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($7), NULL));
         listPush(leafs, $8);
         $$ = astCreate(AST_IFST, NULL, leafs);}
    ;

stmt: bloco
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_STMT, NULL, leafs);}
	| ifst
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_STMT, NULL, leafs);}
    ;

/*
 * Comando foreach
 */

foreach: TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' listaExpr ')' bloco
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, $5);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>6), NULL));
         listPush(leafs, $7);
         $$ = astCreate(AST_FOREACH, NULL, leafs);}
    ;

/*
 * Comando for
 */

for: TK_PR_FOR '(' listaFor ':' expr ':' listaFor ')' bloco
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, $5);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>6), NULL));
         listPush(leafs, $7);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>8), NULL));
         listPush(leafs, $9);
         $$ = astCreate(AST_FOR, NULL, leafs);}
    ;

listaFor: cmdSimplesFor
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_LISTAFOR, NULL, leafs);}
	| listaFor ',' cmdSimplesFor
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_LISTAFOR, NULL, leafs);}
    ;

/*
 * Comando while e do while
 */

while: TK_PR_WHILE '(' expr ')' TK_PR_DO bloco
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($5), NULL));
         listPush(leafs, $6);
         $$ = astCreate(AST_WHILE, NULL, leafs);}
    ;

dowhile: TK_PR_DO bloco TK_PR_WHILE '(' expr ')'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($3), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, $5);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>6), NULL));
         $$ = astCreate(AST_DOWHILE, NULL, leafs);}
    ;

/*
 * Comando switch
 */

switch: TK_PR_SWITCH '(' expr ')' bloco
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, $5);
         $$ = astCreate(AST_DOWHILE, NULL, leafs);}
    ;

/*
 * Expressão
 */

expr: variable
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPR, NULL, leafs);}
	| literal
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPR, NULL, leafs);}
	| exprFuncCall
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPR, NULL, leafs);}
	| exprPipe
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPR, NULL, leafs);}
	| unario
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPR, NULL, leafs);}
	| binario
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPR, NULL, leafs);}
	| ternario
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPR, NULL, leafs);}
	| '(' expr ')'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_EXPR, NULL, leafs);}
    | '.'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_EXPR, NULL, leafs);}
    ;

/*
 * Lista de expressões (para parâmetros de chamadas de função, etc)
 */

listaExpr: expr
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_LISTAEXPR, NULL, leafs);}
	| listaExpr ',' expr
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         $$ = astCreate(AST_LISTAEXPR, NULL, leafs);}
    ;

/*
 * Acesso a variáveis
 */

variable: TK_IDENTIFICADOR variableIndex variableAttribute
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, $2);
         listPush(leafs, $3);
         $$ = astCreate(AST_VARIABLE, NULL, leafs);}
    ;

variableIndex: '[' expr ']'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_VARIABLEINDEX, NULL, leafs);}
	| %empty
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_EMPTY, NULL, NULL));
         $$ = astCreate(AST_VARIABLEINDEX, NULL, leafs);}
    ;

variableAttribute: '$' TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_VARIABLEATTRIBUTE, NULL, leafs);}
	| %empty
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_EMPTY, NULL, NULL));
         $$ = astCreate(AST_VARIABLEATTRIBUTE, NULL, leafs);}
    ;

/*
 * Literais
 */

literal: TK_LIT_INT
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_LITERAL, NULL, leafs);}
    | TK_LIT_FLOAT
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_LITERAL, NULL, leafs);}
    | TK_LIT_CHAR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_LITERAL, NULL, leafs);}
    | TK_LIT_STRING
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_LITERAL, NULL, leafs);}
    | TK_LIT_FALSE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_LITERAL, NULL, leafs);}
    | TK_LIT_TRUE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_LITERAL, NULL, leafs);}
    ;

/*
 * Expressão de chamada de função
 */

exprFuncCall: cmdFuncCall
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPRFUNCCALL, NULL, leafs);}
    ;

/*
 * Expressão pipe
 */

exprPipe: cmdPipe
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_EXPRPIPE, NULL, leafs);}
    ;

/*
* Operadores Expressões
*/

unOp: '+'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_UNOP, NULL, leafs);}
    | '-'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_UNOP, NULL, leafs);}
    | '!'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_UNOP, NULL, leafs);}
    | '&'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_UNOP, NULL, leafs);}
    | '*'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_UNOP, NULL, leafs);}
    | '?'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_UNOP, NULL, leafs);}
    | '#'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_UNOP, NULL, leafs);}
    ;

unario: unOp expr %prec UNARY_OP
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         $$ = astCreate(AST_UNARIO, NULL, leafs);}
    ;

biOp: '+'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '-'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '*'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '/'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '%'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '|'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '&'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '^'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '<'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | '>'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    | relOp
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_BIOP, NULL, leafs);}
    ;

relOp: TK_OC_LE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RELOP, NULL, leafs);}
    | TK_OC_GE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RELOP, NULL, leafs);}
    | TK_OC_EQ
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RELOP, NULL, leafs);}
    | TK_OC_NE
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RELOP, NULL, leafs);}
    | TK_OC_AND
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RELOP, NULL, leafs);}
    | TK_OC_OR
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         $$ = astCreate(AST_RELOP, NULL, leafs);}
    ;

binario: expr biOp expr %prec BINARY_OP
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         listPush(leafs, $3);
         $$ = astCreate(AST_BINARIO, NULL, leafs);}
    ;

ternario: expr '?' expr ':' expr  %prec TERNARY_OP
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>2), NULL));
         listPush(leafs, $3);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>4), NULL));
         listPush(leafs, $5);
         $$ = astCreate(AST_TERNARIO, NULL, leafs);}
    ;

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] on line %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}
