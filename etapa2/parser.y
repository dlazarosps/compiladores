%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror (char const *s);
extern int get_line_number();
%}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_OC_FORWARD_PIPE
%token TK_OC_BASH_PIPE
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

// precedencia de operadores

//TODO associativide a direita '&' e '*' ponteiro
%left '&' '?' '%' '|' '^'
%left '<' '>' '!' TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE TK_OC_AND TK_OC_OR
%left '+' '-'
%left '*' '/' TK_OC_SL TK_OC_SR
%right '[' ']'
%right '(' ')'

//ambiguidade IF ELSE
%nonassoc TK_PR_THEN
%nonassoc TK_PR_ELSE

//resolve conflito do tipo definido por usuário
%nonassoc TK_IDENTIFICADOR

%left UNARY_OP
%left BINARY_OP
%left TERNARY_OP

%%

programa: elemento;

elemento: decFunc elemento
		| decGlobal elemento
		| decTipo elemento
		| %empty;

optStatic: TK_PR_STATIC
		 | %empty;

optConst: TK_PR_CONST
		| %empty;

 tipo: TK_PR_INT
 	 | TK_PR_FLOAT
 	 | TK_PR_BOOL
 	 | TK_PR_CHAR
 	 | TK_PR_STRING
 	 | TK_IDENTIFICADOR;

/*
 * Declaração de variáveis globais
 */

decGlobal: optStatic varGlobal ';';

varGlobal: TK_IDENTIFICADOR tipo
 		 | varVetor tipo;

varVetor: TK_IDENTIFICADOR '[' TK_LIT_INT ']';

/*
 * Declaração de tipos
 */

decTipo: TK_PR_CLASS TK_IDENTIFICADOR '[' listaTipo ']' ';';

listaTipo: campoTipo
 		 | listaTipo ':' campoTipo;

campoTipo: encaps tipo TK_IDENTIFICADOR;

encaps:  TK_PR_PROTECTED
 	   | TK_PR_PRIVATE
 	   | TK_PR_PUBLIC
 	   | %empty;


/*
 * Declaração de funções
 */
decFunc: cabecalhoFun corpoFun ';';

cabecalhoFun: optStatic tipo TK_IDENTIFICADOR listaFun;

listaFun: '(' paramsFunOrEmpty ')';

paramsFunOrEmpty: paramsFun
				| %empty;

paramsFun: params
	   	 | paramsFun ',' params;

params: optConst tipo TK_IDENTIFICADOR;

corpoFun: cmdBlock;

cmdBlock: '{' listaComandos '}';

listaComandos: cmdSimples ';' listaComandos
			 | %empty;


cmdSimplesFor: cmdDecVar
		| cmdAtr
		| shift
		| rbc
		| fluxo;

cmdSimples: cmdSimplesFor
		| cmdFuncCall
		| cmdIO
		| cmdPipe;

/*
 * Comando de declaração de variáveis
 */

cmdDecVar: TK_PR_STATIC TK_PR_CONST decVar
 	 	 | TK_PR_STATIC decVar
 		 | TK_PR_CONST decVar
		 | decVar;

decVar: tipo TK_IDENTIFICADOR optInit;

optInit: TK_OC_LE expr
 	   | %empty;

/*
 * Comando de atribuição
 */

cmdAtr: variable '=' expr;

/*
 * Comando de chamada de função
 */

cmdFuncCall: TK_IDENTIFICADOR '(' listaExprOrEmpty ')';

/*
 * Comando de I/O
 */

cmdIO: cmdin
	 | cmdout;

cmdin: TK_PR_INPUT expr;

cmdout: TK_PR_OUTPUT listaExpr;

/*
*  Comando Shift
*/

shift: variable shiftOp TK_LIT_INT;

shiftOp:  TK_OC_SL
		| TK_OC_SR;

/*
* Comandos Return Break Continue Case
*/

rbc: TK_PR_RETURN expr
	| TK_PR_BREAK
	| TK_PR_CONTINUE;

/*
 * Fluxo de Controle
 */

 fluxo: ifst
	  | foreach
	  | for
	  | while
	  | dowhile
	  | switch;

bloco: "{" listaComandos "}";

/*
 * Comando if
 */

stmt: bloco
	| ifst;

ifst: TK_PR_IF '(' expr ')' TK_PR_THEN stmt %prec TK_PR_THEN
	| TK_PR_IF '(' expr ')' TK_PR_THEN stmt TK_PR_ELSE stmt;

/*
 * Comando foreach
 */

foreach: TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' listaExpr ')' bloco;

/*
 * Comando for
 */

for: TK_PR_FOR '(' listaFor ':' expr ':' listaFor ')' bloco;

listaFor: cmdSimplesFor
	|  cmdSimplesFor ',' listaFor;

/*
 * Comando while e do while
 */

while: TK_PR_WHILE '(' expr ')' TK_PR_DO bloco;

dowhile: TK_PR_DO bloco TK_PR_WHILE '(' expr ')';

/*
 * Comando switch
 */

switch: TK_PR_SWITCH '(' expr ')' blocoSwitch;

blocoSwitch: '{' listaComandosSwitch '}';

listaComandosSwitch: cmdSimples ';' listaComandosSwitch
			 	   | TK_PR_CASE TK_LIT_INT ':' listaComandosSwitch
				   | %empty;

/*
 * Comando pipe
 */

cmdPipe: cmdFuncCall pipeOp pipeList;

pipeList: cmdFuncCall
		| cmdFuncCall pipeOp pipeList;

pipeOp: TK_OC_FORWARD_PIPE
	  | TK_OC_BASH_PIPE;

/*
 * Expressão
 */

expr: variable
	| literal
	| exprFuncCall
	| exprPipe
	| unario
	| binario
	| ternario
	| '(' expr ')'
	| '.';

/*
 * Lista de expressões (para parâmetros de chamadas de função, etc)
 */

listaExprOrEmpty: listaExpr
				| %empty;

listaExpr: expr
		 | listaExpr ',' expr;

/*
 * Acesso a variáveis
 */

variable: TK_IDENTIFICADOR variableIndex variableAttribute;

variableIndex: '[' expr ']'
			 | %empty;

variableAttribute: '$' variable
			 | %empty;

/*
 * Expressão de chamada de função
 */

exprFuncCall: cmdFuncCall;

/*
 * Expressão pipe
 */

exprPipe: cmdPipe;

/*
* Operadores Expressões
*/

unOp: '+' | '-' | '!' | '&' | '*' | '?' | '#';

unario: unOp expr %prec UNARY_OP;

biOp: '+' | '-' | '*' | '/' | '%' | '|' | '&' | '^' | relOp;
relOp: TK_OC_LE | TK_OC_GE | TK_OC_EQ | TK_OC_NE | TK_OC_AND | TK_OC_OR;

binario: expr biOp expr %prec BINARY_OP;

ternario: expr '?' expr ':' expr  %prec TERNARY_OP;

/*
 * Literais
 */

literal: literalNum
	   | literalChar
	   | litBool;

literalNum: TK_LIT_INT
		  | TK_LIT_FLOAT;

literalChar: TK_LIT_CHAR
		   | TK_LIT_STRING;

litBool: TK_LIT_FALSE
	   | TK_LIT_TRUE;

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] Houve erro na linha %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}
