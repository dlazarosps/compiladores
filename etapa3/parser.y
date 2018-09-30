/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */
%{
#include <stdio.h>
#include <stdlib.h>
#include "valor_lexico.h"
#include "ast.h"
int yylex(void);
int yyerror (char const *s);
extern int get_line_number();
extern void *arvore;
void descompila (void *arvore) {}
void libera (void *arvore) {}
%}

%define parse.error verbose

%union {
    TValorLexico valor_lexico;
	//AST *node_AST;
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
%type<AST> programa
%type<AST> elemento
%type<AST> tipoSimples
%type<AST> tipo
%type<AST> decGlobal


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

programa
    : elemento {AST leafs[] = {$1}; $$ = astCreate(AST_PROGRAMA, $1, leafs);};

elemento
    //: decFunc elemento {AST leafs[] = {$1, $2}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
	: decGlobal elemento {AST leafs[] = {$1, $2}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
	//| decTipo elemento {AST leafs[] = {$1, $2}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
	//| decFunc {AST leafs[] = {$1}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);}
    | decGlobal {AST leafs[] = {$1}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);};
    //| decTipo {AST leafs[] = {$1}; $$ = astCreate(AST_ELEMENTO, NULL, leafs);};

tipoSimples
    : TK_PR_INT {AST leafs[MAX_LEAF]; $$ = astCreate(AST_TERMINAL, $1, leafs);}
 	| TK_PR_FLOAT {AST leafs[MAX_LEAF]; $$ = astCreate(AST_TERMINAL, $1, leafs);}
 	| TK_PR_BOOL {AST leafs[MAX_LEAF]; $$ = astCreate(AST_TERMINAL, $1, leafs);}
 	| TK_PR_CHAR {AST leafs[MAX_LEAF]; $$ = astCreate(AST_TERMINAL, $1, leafs);}
 	| TK_PR_STRING {AST leafs[MAX_LEAF]; $$ = astCreate(AST_TERMINAL, $1, leafs);};

tipo
    : tipoSimples {AST leafs[MAX_LEAF]; $$ = astCreate(AST_TERMINAL, $1, leafs);}
	| TK_IDENTIFICADOR {AST leafs[MAX_LEAF]; $$ = astCreate(AST_TERMINAL, $1, leafs);};

/*
 * Declaração de variáveis globais
 */

decGlobal
    : TK_IDENTIFICADOR TK_PR_STATIC tipo ';'
        {AST leafs[] = {$1,$2,$3,$<valor_lexico>4};
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);}
	| TK_IDENTIFICADOR '[' TK_LIT_INT ']' TK_PR_STATIC tipo ';'
        {AST leafs[] = {$1,$<valor_lexico>2,$3,$<valor_lexico>4,$5,$6,$<valor_lexico>7};
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);}
	| TK_IDENTIFICADOR tipo ';'
        {AST leafs[] = {$1,$2,$<valor_lexico>3};
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);}
	| TK_IDENTIFICADOR '[' TK_LIT_INT ']' tipo ';'
        {AST leafs[] = {$1,$<valor_lexico>2,$3,$<valor_lexico>4,$5,$<valor_lexico>6};
         $$ = astCreate(AST_DECGLOBAL, NULL, leafs);};

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] on line %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}
