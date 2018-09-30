/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */
%{
#include <stdio.h>
#include <stdlib.h>
#include "valor_lexico.h"
#include "ast.h"
#include "list.h"
int yylex(void);
int yyerror (char const *s);
extern int get_line_number();
extern void *arvore;

extern void descompila (void *arvore) {
    astDescomp(arvore);
}
extern void libera (void *arvore) {
    astPrint(arvore, 0);
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
//%type<node_AST> cmdSimplesFor
%type<node_AST> cmdCase
%type<node_AST> cmdDecVar
%type<node_AST> decVar
%type<node_AST> expr

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

//TODO: Falta fazer programa poder ser vazio
programa
    : elemento
        {arvore = $$;
        LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_PROGRAMA, NULL, leafs);}
    ;

elemento
    //: decFunc elemento {AST leafs[] = {$1, $2}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    //| decFunc {AST leafs[] = {$1}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
	: elemento decGlobal
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

tipoSimples
    : TK_PR_INT
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

tipo
    : tipoSimples
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

decGlobal
    : TK_IDENTIFICADOR TK_PR_STATIC tipo ';'
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

decTipo
    : TK_PR_CLASS TK_IDENTIFICADOR '[' listaTipo ']' ';'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         listPush(leafs, $4);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>5), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>6), NULL));
         $$ = astCreate(AST_DECTIPO, NULL, leafs);}
    ;

listaTipo
    : campoTipo
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

campoTipo
    : encaps tipoSimples TK_IDENTIFICADOR
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

encaps
    : TK_PR_PROTECTED
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

decFunc
    : cabecalhoFun corpoFun
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, $2);
         $$ = astCreate(AST_ENCAPS, NULL, leafs);}
    ;

cabecalhoFun
    : TK_PR_STATIC tipoSimples TK_IDENTIFICADOR listaFun
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

listaFun
    : '(' paramsFun ')'
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

paramsFun
    : params
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

params
    : TK_PR_CONST tipo TK_IDENTIFICADOR
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

corpoFun
    : bloco
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CORPOFUN, NULL, leafs);}
    ;

bloco
    : '{' listaComandos '}'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         listPush(leafs, $2);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>3), NULL));
         $$ = astCreate(AST_BLOCO, NULL, leafs);}
    ;

listaComandos
    : listaComandos cmdsTerminadosPontoVirgula ';'
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
         TValorLexico lex;
         lex.linha = get_line_number();
         lex.tipo = TIPO_LITERAL;
         lex.tipo_valor = VALOR_STRING;
         lex.valor_string = "";
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy(lex), NULL));
         $$ = astCreate(AST_LISTACOMANDOS, NULL, leafs);}
    ;

cmdsTerminadosPontoVirgula
    : cmdDecVar
/*	| cmdAtr
	| cmdFuncCall
	| cmdIO
	| cmdPipe
	| shift
	| rbc
	| dowhile
	| cmdBloco
	| ifst;
	| foreach
	| for
	| while
	| switch*/
    ;

cmdsTerminadosDoisPontos
    : cmdCase
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         $$ = astCreate(AST_CMDSTERMINADOSDOISPONTOS, NULL, leafs);}
    ;

/*
cmdSimplesFor
    : cmdDecVar
	| cmdAtr
	| shift
	| rbc
	| fluxo
    ;
*/

/*
 * Comando case
 */

cmdCase
    : TK_PR_CASE TK_LIT_INT
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($1), NULL));
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_CMDCASE, NULL, leafs);}
    ;

/*
 * Comando de declaração de variáveis
 */

cmdDecVar
    : TK_PR_STATIC TK_PR_CONST decVar
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

decVar
    : tipoSimples TK_IDENTIFICADOR
        {LIST *leafs = listCreate();
         listPush(leafs, $1);
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($2), NULL));
         $$ = astCreate(AST_DECVAR, NULL, leafs);}
    | tipoSimples TK_IDENTIFICADOR TK_OC_LE expr
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
 * Expressão
 */

expr
/*
    : variable
	| literal
	| exprFuncCall
	| exprPipe
	| unario
	| binario
	| ternario
	| '(' expr ')'
    | '.'
    ;
*/
	: '.'
        {LIST *leafs = listCreate();
         listPush(leafs, astCreate(AST_TERMINAL, lexCopy($<valor_lexico>1), NULL));
         $$ = astCreate(AST_EXPR, NULL, leafs);}
    ;

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] on line %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}
