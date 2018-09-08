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
%left '*' '/'
%left '+' '-'
%right '['']'
%right '('')'
%left '<' TK_OC_LE
%left '>' TK_OC_GE
%left '!' TK_OC_EQ TK_OC_NE
%left TK_OC_AND
%left TK_OC_OR
%left TK_OC_SL TK_OC_SR



%%

programa: elemento;

elemento: decGlobal | decTipo | decFunc | elemento | ;

optStatic: TK_PR_STATIC | ;
optConst: TK_PR_CONST | ;

decGlobal: optStatic varGlobal ';';
varGlobal: TK_IDENTIFICADOR  tipo | varVetor tipo;
varVetor: TK_IDENTIFICADOR '[' TK_LIT_INT ']';

tipo:  TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING | TK_PR_CLASS; 

decTipo: TK_PR_CLASS TK_IDENTIFICADOR '[' listaTipo ']' ';';

listaTipo: campoTipo | campoTipo ':' listaTipo;
campoTipo: encaps tipo TK_IDENTIFICADOR;
encaps:  TK_PR_PROTECTED | TK_PR_PRIVATE | TK_PR_PUBLIC | ;


decFunc: cabecalhoFun corpoFun ';';
cabecalhoFun: optStatic tipo TK_IDENTIFICADOR listaFun;
listaFun: '(' parmsFun ')';
parmsFun: parms | parms ',' parmsFun;
parms: optConst tipo TK_IDENTIFICADOR;

corpoFun: cmdBlock;
cmdBlock: "{" cmdSimples "}";
cmdSimples: decVar | cmdAtr | inout | callFun | shift | rbcc | fluxo | pipes |;
decVar: defaultVar ';' | initVar;
defaultVar: optStatic optConst tipo TK_IDENTIFICADOR;
initVar: defaultVar '<=' valueVar ';';
valueVar: TK_IDENTIFICADOR | literal;

literal: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_CHAR | TK_LIT_STRING | litBool;
litBool: TK_LIT_FALSE | TK_LIT_TRUE;

cmdAtr: {/* TODO */};

%%

int yyerror(char const *s){
	fprintf(stderr,"[ERRO] Houve erro na linha %d: %s\n",get_line_number(), s); //printa msg padrão de erro seguido do número da linha e parametro (s)
	exit(3); // terminar o programa normalmente
}