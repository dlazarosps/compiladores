/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

%{
	#include <vector>
	#include "../include/LexicalValue.h"
	#include "../include/AbstractSyntaxTree.h"
	#include "../include/AstExpression.h"
	#include "../include/parser.tab.h"
	int lineNumber = 1;
	extern int get_line_number();
%}

%option noyywrap

%x COMMENT

%%

"int"		{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_INT;}
"float" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_FLOAT;}
"bool"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_BOOL;}
"char" 		{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CHAR;}
"string" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_STRING;}
"if"    	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_IF; }
"then"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_THEN;}
"else"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_ELSE;}
"while" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_WHILE;}
"do" 		{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_DO;}
"input" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_INPUT;}
"output" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_OUTPUT;}
"return" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_RETURN;}
"const" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CONST;}
"static" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_STATIC;}
"foreach"   {yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_FOREACH;}
"for"   	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_FOR;}
"switch"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_SWITCH;}
"case"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CASE;}
"break"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_BREAK;}
"continue"  {yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CONTINUE;}
"class"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_CLASS;}
"private"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_PRIVATE;}
"public"  	{yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_PUBLIC;}
"protected" {yylval.lex = new LexicalValue(get_line_number(), TIPO_PALAVRA_RESERVADA, VALOR_STRING, yytext); return TK_PR_PROTECTED;}

"<=" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_LE;}
">=" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_GE;}
"==" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_EQ;}
"!=" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_NE;}
"&&" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_AND;}
"||" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_OR;}
"<<" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_SL;}
">>" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_SR;}
"%>%" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_FORWARD_PIPE;}
"%|%" 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_OPERADOR_COMPOSTO, VALOR_STRING, yytext); return TK_OC_BASH_PIPE;}

[\,\;\:\(\)\[\]\{\}\+\-\|\?\*\/\<\>\=\!\&\%\#\^\.\$] 	{yylval.lex = new LexicalValue(get_line_number(), TIPO_CARACTER_ESPECIAL, VALOR_STRING, yytext); return yytext[0];}

[0-9]+													{yylval.lex = new LexicalValue(get_line_number(), TIPO_LITERAL, VALOR_INT, yytext); return TK_LIT_INT;}
[0-9]*\.[0-9]+											{yylval.lex = new LexicalValue(get_line_number(), TIPO_LITERAL, VALOR_FLOAT, yytext); return TK_LIT_FLOAT;}
[0-9]*\.[0-9]+(e|E)(\+|\-)?[0-9]+						{yylval.lex = new LexicalValue(get_line_number(), TIPO_LITERAL, VALOR_FLOAT, yytext); return TK_LIT_FLOAT;} /*notação científica*/
"false"													{yylval.lex = new LexicalValue(get_line_number(), TIPO_LITERAL, VALOR_BOOL, yytext); return TK_LIT_FALSE;}
"true"													{yylval.lex = new LexicalValue(get_line_number(), TIPO_LITERAL, VALOR_BOOL, yytext); return TK_LIT_TRUE;}
\'.\'						{yylval.lex = new LexicalValue(get_line_number(), TIPO_LITERAL, VALOR_CHAR, yytext); return TK_LIT_CHAR;}
\"(\\.|[^"])*\" 			{yylval.lex = new LexicalValue(get_line_number(), TIPO_LITERAL, VALOR_STRING, yytext); return TK_LIT_STRING;}

[a-zA-Z_][a-zA-Z0-9_]* 		{yylval.lex = new LexicalValue(get_line_number(), TIPO_IDENTIFICADOR, VALOR_STRING, yytext); return TK_IDENTIFICADOR;}

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
