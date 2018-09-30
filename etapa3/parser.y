/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror (char const *s);
extern int get_line_number();
%}

%define parse.error verbose

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
%token TOKEN_ERRO

/* 
 * TIPOS (E1)
 * 	1 - resv 	- Palavras Reservado
 *	2 - espc 	- Caracteres Especiais
 *	3 - opsc 	- Operadores Compostos
 *	4 - ids 	- Identificadores
 *	5 - lit 	- Literal
 *	* - ast 	- Abstract Syntax Tree
 */

/*
	TODO
	São 5 tipos conforme a especificação (E1), porem literais tem 6 'sub'tipos (int, bool, float, char, string)
	além disso tem a struct da arvore, verificar o  como vai ficar o UNION e os tipos
*/
%union{
	int 		intValue;
	//TODO bool
	float 		floatValue;
	char 		charValue;
	char* 		stringValue;
	AST_node 	ast; //struct arvore (?)
} 
//Tokens com tipo (lit)
%token<lit> TK_LIT_INT
%token<lit> TK_LIT_FLOAT
%token<lit> TK_LIT_FALSE
%token<lit> TK_LIT_TRUE
%token<lit> TK_LIT_CHAR
%token<lit> TK_LIT_STRING
%token<lit> TK_IDENTIFICADOR //TODO tipo ids ?

//Tipos Gramatica
%type<ast> programa
%type<ast> elemento
%type<ast> optConst
%type<ast> tipoSimples
%type<ast> tipo
%type<ast> decGlobal
%type<ast> decTipo
%type<ast> decFunc
%type<ast> listaTipo
%type<ast> campoTipo
%type<ast> encaps
%type<ast> decFunc
%type<ast> cabecalhoFun
%type<ast> listaFunc
%type<ast> paramsFunOrEmpty
%type<ast> paramsFun
%type<ast> params
%type<ast> corpoFun
%type<ast> bloco
%type<ast> listaComandos
%type<ast> cmdsTerminadosPontoVirgula
%type<ast> cmdsTerminadosDoisPontos
%type<ast> cmdSimplesFor
%type<ast> cmdBloco
%type<ast> cmdDecVar
%type<ast> decVar
%type<ast> optInit
%type<ast> cmdAtr
%type<ast> cmdFuncCall
%type<ast> cmdIO
%type<ast> cmdin
%type<ast> cmdout
%type<ast> shift
%type<ast> shiftOp
%type<ast> rbc
%type<ast> fluxo
%type<ast> stmt
%type<ast> ifst
%type<ast> foreach
%type<ast> for
%type<ast> listaFor
%type<ast> while
%type<ast> dowhile
%type<ast> switch
%type<ast> cmdPipe
%type<ast> pipeList
%type<ast> pipeOp
%type<ast> listaExprOrEmpty
%type<ast> listaExpr
%type<ast> variable
%type<ast> variableIndex
%type<ast> variableAttribute
%type<ast> exprFuncCall
%type<ast> exprPipe
%type<ast> unOp
%type<ast> unario
%type<ast> biOp
%type<ast> binario
%type<ast> relOp
%type<ast> ternario
%type<ast> literal
%type<ast> literalNum
%type<ast> literalChar
%type<ast> literalBool

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

programa: elemento;

elemento: decFunc elemento
		| decGlobal elemento
		| decTipo elemento
		| %empty;

optConst: TK_PR_CONST
		| %empty;

 tipoSimples: TK_PR_INT
 	 | TK_PR_FLOAT
 	 | TK_PR_BOOL
 	 | TK_PR_CHAR
 	 | TK_PR_STRING;

 tipo: tipoSimples
	 | TK_IDENTIFICADOR;

/*
 * Declaração de variáveis globais
 */

decGlobal: TK_IDENTIFICADOR TK_PR_STATIC tipo ';'
		 | TK_IDENTIFICADOR '[' TK_LIT_INT ']' TK_PR_STATIC tipo ';'
		 | TK_IDENTIFICADOR tipo ';'
		 | TK_IDENTIFICADOR'[' TK_LIT_INT ']' tipo ';';

/*
 * Declaração de tipos
 */

decTipo: TK_PR_CLASS TK_IDENTIFICADOR '[' listaTipo ']' ';';

listaTipo: campoTipo
 		 | listaTipo ':' campoTipo;

campoTipo: encaps tipoSimples TK_IDENTIFICADOR;

encaps:  TK_PR_PROTECTED
 	   | TK_PR_PRIVATE
 	   | TK_PR_PUBLIC
 	   | %empty;


/*
 * Declaração de funções
 */
decFunc: cabecalhoFun corpoFun;

cabecalhoFun: TK_PR_STATIC tipoSimples TK_IDENTIFICADOR listaFun
			| tipo TK_IDENTIFICADOR listaFun;
			| TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
			| TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun;

listaFun: '(' paramsFunOrEmpty ')';

paramsFunOrEmpty: paramsFun
				| %empty;

paramsFun: params
	   	 | paramsFun ',' params;

params: optConst tipo TK_IDENTIFICADOR;

corpoFun: bloco;

bloco: '{' listaComandos '}';

listaComandos: listaComandos cmdsTerminadosPontoVirgula ';'
			 | listaComandos cmdsTerminadosDoisPontos ':'
			 | %empty;

cmdsTerminadosPontoVirgula: cmdDecVar
						  | cmdAtr
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
	   				   	  | switch;

cmdsTerminadosDoisPontos: cmdCase;

cmdSimplesFor: cmdDecVar
		| cmdAtr
		| shift
		| rbc
		| fluxo;

/*
 * Comando simples de bloco
 */

cmdBloco: bloco;

/*
 * Comando de declaração de variáveis
 */

cmdDecVar: TK_PR_STATIC TK_PR_CONST decVar
 	 	 | TK_PR_STATIC decVar
 		 | TK_PR_CONST decVar
		 | decVar;

decVar: tipoSimples TK_IDENTIFICADOR optInit
	  | TK_IDENTIFICADOR TK_IDENTIFICADOR;

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

shift: variable shiftOp expr;

shiftOp:  TK_OC_SL
		| TK_OC_SR;

/*
* Comandos Return Break Continue
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

switch: TK_PR_SWITCH '(' expr ')' bloco;

/*
 * Comando case
 */

cmdCase: TK_PR_CASE TK_LIT_INT;

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

biOp: '+' | '-' | '*' | '/' | '%' | '|' | '&' | '^' | '<' | '>' | relOp;
relOp: TK_OC_LE | TK_OC_GE | TK_OC_EQ | TK_OC_NE | TK_OC_AND | TK_OC_OR;

binario: expr biOp expr %prec BINARY_OP;

ternario: expr '?' expr ':' expr  %prec TERNARY_OP;

/*
 * Literais
 */

literal: literalNum
	   | literalChar
	   | literalBool;

literalNum: TK_LIT_INT
		  | TK_LIT_FLOAT;

literalChar: TK_LIT_CHAR
		   | TK_LIT_STRING;

literalBool: TK_LIT_FALSE
	   | TK_LIT_TRUE;

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] on line %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}
