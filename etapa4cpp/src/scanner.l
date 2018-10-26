/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

%{
	#include "lexical_value.h"
	#include "ast.h"
	#include "parser.tab.h"
	int lineNumber = 1;
	extern int get_line_number();
%}

%option noyywrap

%x COMMENT

%%

"int"		{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_INT;}
"float" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_FLOAT;}
"bool"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_BOOL;}
"char" 		{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CHAR;}
"string" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_STRING;}
"if"    	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_IF; }
"then"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_THEN;}
"else"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_ELSE;}
"while" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_WHILE;}
"do" 		{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_DO;}
"input" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_INPUT;}
"output" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_OUTPUT;}
"return" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_RETURN;}
"const" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CONST;}
"static" 	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_STATIC;}
"foreach"   {yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_FOREACH;}
"for"   	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_FOR;}
"switch"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_SWITCH;}
"case"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CASE;}
"break"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_BREAK;}
"continue"  {yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CONTINUE;}
"class"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CLASS;}
"private"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_PRIVATE;}
"public"  	{yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_PUBLIC;}
"protected" {yylval.valor_lexico = GetValorLexico(TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_PROTECTED;}

"<=" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_LE;}
">=" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_GE;}
"==" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_EQ;}
"!=" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_NE;}
"&&" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_AND;}
"||" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_OR;}
"<<" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_SL;}
">>" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_SR;}
"%>%" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_FORWARD_PIPE;}
"%|%" 	{yylval.valor_lexico = GetValorLexico(TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_BASH_PIPE;}

[\,\;\:\(\)\[\]\{\}\+\-\|\?\*\/\<\>\=\!\&\%\#\^\.\$] 	{yylval.valor_lexico = GetValorLexico(TIPO_CARACTER_ESPECIAL, VALOR_STRING, yytext); return yytext[0];}
[0-9]+													{yylval.valor_lexico = GetValorLexico(TIPO_LITERAL, VALOR_INT, yytext); return TK_LIT_INT;}
[0-9]*\.[0-9]+											{yylval.valor_lexico = GetValorLexico(TIPO_LITERAL, VALOR_FLOAT, yytext); return TK_LIT_FLOAT;}
[0-9]*\.[0-9]+(e|E)(\+|\-)?[0-9]+						{yylval.valor_lexico = GetValorLexico(TIPO_LITERAL, VALOR_FLOAT, yytext); return TK_LIT_FLOAT;} /*notação científica*/
"false"													{yylval.valor_lexico = GetValorLexico(TIPO_LITERAL, VALOR_BOOL, yytext); return TK_LIT_FALSE;}
"true"													{yylval.valor_lexico = GetValorLexico(TIPO_LITERAL, VALOR_BOOL, yytext); return TK_LIT_TRUE;}
\'.\'						{yylval.valor_lexico = GetValorLexico(TIPO_LITERAL, VALOR_CHAR, yytext); return TK_LIT_CHAR;}
\"(\\.|[^"])*\" 			{yylval.valor_lexico = GetValorLexico(TIPO_LITERAL, VALOR_STRING, yytext); return TK_LIT_STRING;}

[a-zA-Z_][a-zA-Z0-9_]* 		{yylval.valor_lexico = GetValorLexico(TIPO_IDENTIFICADOR, VALOR_STRING, yytext); return TK_IDENTIFICADOR;}

[ \t] {}
[\n]    {lineNumber++;}

"//".* {}

"/*"         BEGIN(COMMENT);

<COMMENT>[^*\n]*        /* consome tudo diferente de '*' */
<COMMENT>"*"+[^*/\n]*   /* consome '*' não seguidos de '/' */
<COMMENT>\n             {lineNumber++;}
<COMMENT>"*"+"/"        BEGIN(INITIAL);

. {return TOKEN_ERRO;}

%%

int get_line_number(void){
    return lineNumber;
}
