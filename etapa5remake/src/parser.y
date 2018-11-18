/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
%{
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "../include/LexicalValue.h"
#include "../include/SemanticAnalyzer.h"
#include "../include/AbstractSyntaxTree.h"
#include "../include/AstExpression.h"
#include "../include/AstProgram.h"
#include "../include/AstDeclareGlobalVariable.h"
#include "../include/AstDeclareFunction.h"
#include "../include/AstDeclareParameter.h"
#include "../include/AstDeclareVariable.h"
#include "../include/AstAssignVariable.h"
#include "../include/AstFunctionCall.h"
#include "../include/AstAccessVariable.h"
#include "../include/AstLiteral.h"
#include "../include/AstUnaryOperation.h"
#include "../include/AstBinaryOperation.h"
int yylex(void);
int yyerror (char const *s);
extern int get_line_number();
extern void *arvore;

extern void descompila (AbstractSyntaxTree *arvore) {
    //arvore->Decompile();
    //fprintf(stdout, "\n");
}
extern void libera (AbstractSyntaxTree *arvore) {
    //arvore->Print(0);
    delete arvore;
}
%}

%define parse.error verbose

%union {
    LexicalValue *lex;
	AbstractSyntaxTree *astNode;
    vector<AbstractSyntaxTree*> *listOfAst;
    AstExpression *expr;
    vector<AstExpression*> *listOfExpr;
    int integer;

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
%type<listOfAst> listaElementos
%type<astNode> elemento
%type<astNode> tipo
%type<astNode> decGlobal
%type<astNode> decFunc
%type<listOfAst> decFuncParamsList
%type<astNode> decFuncParam
%type<listOfAst> bloco
%type<listOfAst> listaComandos
%type<astNode> comandos
%type<astNode> cmdDecVar
%type<expr> expr
%type<listOfExpr> listaExpr
%type<astNode> cmdAtr
%type<astNode> cmdFuncCall
%type<expr> variable
%type<expr> literal
%type<expr> exprFuncCall
%type<astNode> cmdReturn
%type<astNode> cmdIfElse
%type<astNode> stmt
%type<astNode> cmdWhile
%type<astNode> cmdDoWhile
%type<integer> unOp
%type<expr> unario
%type<integer> biOp
%type<expr> binario

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

programa: listaElementos
    {
        AstProgram *programa = new AstProgram();
        programa->addElements($1);
        AbstractSyntaxTree *node = programa;
        $$ = node;
        arvore = $$;
    }
    ;

listaElementos: listaElementos elemento
    {
        vector<AbstractSyntaxTree*> *elements = $1;
        elements->push_back($2);
        $$ = elements;
    }
    | %empty
    {
        vector<AbstractSyntaxTree*> *elements = new vector<AbstractSyntaxTree*>();
        $$ = elements;
    }
    ;

elemento: decGlobal
    {
        $$ = $1;
    }
    | decFunc
    {
        $$ = $1;
    }
    ;

/* desconsiderando o tipo já que variáveis só podem ser INT */
tipo: TK_PR_INT
    {
        $$ = NULL;
    }
    ;

/*
 * Declaração de variáveis globais
 */

decGlobal: TK_IDENTIFICADOR tipo ';'
    {
        AstDeclareGlobalVariable *decGlobal = new AstDeclareGlobalVariable($1);
        AbstractSyntaxTree *node = decGlobal;
        $$ = node;
    }
    ;

/*
 * Declaração de funções
 */

decFunc: tipo TK_IDENTIFICADOR '(' decFuncParamsList ')' bloco
    {
        AstDeclareFunction *decFunc = new AstDeclareFunction($2, $4, $6);
        AbstractSyntaxTree *node = decFunc;
        $$ = node;
    }
    | tipo TK_IDENTIFICADOR '(' ')' bloco
    {
        vector<AbstractSyntaxTree*> *emptyList = new vector<AbstractSyntaxTree*>();
        AstDeclareFunction *decFunc = new AstDeclareFunction($2, emptyList, $5);
        AbstractSyntaxTree *node = decFunc;
        $$ = node;
    }
    ;

decFuncParamsList: decFuncParam
    {
        vector<AbstractSyntaxTree*> *params = new vector<AbstractSyntaxTree*>();
        params->push_back($1);
        $$ = params;
    }
	| decFuncParamsList ',' decFuncParam
    {
        vector<AbstractSyntaxTree*> *params = $1;
        params->push_back($3);
        $$ = params;
    }
    ;

decFuncParam: tipo TK_IDENTIFICADOR
    {
        AstDeclareParameter *decFuncParam = new AstDeclareParameter($2);
        AbstractSyntaxTree *node = decFuncParam;
        $$ = node;
    }
    ;

bloco: '{' listaComandos '}'
    {
        $$ = $2;
    }
    ;

listaComandos: listaComandos comandos ';'
    {
        vector<AbstractSyntaxTree*> *commands = $1;
        commands->push_back($2);
        $$ = commands;
    }
	| %empty
    {
        vector<AbstractSyntaxTree*> *commands = new vector<AbstractSyntaxTree*>;
        $$ = commands;
    }
    ;

comandos: cmdDecVar
    {
        $$ = $1;
    }
	| cmdAtr
    {
        $$ = $1;
    }
	| cmdFuncCall
    {
        $$ = $1;
    }
	| cmdReturn
    {
        $$ = $1;
    }
	| cmdDoWhile
    {
        $$ = $1;
    }
	| cmdIfElse
    {
        $$ = $1;
    }
	| cmdWhile
    {
        $$ = $1;
    }
    ;

/*
 * Comando de declaração de variáveis
 */

cmdDecVar: tipo TK_IDENTIFICADOR
    {
        AstDeclareVariable *decVar = new AstDeclareVariable($2, NULL);
        AbstractSyntaxTree *node = decVar;
        $$ = node;
    }
    | tipo TK_IDENTIFICADOR TK_OC_LE variable
    {
        AstDeclareVariable *decVar = new AstDeclareVariable($2, $4);
        AbstractSyntaxTree *node = decVar;
        $$ = node;
    }
    | tipo TK_IDENTIFICADOR TK_OC_LE literal
    {
        AstDeclareVariable *decVar = new AstDeclareVariable($2, $4);
        AbstractSyntaxTree *node = decVar;
        $$ = node;
    }
    ;

/*
 * Comando de atribuição
 */

cmdAtr: TK_IDENTIFICADOR '=' expr
    {
        AstAssignVariable *assign = new AstAssignVariable($1, $3);
        AbstractSyntaxTree *node = assign;
        $$ = node;
    }
    ;

/*
 * Comando de chamada de função
 */

cmdFuncCall: TK_IDENTIFICADOR '(' listaExpr ')'
    {
        AstFunctionCall *funcCall = new AstFunctionCall($1, $3);
        AbstractSyntaxTree *node = funcCall;
        $$ = node;
    }
    | TK_IDENTIFICADOR '(' ')'
    {
        vector<AstExpression*> *params = new vector<AstExpression*>;
        AstFunctionCall *funcCall = new AstFunctionCall($1, params);
        AbstractSyntaxTree *node = funcCall;
        $$ = node;
    }
    ;

/*
* Comandos Return Break Continue
*/

cmdReturn: TK_PR_RETURN expr
    {
        $$ = NULL; //TODO
    }
    ;

/*
 * Comando if
 */

cmdIfElse: TK_PR_IF '(' expr ')' TK_PR_THEN stmt %prec TK_PR_THEN
    {
        $$ = NULL; //TODO
    }
	| TK_PR_IF '(' expr ')' TK_PR_THEN stmt TK_PR_ELSE stmt
    {
        $$ = NULL; //TODO
    }
    ;

stmt: bloco
    {
        $$ = NULL; //TODO
    }
	| cmdIfElse
    {
        $$ = NULL; //TODO
    }
    ;

/*
 * Comando while e do while
 */

cmdWhile: TK_PR_WHILE '(' expr ')' TK_PR_DO bloco
    {
        $$ = NULL; //TODO
    }
    ;

cmdDoWhile: TK_PR_DO bloco TK_PR_WHILE '(' expr ')'
    {
        $$ = NULL; //TODO
    }
    ;

/*
 * Expressão
 */

expr: variable
    {
        $$ = $1;
    }
	| literal
    {
        $$ = $1;
    }
	| exprFuncCall
    {
        $$ = $1;
    }
	| unario
    {
        $$ = $1;
    }
	| binario
    {
        $$ = $1;
    }
	| '(' expr ')'
    {
        $$ = $2;
    }
    ;

/*
 * Lista de expressões (para parâmetros de chamadas de função, etc)
 */

listaExpr: expr
    {
        vector<AstExpression*> *expressions = new vector<AstExpression*>();
        expressions->push_back($1);
        $$ = expressions;
    }
	| listaExpr ',' expr
    {
        vector<AstExpression*> *expressions = $1;
        expressions->push_back($3);
        $$ = expressions;
    }
    ;

/*
 * Acesso a variáveis
 */

variable: TK_IDENTIFICADOR
    {
        AstAccessVariable *access = new AstAccessVariable($1);
        AstExpression *node = access;
        $$ = node;
    }
    ;

/*
 * Literais
 */

literal: TK_LIT_INT
    {
        AstLiteral *lit = new AstLiteral($1);
        AstExpression *node = lit;
        $$ = node;
    }
    | TK_LIT_FALSE
    {
        AstLiteral *lit = new AstLiteral($1);
        AstExpression *node = lit;
        $$ = node;
    }
    | TK_LIT_TRUE
    {
        AstLiteral *lit = new AstLiteral($1);
        AstExpression *node = lit;
        $$ = node;
    }
    ;

/*
 * Expressão de chamada de função
 */

exprFuncCall: cmdFuncCall
    {
        $$ = NULL; //TODO
    }
    ;

/*
* Operadores Expressões
*/

unOp: '+'
    {
        $$ = UNARY_OPERATION_TYPE_POSITIVE;
    }
    | '-'
    {
        $$ = UNARY_OPERATION_TYPE_NEGATIVE;
    }
    | '!'
    {
        $$ = UNARY_OPERATION_TYPE_LOGICAL_NEGATION;
    }
    ;

unario: unOp expr %prec UNARY_OP
    {
        AstUnaryOperation *un = new AstUnaryOperation($1,$2);
        AstExpression *node = un;
        $$ = node;
    }
    ;

biOp: '+'
    {
        $$ = BINARY_OPERATION_TYPE_SUM;
    }
    | '-'
    {
        $$ = BINARY_OPERATION_TYPE_SUBTRACT;
    }
    | '*'
    {
        $$ = BINARY_OPERATION_TYPE_DIVIDE;
    }
    | '/'
    {
        $$ = BINARY_OPERATION_TYPE_MULTIPLY;
    }
    | '^'
    {
        $$ = BINARY_OPERATION_TYPE_POWER;
    }
    | '<'
    {
        $$ = BINARY_OPERATION_TYPE_LESS_THAN;
    }
    | '>'
    {
        $$ = BINARY_OPERATION_TYPE_GREATER_THAN;
    }
    | TK_OC_LE
    {
        $$ = BINARY_OPERATION_TYPE_LE;
    }
    | TK_OC_GE
    {
        $$ = BINARY_OPERATION_TYPE_GE;
    }
    | TK_OC_EQ
    {
        $$ = BINARY_OPERATION_TYPE_EQ;
    }
    | TK_OC_NE
    {
        $$ = BINARY_OPERATION_TYPE_NE;
    }
    | TK_OC_AND
    {
        $$ = BINARY_OPERATION_TYPE_AND;
    }
    | TK_OC_OR
    {
        $$ = BINARY_OPERATION_TYPE_OR;
    }
    ;

binario: expr biOp expr %prec BINARY_OP
    {
        AstBinaryOperation *bi = new AstBinaryOperation($1,$2,$3);
        AstExpression *node = bi;
        $$ = node;
    }
    ;

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] on line %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}
