/* ETAPA 3 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "valor_lexico.h"

AST *astCreate(int type, TValorLexico lex, AST leafs[])
{
	AST *node = calloc(1, sizeof(AST)); //aloca struct

	node->type = type;

	node->valor_lexico = lex;
	// memcpy(&node->valor_lexico, &lex, sizeof(lex));

	//node->leafs = leafs;
	memcpy(&node->leafs, &leafs, sizeof(leafs));

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
			fprintf(stderr, "[ERROR] Node Type: %d", node->type);
			break;
	}

	if (node->valor_lexico){
		switch (node->valor_lexico->tipo_valor)
		{
			case VALOR_CHAR:
				fprintf(stderr, ", %c) \n", node->valor_lexico->valor_char);
				break;
			case VALOR_STRING:
				fprintf(stderr, ", %s) \n", node->valor_lexico->valor_string);
				break;
			case VALOR_INT:
				fprintf(stderr, ", %i) \n", node->valor_lexico->valor_int);
				break;
			case VALOR_FLOAT:
				fprintf(stderr, ", %f) \n", node->valor_lexico->valor_float);
				break;
			case VALOR_BOOL:
				fprintf(stderr, ", %d) \n", node->valor_lexico->valor_bool);
				break;
			default:
				fprintf(stderr, "\n\t [ERROR] tipo valor: %d \n", node->valor_lexico->tipo_valor);
				break;
		}
	}
	else{
		fprintf(stderr, ",)\n");
	}

	for(i = 0; i < MAX_LEAF; i++){
		astPrint(node->leafs[i], nivel+1)
	}
}

void astDescomp(AST *ast)
{
	int i;
	if(!ast) return;
	if(ast){	
		switch(ast->type){

		case AST_PROGRAMA:
			fprintf(stderr, "AST_PROGRAMA");
			//ROOT da arvore ?
			break;

		case AST_ELEMENTO:
			astDescomp(ast->leafs[0]);

			if (ast->leafs[1] != NULL) {
				astDescomp(ast->leafs[1]);
			}
			break;

		case AST_TIPOSIMPLES:
		case AST_TIPO:
			switch (ast->valor_lexico->tipo_valor)
			{
				case VALOR_CHAR:
					fprintf(stderr, "%c", ast->valor_lexico->valor_char);
					break;
				case VALOR_STRING:
					fprintf(stderr, "%s", ast->valor_lexico->valor_string);
					break;
				case VALOR_INT:
					fprintf(stderr, "%i", ast->valor_lexico->valor_int);
					break;
				case VALOR_FLOAT:
					fprintf(stderr, "%f", ast->valor_lexico->valor_float);
					break;
				case VALOR_BOOL:
					fprintf(stderr, "%d", ast->valor_lexico->valor_bool);
					break;
				default:
					fprintf(stderr, "[ERROR] tipo valor: %d", ast->valor_lexico->tipo_valor);
					break;
			}
			break;

		case AST_DECGLOBAL:
			fprintf(stderr, "%s ", ast->leafs[0]->valor_lexico->valor_string); //id
			//descompila folhas genérico
			//TODO especializar
			i=1;
			while(ast->leafs[i] != NULL){
				astDescomp(ast->leafs[i]);
				i++;
			}
			break;

		case AST_DECTIPO:
			fprintf(stderr, "class ");
			fprintf(stderr, "%s ", ast->leafs[1]->valor_lexico->valor_string); //id
			fprintf(stderr, "[ ");
				astDescomp(ast->leafs[3]);
			fprintf(stderr, " ]");
			fprintf(stderr, ";");
			break;

		case AST_LISTATIPO:
			astDescomp(ast->leafs[0]);

			if (ast->leafs[2] != NULL)
			{
				fprintf(stderr, " : ");
				astDescomp(ast->leafs[2]);
			}
			break;

		// folha folha ID
		case AST_CAMPOTIPO:
		case AST_PARAMS:
			astDescomp(ast->leafs[0]);
			astDescomp(ast->leafs[1]);
			fprintf(stderr, "%s ", ast->leafs[2]->valor_lexico->valor_string); //id
			break;

		case AST_OPTCONST:
		case AST_ENCAPS:
			fprintf(stderr, "%s ", ast->valor_lexico->valor_string);
			// % empty ?
			break;

		case AST_DECFUNC:
			astDescomp(ast->leafs[0]);
			astDescomp(ast->leafs[1]);
			break;

		case AST_CABECALHOFUN:
			//descompila folhas genérico
			//TODO especializar
			// opStatic Tipo Nome Lista
			i = 0;
			while (ast->leafs[i] != NULL)
			{
				astDescomp(ast->leafs[i]);
				i++;
			}
			break;

		case AST_LISTAFUN:
			fprintf(stderr, "(");
				astDescomp(ast->leafs[1]);
			fprintf(stderr, ")");
			break;

		case AST_PARAMSFUNOREMPTY:
			if (ast->leafs[0] != NULL) {
				astDescomp(ast->leafs[0]);
			}
			break;

		case AST_PARAMSFUN:
			astDescomp(ast->leafs[0]);

			if (ast->leafs[2] != NULL)
			{
				fprintf(stderr, ", ");
				astDescomp(ast->leafs[2]);
			}
			break;

		//Produções que levam a outras produções 1 -> 1 
		case AST_CORPOFUN:
		case AST_CMDSTERMINADOSPONTOVIRGULA:
		case AST_CMDSTERMINADOSDOISPONTOS:
		case AST_CMDSIMPLESFOR:
		case AST_CMDBLOCO:
			astDescomp(ast->leafs[0]);
			break;

		case AST_BLOCO:
			fprintf(stderr, "{ ");
			astDescomp(ast->leafs[1]);
			fprintf(stderr, " }");
			break;

		case AST_LISTACOMANDOS:
			if (ast->leafs[0] != NULL)
			{
				astDescomp(ast->leafs[0]);
				astDescomp(ast->leafs[1]);

				if (ast->leafs[2]->type == AST_PONTOVIRG)
				{
					fprintf(stderr, ";");
				}
				else
				{
					fprintf(stderr, ":");
				}		
			}
			break;

		case AST_CMDDECVAR:
			// static const var
			if (ast->leafs[0] != NULL)
			{
				fprintf(stderr, "static ");
			}
			if (ast->leafs[1] != NULL)
			{
				fprintf(stderr, "const ");
			}
			astDescomp(ast->leafs[2]);
			break;

		case AST_DECVAR:
			astDescomp(ast->leafs[0]);
			astDescomp(ast->leafs[1]);

			if (ast->leafs[2] != NULL)
			{
				astDescomp(ast->leafs[2]);
			}
			
			break;

		case AST_OPTINIT:
			fprintf(stderr, " <= ");
			astDescomp(ast->leafs[1]);
			break;

		case AST_CMDATR:
			astDescomp(ast->leafs[0]);
			fprintf(stderr, " = ");
			astDescomp(ast->leafs[2]);
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
