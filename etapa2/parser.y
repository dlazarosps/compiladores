%{
int yylex(void);
void yyerror (char const *s);
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
%left '<' '>' '!' TK_OC_LE TK_OC_LGE TK_OC_EQ TK_OC_NE TK_OC_AND TK_OC_OR TK_OC_
%left '+' '-'
%left '*' '/' TK_OC_SL TK_OC_SR
%right '['']'
%right '('')'

//TODO ainda não consegui resolver isso
%nonassoc TK_IDENTIFICADOR

%nonassoc ':'
%nonassoc ','

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
 		 | campoTipo ':' listaTipo;

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

listaFun: '(' paramsFun ')';

paramsFun: params
	   	 | params ',' paramsFun;

params: optConst tipo TK_IDENTIFICADOR;

corpoFun: cmdBlock;

cmdBlock: '{' listaComandos '}' ';';

listaComandos: cmdSimples ';' listaComandos
			 | %empty;

cmdSimples: decVar
		  | cmdAtr
		  | cmdIO
		  //| callFun
		  //| shift
		  //| rbcc
		  //| fluxo
		  //| pipes;
;
/*
 * Comando de declaração de variáveis
 */

decVar: optStatic optConst tipo TK_IDENTIFICADOR decVarAtr;

decVarAtr: "<=" expr
		  | %empty;

/*
 * Comando de atribuição
 */

cmdAtr: variable '=' expr;

/*
 * Comando de I/O
 */

cmdIO: cmdin
	 | cmdout;

cmdin: TK_PR_INPUT expr;

cmdout: TK_PR_OUTPUT listaOut;

listaOut: expr
		| expr ',' listaOut;

/*
 * Expressão
 */

expr: variable
	| literal
	//| callFun
	//| unario
	//| binario
	//| ternario
	//| wpipes
	| '(' expr ')';

variable: TK_IDENTIFICADOR variableIndex variableAttribute;

variableIndex: '[' expr ']'
			 | %empty;

variableAttribute: '$' variable
			 | %empty;
/*
unop: '+' | '-' | '!' | '&' | '*' | '?' | '#';
biop: '+' | '-' | '*' | '/' | '%' | '|' | '&' | '^' | oprel;
oprel: TK_OC_LE | TK_OC_GE | TK_OC_EQ | TK_OC_NE | TK_OC_AND | TK_OC_OR | TK_OC_SL;
unario: unop expr;
binario: expr biop expr;
ternario: expr '?' expr ':' expr;
*/
//wpipes: pipes;

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
