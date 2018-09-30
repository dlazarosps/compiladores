/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *astCreate(int type, VALOR_LEXICO lex, AST leafs[])
{
	AST *node = calloc(1, sizeof(AST)); //aloca struct

	node->type = type;
	node->valor_lexico = lex; //copia struct valor lexico
	node->leafs = leafs; //copia array de folhas

	return node;
}

void astPrint(AST *node, int nivel)
{
	//Testa se Nodo vazio	
	if(!node) return;
	
	int i;
	for(i = 0; i < level; i++) 
		fprintf(stderr,"  ");
	
	fprintf(stderr, "AST(");
	
	switch(node->type){
		case TK_PR_INT: fprintf(stderr, "TK_PR_INT"); break;
		case TK_PR_FLOAT: fprintf(stderr, "TK_PR_FLOAT"); break;
		case TK_PR_BOOL: fprintf(stderr, "TK_PR_BOOL"); break;
		case TK_PR_CHAR: fprintf(stderr, "TK_PR_CHAR"); break;
		case TK_PR_STRING: fprintf(stderr, "TK_PR_STRING"); break;
		case TK_PR_IF: fprintf(stderr, "TK_PR_IF"); break;
		case TK_PR_THEN: fprintf(stderr, "TK_PR_THEN"); break;
		case TK_PR_ELSE: fprintf(stderr, "TK_PR_ELSE"); break;
		case TK_PR_WHILE: fprintf(stderr,"TK_PR_WHILE"); break;
		case TK_PR_DO: fprintf(stderr,"TK_PR_DO"); break;
		case TK_PR_INPUT: fprintf(stderr,"TK_PR_INPUT"); break;
		case TK_PR_OUTPUT: fprintf(stderr,"TK_PR_OUTPUT"); break;
		case TK_PR_RETURN: fprintf(stderr,"TK_PR_RETURN"); break;
		case TK_PR_CONST: fprintf(stderr,"TK_PR_CONST"); break;
		case TK_PR_STATIC: fprintf(stderr,"TK_PR_STATIC"); break;
		case TK_PR_FOREACH: fprintf(stderr,"TK_PR_FOREACH"); break;
		case TK_PR_FOR: fprintf(stderr, "TK_PR_FOR"); break;
		case TK_PR_SWITCH: fprintf(stderr, "TK_PR_SWITCH"); break;
		case TK_PR_CASE: fprintf(stderr, "TK_PR_CASE"); break;
		case TK_PR_BREAK: fprintf(stderr, "TK_PR_BREAK"); break;
		case TK_PR_CONTINUE: fprintf(stderr, "TK_PR_CONTINUE"); break;
		case TK_PR_CLASS: fprintf(stderr, "TK_PR_CLASS"); break;
		case TK_PR_PRIVATE: fprintf(stderr, "TK_PR_PRIVATE"); break;
		case TK_PR_PUBLIC: fprintf(stderr, "TK_PR_PUBLIC"); break;
		case TK_PR_PROTECTED: fprintf(stderr, "TK_PR_PROTECTED"); break;
		case TK_OC_LE: fprintf(stderr, "TK_OC_LE"); break;
		case TK_OC_GE: fprintf(stderr, "TK_OC_GE"); break;
		case TK_OC_EQ: fprintf(stderr, "TK_OC_EQ"); break;
		case TK_OC_NE: fprintf(stderr, "TK_OC_NE"); break;
		case TK_OC_AND: fprintf(stderr, "TK_OC_AND"); break;
		case TK_OC_OR: fprintf(stderr, "TK_OC_OR"); break;
		case TK_OC_SL: fprintf(stderr, "TK_OC_SL"); break;
		case TK_OC_SR: fprintf(stderr, "TK_OC_SR"); break;
		case TK_OC_FORWARD_PIPE: fprintf(stderr, "TK_OC_FORWARD_PIPE"); break;
		case TK_OC_BASH_PIPE: fprintf(stderr, "TK_OC_BASH_PIPE"); break;
		case TK_LIT_INT: fprintf(stderr, "TK_LIT_INT"); break;
		case TK_LIT_FLOAT: fprintf(stderr, "TK_LIT_FLOAT"); break;
		case TK_LIT_FALSE: fprintf(stderr, "TK_LIT_FALSE"); break;
		case TK_LIT_TRUE: fprintf(stderr, "TK_LIT_TRUE"); break;
		case TK_LIT_CHAR: fprintf(stderr, "TK_LIT_CHAR"); break;
		case TK_LIT_STRING: fprintf(stderr, "TK_LIT_STRING"); break;
		case TK_IDENTIFICADOR: fprintf(stderr, "TK_IDENTIFICADOR"); break;
		case TOKEN_ERRO: fprintf(stderr, "TOKEN_ERRO"); break;
		case AST_PROGRAMA: fprintf(stderr, "AST_PROGRAMA"); break;
		case AST_ELEMENTO: fprintf(stderr, "AST_ELEMENTO"); break;
		case AST_OPTCONST: fprintf(stderr, "AST_OPTCONST"); break;
		case AST_TIPOSIMPLES: fprintf(stderr, "AST_TIPOSIMPLES"); break;
		case AST_TIPO: fprintf(stderr, "AST_TIPO"); break;
		case AST_DECGLOBAL: fprintf(stderr, "AST_DECGLOBAL"); break;
		case AST_DECTIPO: fprintf(stderr, "AST_DECTIPO"); break;
		case AST_LISTATIPO: fprintf(stderr, "AST_LISTATIPO"); break;
		case AST_CAMPOTIPO: fprintf(stderr, "AST_CAMPOTIPO"); break;
		case AST_ENCAPS: fprintf(stderr, "AST_ENCAPS"); break;
		case AST_DECFUNC: fprintf(stderr, "AST_DECFUNC"); break;
		case AST_CABECALHOFUN: fprintf(stderr, "AST_CABECALHOFUN"); break;
		case AST_LISTAFUN: fprintf(stderr, "AST_LISTAFUN"); break;
		case AST_PARAMSFUNOREMPTY: fprintf(stderr, "AST_PARAMSFUNOREMPTY"); break;
		case AST_PARAMSFUN: fprintf(stderr, "AST_PARAMSFUN"); break;
		case AST_PARAMS: fprintf(stderr, "AST_PARAMS"); break;
		case AST_CORPOFUN: fprintf(stderr, "AST_CORPOFUN"); break;
		case AST_BLOCO: fprintf(stderr, "AST_BLOCO"); break;
		case AST_LISTACOMANDOS: fprintf(stderr, "AST_LISTACOMANDOS"); break;
		case AST_CMDSTERMINADOSPONTOVIRGULA: fprintf(stderr, "AST_CMDSTERMINADOSPONTOVIRGULA"); break;
		case AST_CMDSTERMINADOSDOISPONTOS: fprintf(stderr, "AST_CMDSTERMINADOSDOISPONTOS"); break;
		case AST_CMDSIMPLESFOR: fprintf(stderr, "AST_CMDSIMPLESFOR"); break;
		case AST_CMDBLOCO: fprintf(stderr, "AST_CMDBLOCO"); break;
		case AST_CMDDECVAR: fprintf(stderr, "AST_CMDDECVAR"); break;
		case AST_DECVAR: fprintf(stderr, "AST_DECVAR"); break;
		case AST_OPTINIT: fprintf(stderr, "AST_OPTINIT"); break;
		case AST_CMDATR: fprintf(stderr, "AST_CMDATR"); break;
		case AST_CMDFUNCCALL: fprintf(stderr, "AST_CMDFUNCCALL"); break;
		case AST_CMDIO: fprintf(stderr, "AST_CMDIO"); break;
		case AST_CMDIN: fprintf(stderr, "AST_CMDIN"); break;
		case AST_CMDOUT: fprintf(stderr, "AST_CMDOUT"); break;
		case AST_SHIFT: fprintf(stderr, "AST_SHIFT"); break;
		case AST_SHIFTOP: fprintf(stderr, "AST_SHIFTOP"); break;
		case AST_RBC: fprintf(stderr, "AST_RBC"); break;
		case AST_FLUXO: fprintf(stderr, "AST_FLUXO"); break;
		case AST_STMT: fprintf(stderr, "AST_STMT"); break;
		case AST_IFST: fprintf(stderr, "AST_IFST"); break;
		case AST_FOREACH: fprintf(stderr, "AST_FOREACH"); break;
		case AST_FOR: fprintf(stderr, "AST_FOR"); break;
		case AST_LISTAFOR: fprintf(stderr, "AST_LISTAFOR"); break;
		case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
		case AST_DOWHILE: fprintf(stderr, "AST_DOWHILE"); break;
		case AST_SWITCH: fprintf(stderr, "AST_SWITCH"); break;
		case AST_CMDPIPE: fprintf(stderr, "AST_CMDPIPE"); break;
		case AST_PIPELIST: fprintf(stderr, "AST_PIPELIST"); break;
		case AST_PIPEOP: fprintf(stderr, "AST_PIPEOP"); break;
		case AST_LISTAEXPROREMPTY: fprintf(stderr, "AST_LISTAEXPROREMPTY"); break;
		case AST_LISTAEXPR: fprintf(stderr, "AST_LISTAEXPR"); break;
		case AST_VARIABLE: fprintf(stderr, "AST_VARIABLE"); break;
		case AST_VARIABLEINDEX: fprintf(stderr, "AST_VARIABLEINDEX"); break;
		case AST_VARIABLEATTRIBUTE: fprintf(stderr, "AST_VARIABLEATTRIBUTE"); break;
		case AST_EXPRFUNCCALL: fprintf(stderr, "AST_EXPRFUNCCALL"); break;
		case AST_EXPRPIPE: fprintf(stderr, "AST_EXPRPIPE"); break;
		case AST_UNOP: fprintf(stderr, "AST_UNOP"); break;
		case AST_UNARIO: fprintf(stderr, "AST_UNARIO"); break;
		case AST_BIOP: fprintf(stderr, "AST_BIOP"); break;
		case AST_BINARIO: fprintf(stderr, "AST_BINARIO"); break;
		case AST_RELOP: fprintf(stderr, "AST_RELOP"); break;
		case AST_TERNARIO: fprintf(stderr, "AST_TERNARIO"); break;
		case AST_LITERAL: fprintf(stderr, "AST_LITERAL"); break;
		case AST_LITERALNUM: fprintf(stderr, "AST_LITERALNUM"); break;
		case AST_LITERALCHAR: fprintf(stderr, "AST_LITERALCHAR"); break;
		case AST_LITERALBOOL: fprintf(stderr, "AST_LITERALBOOL"); break;
		default:
			fprintf(stderr, "Node Type: %d", node->type);
			break;
	}

	if (node->valor_lexico){
		fprintf(stderr, ", %s)\n", node->valor_lexico);
	}
	else{
		fprintf(stderr, ",)\n");
	}

	for(i = 0; i < MAX_LEAF; i++){
		void astPrint(node->leafs[i], nivel+1)
	}
}

void astDescomp(AST *ast)
{

	if(!ast) return;
	if(ast){	
		//TODO descompile print
		switch(ast->type){
		case TK_PR_INT:
			fprintf(stderr, "int");
			break;
		case TK_PR_FLOAT:
			fprintf(stderr, "float");
			break;
		case TK_PR_BOOL:
			fprintf(stderr, "bool");
			break;
		case TK_PR_CHAR:
			fprintf(stderr, "char");
			break;
		case TK_PR_STRING:
			fprintf(stderr, "string");
			break;
		case TK_PR_IF:
			fprintf(stderr, "if");
			break;
		case TK_PR_THEN:
			fprintf(stderr, "then");
			break;
		case TK_PR_ELSE:
			fprintf(stderr, "else");
			break;
		case TK_PR_WHILE:
			fprintf(stderr, "while");
			break;
		case TK_PR_DO:
			fprintf(stderr, "do");
			break;
		case TK_PR_INPUT:
			fprintf(stderr, "input");
			break;
		case TK_PR_OUTPUT:
			fprintf(stderr, "output");
			break;
		case TK_PR_RETURN:
			fprintf(stderr, "return");
			break;
		case TK_PR_CONST:
			fprintf(stderr, "const");
			break;
		case TK_PR_STATIC:
			fprintf(stderr, "static");
			break;
		case TK_PR_FOREACH:
			fprintf(stderr, "foreach");
			break;
		case TK_PR_FOR:
			fprintf(stderr, "for");
			break;
		case TK_PR_SWITCH:
			fprintf(stderr, "switch");
			break;
		case TK_PR_CASE:
			fprintf(stderr, "case");
			break;
		case TK_PR_BREAK:
			fprintf(stderr, "break");
			break;
		case TK_PR_CONTINUE:
			fprintf(stderr, "continue");
			break;
		case TK_PR_CLASS:
			fprintf(stderr, "class");
			break;
		case TK_PR_PRIVATE:
			fprintf(stderr, "private");
			break;
		case TK_PR_PUBLIC:
			fprintf(stderr, "public");
			break;
		case TK_PR_PROTECTED:
			fprintf(stderr, "protected");
			break;
		case TK_OC_LE:
			fprintf(stderr, "<=");
			break;
		case TK_OC_GE:
			fprintf(stderr, ">=");
			break;
		case TK_OC_EQ:
			fprintf(stderr, "==");
			break;
		case TK_OC_NE:
			fprintf(stderr, "!=");
			break;
		case TK_OC_AND:
			fprintf(stderr, "&&");
			break;
		case TK_OC_OR:
			fprintf(stderr, "||");
			break;
		case TK_OC_SL:
			fprintf(stderr, "<<");
			break;
		case TK_OC_SR:
			fprintf(stderr, ">>");
			break;
		case TK_OC_FORWARD_PIPE:
			fprintf(stderr, "%%>%%");
			break;
		case TK_OC_BASH_PIPE:
			fprintf(stderr, "%%|%%");
			break;
		case TK_LIT_INT:
			fprintf(stderr, "TK_LIT_INT");
			//get valor_lexico
			break;
		case TK_LIT_FLOAT:
			fprintf(stderr, "TK_LIT_FLOAT");
			//get valor_lexico
			break;
		case TK_LIT_FALSE:
			fprintf(stderr, "false");
			break;
		case TK_LIT_TRUE:
			fprintf(stderr, "true");
			break;
		case TK_LIT_CHAR:
			fprintf(stderr, "TK_LIT_CHAR");
			//get valor_lexico
			break;
		case TK_LIT_STRING:
			fprintf(stderr, "TK_LIT_STRING");
			//get valor_lexico
			break;
		case TK_IDENTIFICADOR:
			fprintf(stderr, "TK_IDENTIFICADOR");
			//get valor_lexico
			break;
		case AST_PROGRAMA:
			fprintf(stderr, "AST_PROGRAMA");
			//aplicar recursão
			break;
		case AST_ELEMENTO:
			fprintf(stderr, "AST_ELEMENTO");
			break;
		case AST_OPTCONST:
			fprintf(stderr, "AST_OPTCONST");
			break;
		case AST_TIPOSIMPLES:
			fprintf(stderr, "AST_TIPOSIMPLES");
			break;
		case AST_TIPO:
			fprintf(stderr, "AST_TIPO");
			break;
		case AST_DECGLOBAL:
			fprintf(stderr, "AST_DECGLOBAL");
			break;
		case AST_DECTIPO:
			fprintf(stderr, "AST_DECTIPO");
			break;
		case AST_LISTATIPO:
			fprintf(stderr, "AST_LISTATIPO");
			break;
		case AST_CAMPOTIPO:
			fprintf(stderr, "AST_CAMPOTIPO");
			break;
		case AST_ENCAPS:
			fprintf(stderr, "AST_ENCAPS");
			break;
		case AST_DECFUNC:
			fprintf(stderr, "AST_DECFUNC");
			break;
		case AST_CABECALHOFUN:
			fprintf(stderr, "AST_CABECALHOFUN");
			break;
		case AST_LISTAFUN:
			fprintf(stderr, "AST_LISTAFUN");
			break;
		case AST_PARAMSFUNOREMPTY:
			fprintf(stderr, "AST_PARAMSFUNOREMPTY");
			break;
		case AST_PARAMSFUN:
			fprintf(stderr, "AST_PARAMSFUN");
			break;
		case AST_PARAMS:
			fprintf(stderr, "AST_PARAMS");
			break;
		case AST_CORPOFUN:
			fprintf(stderr, "AST_CORPOFUN");
			break;
		case AST_BLOCO:
			fprintf(stderr, "AST_BLOCO");
			break;
		case AST_LISTACOMANDOS:
			fprintf(stderr, "AST_LISTACOMANDOS");
			break;
		case AST_CMDSTERMINADOSPONTOVIRGULA:
			fprintf(stderr, "AST_CMDSTERMINADOSPONTOVIRGULA");
			break;
		case AST_CMDSTERMINADOSDOISPONTOS:
			fprintf(stderr, "AST_CMDSTERMINADOSDOISPONTOS");
			break;
		case AST_CMDSIMPLESFOR:
			fprintf(stderr, "AST_CMDSIMPLESFOR");
			break;
		case AST_CMDBLOCO:
			fprintf(stderr, "AST_CMDBLOCO");
			break;
		case AST_CMDDECVAR:
			fprintf(stderr, "AST_CMDDECVAR");
			break;
		case AST_DECVAR:
			fprintf(stderr, "AST_DECVAR");
			break;
		case AST_OPTINIT:
			fprintf(stderr, "AST_OPTINIT");
			break;
		case AST_CMDATR:
			fprintf(stderr, "AST_CMDATR");
			break;
		case AST_CMDFUNCCALL:
			fprintf(stderr, "AST_CMDFUNCCALL");
			break;
		case AST_CMDIO:
			fprintf(stderr, "AST_CMDIO");
			break;
		case AST_CMDIN:
			fprintf(stderr, "AST_CMDIN");
			break;
		case AST_CMDOUT:
			fprintf(stderr, "AST_CMDOUT");
			break;
		case AST_SHIFT:
			fprintf(stderr, "AST_SHIFT");
			break;
		case AST_SHIFTOP:
			fprintf(stderr, "AST_SHIFTOP");
			break;
		case AST_RBC:
			fprintf(stderr, "AST_RBC");
			break;
		case AST_FLUXO:
			fprintf(stderr, "AST_FLUXO");
			break;
		case AST_STMT:
			fprintf(stderr, "AST_STMT");
			break;
		case AST_IFST:
			fprintf(stderr, "AST_IFST");
			break;
		case AST_FOREACH:
			fprintf(stderr, "AST_FOREACH");
			break;
		case AST_FOR:
			fprintf(stderr, "AST_FOR");
			break;
		case AST_LISTAFOR:
			fprintf(stderr, "AST_LISTAFOR");
			break;
		case AST_WHILE:
			fprintf(stderr, "AST_WHILE");
			break;
		case AST_DOWHILE:
			fprintf(stderr, "AST_DOWHILE");
			break;
		case AST_SWITCH:
			fprintf(stderr, "AST_SWITCH");
			break;
		case AST_CMDPIPE:
			fprintf(stderr, "AST_CMDPIPE");
			break;
		case AST_PIPELIST:
			fprintf(stderr, "AST_PIPELIST");
			break;
		case AST_PIPEOP:
			fprintf(stderr, "AST_PIPEOP");
			break;
		case AST_LISTAEXPROREMPTY:
			fprintf(stderr, "AST_LISTAEXPROREMPTY");
			break;
		case AST_LISTAEXPR:
			fprintf(stderr, "AST_LISTAEXPR");
			break;
		case AST_VARIABLE:
			fprintf(stderr, "AST_VARIABLE");
			break;
		case AST_VARIABLEINDEX:
			fprintf(stderr, "AST_VARIABLEINDEX");
			break;
		case AST_VARIABLEATTRIBUTE:
			fprintf(stderr, "AST_VARIABLEATTRIBUTE");
			break;
		case AST_EXPRFUNCCALL:
			fprintf(stderr, "AST_EXPRFUNCCALL");
			break;
		case AST_EXPRPIPE:
			fprintf(stderr, "AST_EXPRPIPE");
			break;
		case AST_UNOP:
			fprintf(stderr, "AST_UNOP");
			break;
		case AST_UNARIO:
			fprintf(stderr, "AST_UNARIO");
			break;
		case AST_BIOP:
			fprintf(stderr, "AST_BIOP");
			break;
		case AST_BINARIO:
			fprintf(stderr, "AST_BINARIO");
			break;
		case AST_RELOP:
			fprintf(stderr, "AST_RELOP");
			break;
		case AST_TERNARIO:
			fprintf(stderr, "AST_TERNARIO");
			break;
		case AST_LITERAL:
			fprintf(stderr, "AST_LITERAL");
			break;
		case AST_LITERALNUM:
			fprintf(stderr, "AST_LITERALNUM");
			break;
		case AST_LITERALCHAR:
			fprintf(stderr, "AST_LITERALCHAR");
			break;
		case AST_LITERALBOOL:
			fprintf(stderr, "AST_LITERALBOOL");
			break;
		case TOKEN_ERRO:
		default:
			fprintf(stderr, "TOKEN_ERRO");
			break;
		}
	}
 
	return;

}
