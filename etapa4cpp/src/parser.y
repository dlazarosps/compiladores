/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
%{
#include <stdio.h>
#include <stdlib.h>
#include "../include/lexical_value.h"
#include "../include/ast.h"
int yylex(void);
int yyerror (char const *s);
extern int get_line_number();
extern void *arvore;

extern void descompila (void *arvore) {
    //astDescomp(arvore);
    //fprintf(stdout, "\n");
}
extern void libera (void *arvore) {
    //astPrint(arvore, 0);
    //astDelete(arvore);
}
%}

%define parse.error verbose

%union {
    LexicalValue *lex;
	AbstractSyntaxTree *astNode;
}

%token <lex> TK_PR_INT
%token <lex> TK_PR_FLOAT
%token <lex> TK_PR_BOOL
%token <lex> TK_PR_CHAR
%token <lex> TK_PR_STRING
%token <lex> TK_PR_IF
%token <lex> TK_PR_THEN
%token <lex> TK_PR_ELSE
%token <lex> TK_PR_WHILE
%token <lex> TK_PR_DO
%token <lex> TK_PR_INPUT
%token <lex> TK_PR_OUTPUT
%token <lex> TK_PR_RETURN
%token <lex> TK_PR_CONST
%token <lex> TK_PR_STATIC
%token <lex> TK_PR_FOREACH
%token <lex> TK_PR_FOR
%token <lex> TK_PR_SWITCH
%token <lex> TK_PR_CASE
%token <lex> TK_PR_BREAK
%token <lex> TK_PR_CONTINUE
%token <lex> TK_PR_CLASS
%token <lex> TK_PR_PRIVATE
%token <lex> TK_PR_PUBLIC
%token <lex> TK_PR_PROTECTED
%token <lex> TK_OC_LE
%token <lex> TK_OC_GE
%token <lex> TK_OC_EQ
%token <lex> TK_OC_NE
%token <lex> TK_OC_AND
%token <lex> TK_OC_OR
%token <lex> TK_OC_SL
%token <lex> TK_OC_SR
%token <lex> TK_OC_FORWARD_PIPE
%token <lex> TK_OC_BASH_PIPE
%token TOKEN_ERRO
%token <lex> TK_LIT_INT
%token <lex> TK_LIT_FLOAT
%token <lex> TK_LIT_FALSE
%token <lex> TK_LIT_TRUE
%token <lex> TK_LIT_CHAR
%token <lex> TK_LIT_STRING
%token <lex> TK_IDENTIFICADOR

//Tipos Gramatica
%type<astNode> programa
%type<astNode> elemento
%type<astNode> tipoSimples
%type<astNode> tipo
%type<astNode> decGlobal
%type<astNode> decTipo
%type<astNode> listaTipo
%type<astNode> campoTipo
%type<astNode> encaps
%type<astNode> decFunc
%type<astNode> cabecalhoFun
%type<astNode> listaFun
%type<astNode> paramsFun
%type<astNode> params
%type<astNode> corpoFun
%type<astNode> bloco
%type<astNode> listaComandos
%type<astNode> cmdsTerminadosPontoVirgula
%type<astNode> cmdsTerminadosDoisPontos
%type<astNode> cmdSimplesFor
%type<astNode> cmdCase
%type<astNode> cmdDecVar
%type<astNode> decVar
%type<astNode> expr
%type<astNode> cmdAtr
%type<astNode> cmdFuncCall
%type<astNode> cmdIO
%type<astNode> cmdin
%type<astNode> cmdout
%type<astNode> listaExpr
%type<astNode> variable
%type<astNode> variableIndex
%type<astNode> variableAttribute
%type<astNode> literal
%type<astNode> exprFuncCall
%type<astNode> cmdPipe
%type<astNode> pipeList
%type<astNode> pipeOp
%type<astNode> shift
%type<astNode> shiftOp
%type<astNode> rbc
%type<astNode> ifst
%type<astNode> stmt
%type<astNode> foreach
%type<astNode> for
%type<astNode> listaFor
%type<astNode> while
%type<astNode> dowhile
%type<astNode> switch
%type<astNode> cmdBloco
%type<astNode> exprPipe
%type<astNode> unOp
%type<astNode> unario
%type<astNode> biOp
%type<astNode> relOp
%type<astNode> binario
%type<astNode> ternario

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
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PROGRAMA, NULL);
        node->AddLeaf($1);
        $$ = node;
        arvore = $$;
    }
    | %empty
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PROGRAMA, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_EMPTY, NULL));
        $$ = node;
        arvore = $$;
    }
    ;

elemento: elemento decGlobal
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ELEMENTO, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        $$ = node;
    }
    | decGlobal
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ELEMENTO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | elemento decTipo
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ELEMENTO, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        $$ = node;
    }
    | decTipo
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ELEMENTO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | elemento decFunc
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ELEMENTO, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        $$ = node;
    }
    | decFunc
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ELEMENTO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

tipoSimples: TK_PR_INT
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TIPOSIMPLES, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
 	| TK_PR_FLOAT
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TIPOSIMPLES, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
 	| TK_PR_BOOL
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TIPOSIMPLES, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
 	| TK_PR_CHAR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TIPOSIMPLES, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
 	| TK_PR_STRING
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TIPOSIMPLES, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

tipo: tipoSimples
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TIPO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TIPO, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

/*
 * Declaração de variáveis globais
 */

decGlobal: TK_IDENTIFICADOR TK_PR_STATIC tipo ';'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECGLOBAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        $$ = node;
    }
	| TK_IDENTIFICADOR '[' TK_LIT_INT ']' TK_PR_STATIC tipo ';'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECGLOBAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $5));
        node->AddLeaf($6);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>7));
        $$ = node;
    }
	| TK_IDENTIFICADOR tipo ';'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECGLOBAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
	| TK_IDENTIFICADOR '[' TK_LIT_INT ']' tipo ';'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECGLOBAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf($5);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>6));
        $$ = node;
    }
    ;

/*
* Declaração de tipos
*/

decTipo: TK_PR_CLASS TK_IDENTIFICADOR '[' listaTipo ']' ';'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECTIPO, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        node->AddLeaf($4);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>5));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>6));
        $$ = node;
    }
    ;

listaTipo: campoTipo
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTATIPO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| listaTipo ':' campoTipo
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTATIPO, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        $$ = node;
    }
    ;

campoTipo: encaps tipoSimples TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CAMPOTIPO, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        $$ = node;
    }
    | tipoSimples TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CAMPOTIPO, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        $$ = node;
    }
    ;

encaps: TK_PR_PROTECTED
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ENCAPS, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
	| TK_PR_PRIVATE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ENCAPS, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
	| TK_PR_PUBLIC
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_ENCAPS, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

/*
 * Declaração de funções
 */

decFunc: cabecalhoFun corpoFun
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECFUNC, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        $$ = node;
    }
    ;

cabecalhoFun: TK_PR_STATIC tipoSimples TK_IDENTIFICADOR listaFun
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CABECALHOFUN, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf($4);
        $$ = node;
    }
	| tipo TK_IDENTIFICADOR listaFun
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CABECALHOFUN, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf($3);
        $$ = node;
    }
	| TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CABECALHOFUN, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf($4);
        $$ = node;
    }
	| TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CABECALHOFUN, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf($3);
        $$ = node;
    }
    ;

listaFun: '(' paramsFun ')'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTAFUN, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
    | '(' ')'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTAFUN, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        $$ = node;
    }
    ;

paramsFun: params
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PARAMSFUN, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| paramsFun ',' params
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PARAMSFUN, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        $$ = node;
    }
    ;

params: TK_PR_CONST tipo TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PARAMS, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        $$ = node;
    }
    | tipo TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PARAMS, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        $$ = node;
    }
    ;

corpoFun: bloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CORPOFUN, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

bloco: '{' listaComandos '}'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BLOCO, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
    ;

listaComandos: listaComandos cmdsTerminadosPontoVirgula ';'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTACOMANDOS, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
	| listaComandos cmdsTerminadosDoisPontos ':'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTACOMANDOS, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
	| %empty
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTACOMANDOS, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_EMPTY, NULL));
        $$ = node;
    }
    ;

cmdsTerminadosPontoVirgula: cmdDecVar
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdAtr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdFuncCall
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdIO
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdPipe
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| shift
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| rbc
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| dowhile
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdBloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| ifst
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| foreach
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| for
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| while
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| switch
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSPONTOVIRGULA, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

cmdsTerminadosDoisPontos: cmdCase
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSTERMINADOSDOISPONTOS, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

cmdSimplesFor: cmdDecVar
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdAtr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| shift
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| rbc
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | ifst
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | foreach
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | for
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | while
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | dowhile
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    | switch
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDSIMPLESFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

/*
 * Comando case
 */

cmdCase: TK_PR_CASE TK_LIT_INT
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDCASE, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        $$ = node;
    }
    ;

/*
 * Comando simples de bloco
 */

cmdBloco: bloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDBLOCO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

/*
 * Comando de declaração de variáveis
 */

cmdDecVar: TK_PR_STATIC TK_PR_CONST decVar
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDDECVAR, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf($3);
        $$ = node;
    }
 	| TK_PR_STATIC decVar
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDDECVAR, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        $$ = node;
    }
 	| TK_PR_CONST decVar
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDDECVAR, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        $$ = node;
    }
	| decVar
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDDECVAR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

decVar: tipoSimples TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECVAR, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        $$ = node;
    }
    | tipoSimples TK_IDENTIFICADOR TK_OC_LE variable
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECVAR, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf($4);
        $$ = node;
    }
    | tipoSimples TK_IDENTIFICADOR TK_OC_LE literal
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECVAR, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf($4);
        $$ = node;
    }
	| TK_IDENTIFICADOR TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DECVAR, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        $$ = node;
    }
    ;

/*
 * Comando de atribuição
 */

cmdAtr: variable '=' expr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDATR, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        $$ = node;
    }
    ;

/*
 * Comando de chamada de função
 */

cmdFuncCall: TK_IDENTIFICADOR '(' listaExpr ')'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDFUNCCALL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        $$ = node;
    }
    | TK_IDENTIFICADOR '(' ')'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDFUNCCALL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
    ;

/*
 * Comando de I/O
 */

cmdIO: cmdin
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDIO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdout
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDIO, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

cmdin: TK_PR_INPUT expr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDIN, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        $$ = node;
    }
    ;

cmdout: TK_PR_OUTPUT listaExpr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDOUT, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        $$ = node;
    }
    ;

/*
 * Comando pipe
 */

cmdPipe: cmdFuncCall pipeOp pipeList
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_CMDPIPE, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        node->AddLeaf($3);
        $$ = node;
    }
    ;

pipeList: cmdFuncCall
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PIPELIST, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| cmdFuncCall pipeOp pipeList
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PIPELIST, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        node->AddLeaf($3);
        $$ = node;
    }
    ;

pipeOp: TK_OC_FORWARD_PIPE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PIPEOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
	| TK_OC_BASH_PIPE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_PIPEOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

/*
*  Comando Shift
*/

shift: variable shiftOp expr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_SHIFT, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        node->AddLeaf($3);
        $$ = node;
    }
    ;

shiftOp: TK_OC_SL
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_SHIFTOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
	| TK_OC_SR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_SHIFTOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

/*
* Comandos Return Break Continue
*/

rbc: TK_PR_RETURN expr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RBC, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        $$ = node;
    }
	| TK_PR_BREAK
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RBC, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
	| TK_PR_CONTINUE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RBC, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

/*
 * Comando if
 */

ifst: TK_PR_IF '(' expr ')' TK_PR_THEN stmt %prec TK_PR_THEN
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_IFST, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $5));
        node->AddLeaf($6);
        $$ = node;
    }
	| TK_PR_IF '(' expr ')' TK_PR_THEN stmt TK_PR_ELSE stmt
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_IFST, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $5));
        node->AddLeaf($6);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $7));
        node->AddLeaf($8);
        $$ = node;
    }
    ;

stmt: bloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_STMT, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| ifst
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_STMT, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

/*
 * Comando foreach
 */

foreach: TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' listaExpr ')' bloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_FOREACH, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf($5);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>6));
        node->AddLeaf($7);
        $$ = node;
    }
    ;

/*
 * Comando for
 */

for: TK_PR_FOR '(' listaFor ':' expr ':' listaFor ')' bloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_FOR, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf($5);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>6));
        node->AddLeaf($7);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>8));
        node->AddLeaf($9);
        $$ = node;
    }
    ;

listaFor: cmdSimplesFor
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTAFOR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| listaFor ',' cmdSimplesFor
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTAFOR, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        $$ = node;
    }
    ;

/*
 * Comando while e do while
 */

while: TK_PR_WHILE '(' expr ')' TK_PR_DO bloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_WHILE, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $5));
        node->AddLeaf($6);
        $$ = node;
    }
    ;

dowhile: TK_PR_DO bloco TK_PR_WHILE '(' expr ')'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_DOWHILE, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $3));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf($5);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>6));
        $$ = node;
    }
    ;

/*
 * Comando switch
 */

switch: TK_PR_SWITCH '(' expr ')' bloco
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_SWITCH, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf($5);
        $$ = node;
    }
    ;

/*
 * Expressão
 */

expr: variable
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| literal
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| exprFuncCall
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| exprPipe
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| unario
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| binario
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| ternario
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| '(' expr ')'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
    | '.'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPR, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    ;

/*
 * Lista de expressões (para parâmetros de chamadas de função, etc)
 */

listaExpr: expr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTAEXPR, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
	| listaExpr ',' expr
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LISTAEXPR, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        $$ = node;
    }
    ;

/*
 * Acesso a variáveis
 */

variable: TK_IDENTIFICADOR variableIndex variableAttribute
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_VARIABLE, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        node->AddLeaf($2);
        node->AddLeaf($3);
        $$ = node;
    }
    ;

variableIndex: '[' expr ']'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_VARIABLEINDEX, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        node->AddLeaf($2);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>3));
        $$ = node;
    }
	| %empty
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_VARIABLEINDEX, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_EMPTY, NULL));
        $$ = node;
    }
    ;

variableAttribute: '$' TK_IDENTIFICADOR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_VARIABLEATTRIBUTE, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $2));
        $$ = node;
    }
	| %empty
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_VARIABLEATTRIBUTE, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_EMPTY, NULL));
        $$ = node;
    }
    ;

/*
 * Literais
 */

literal: TK_LIT_INT
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LITERAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_LIT_FLOAT
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LITERAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_LIT_CHAR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LITERAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_LIT_STRING
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LITERAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_LIT_FALSE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LITERAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_LIT_TRUE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_LITERAL, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

/*
 * Expressão de chamada de função
 */

exprFuncCall: cmdFuncCall
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPRFUNCCALL, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

/*
 * Expressão pipe
 */

exprPipe: cmdPipe
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_EXPRPIPE, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

/*
* Operadores Expressões
*/

unOp: '+'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '-'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '!'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '&'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '*'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '?'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '#'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    ;

unario: unOp expr %prec UNARY_OP
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_UNARIO, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        $$ = node;
    }
    ;

biOp: '+'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '-'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '*'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '/'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '%'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '|'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '&'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '^'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '<'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | '>'
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>1));
        $$ = node;
    }
    | relOp
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BIOP, NULL);
        node->AddLeaf($1);
        $$ = node;
    }
    ;

relOp: TK_OC_LE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RELOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_OC_GE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RELOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_OC_EQ
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RELOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_OC_NE
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RELOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_OC_AND
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RELOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    | TK_OC_OR
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_RELOP, NULL);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $1));
        $$ = node;
    }
    ;

binario: expr biOp expr %prec BINARY_OP
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_BINARIO, NULL);
        node->AddLeaf($1);
        node->AddLeaf($2);
        node->AddLeaf($3);
        $$ = node;
    }
    ;

ternario: expr '?' expr ':' expr  %prec TERNARY_OP
    {
        AbstractSyntaxTree *node = new AbstractSyntaxTree(AST_TERNARIO, NULL);
        node->AddLeaf($1);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>2));
        node->AddLeaf($3);
        node->AddLeaf(new AbstractSyntaxTree(AST_TERMINAL, $<lex>4));
        node->AddLeaf($5);
        $$ = node;
    }
    ;

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] on line %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}
