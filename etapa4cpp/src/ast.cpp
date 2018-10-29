/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <iostream>
#include <vector>
#include "../include/ast.h"
#include "../include/lexical_value.h"

using namespace std;

AbstractSyntaxTree::AbstractSyntaxTree(int type, LexicalValue* lexicalValue)
{
	this->type = type;
	this->lexicalValue = lexicalValue;
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
	// TODO: review this clean up
	for (unsigned int i = 0; i < this->leafs.size(); i++)
	{
		delete this->leafs.at(i);
	}

	if(this->lexicalValue != NULL) {
		delete this->lexicalValue;
	}
}

void AbstractSyntaxTree::AddLeaf(AbstractSyntaxTree* node)
{
	this->leafs.push_back(node);
}

int AbstractSyntaxTree::GetType()
{
	return this->type;
}

LexicalValue* AbstractSyntaxTree::GetLexicalValue()
{
	return this->lexicalValue;
}

int AbstractSyntaxTree::GetLeafsSize()
{
	return this->leafs.size();
}

AbstractSyntaxTree* AbstractSyntaxTree::GetNodeLeaf(int index)
{
	return this->leafs[index];
}

void AbstractSyntaxTree::Decompile()
{
	LexicalValue *lex;

	/* //TODO check AST IS NULL
	if (this == NULL)
		return;
	else
	{
	*/
		//printa valor lexico
		if (this->GetType() == AST_TERMINAL)
		{
			lex = this->GetLexicalValue();
			cout << lex->ValueToString() << " ";
		}

		//recursão para as folhas
		for (auto& leaf : this->leafs) {
			leaf->Decompile();
		}

	//}

	return;
}

void AbstractSyntaxTree::Print(int nivel)
{
	LexicalValue *lex;
	//TODO AST empty
	// if(this == NULL) return;

	int i;
	for(i = 0; i < nivel; i++)
		cout << "  ";

	cout << "AST(";

	switch(this->GetType()){
		case AST_PROGRAMA: cout << "AST_PROGRAMA"; break;
		case AST_ELEMENTO: cout << "AST_ELEMENTO"; break;
		case AST_OPTCONST: cout << "AST_OPTCONST"; break;
		case AST_TIPOSIMPLES: cout << "AST_TIPOSIMPLES"; break;
		case AST_TIPO: cout << "AST_TIPO"; break;
		case AST_DECGLOBAL: cout << "AST_DECGLOBAL"; break;
		case AST_DECTIPO: cout << "AST_DECTIPO"; break;
		case AST_LISTATIPO: cout << "AST_LISTATIPO"; break;
		case AST_CAMPOTIPO: cout << "AST_CAMPOTIPO"; break;
		case AST_ENCAPS: cout << "AST_ENCAPS"; break;
		case AST_DECFUNC: cout << "AST_DECFUNC"; break;
		case AST_CABECALHOFUN: cout << "AST_CABECALHOFUN"; break;
		case AST_LISTAFUN: cout << "AST_LISTAFUN"; break;
		case AST_PARAMSFUNOREMPTY: cout << "AST_PARAMSFUNOREMPTY"; break;
		case AST_PARAMSFUN: cout << "AST_PARAMSFUN"; break;
		case AST_PARAMS: cout << "AST_PARAMS"; break;
		case AST_CORPOFUN: cout << "AST_CORPOFUN"; break;
		case AST_BLOCO: cout << "AST_BLOCO"; break;
		case AST_LISTACOMANDOS: cout << "AST_LISTACOMANDOS"; break;
		case AST_CMDSTERMINADOSPONTOVIRGULA: cout << "AST_CMDSTERMINADOSPONTOVIRGULA"; break;
		case AST_CMDSTERMINADOSDOISPONTOS: cout << "AST_CMDSTERMINADOSDOISPONTOS"; break;
		case AST_CMDSIMPLESFOR: cout << "AST_CMDSIMPLESFOR"; break;
		case AST_CMDBLOCO: cout << "AST_CMDBLOCO"; break;
		case AST_CMDDECVAR: cout << "AST_CMDDECVAR"; break;
		case AST_DECVAR: cout << "AST_DECVAR"; break;
		case AST_OPTINIT: cout << "AST_OPTINIT"; break;
		case AST_CMDATR: cout << "AST_CMDATR"; break;
		case AST_CMDFUNCCALL: cout << "AST_CMDFUNCCALL"; break;
		case AST_CMDIO: cout << "AST_CMDIO"; break;
		case AST_CMDIN: cout << "AST_CMDIN"; break;
		case AST_CMDOUT: cout << "AST_CMDOUT"; break;
		case AST_SHIFT: cout << "AST_SHIFT"; break;
		case AST_SHIFTOP: cout << "AST_SHIFTOP"; break;
		case AST_RBC: cout << "AST_RBC"; break;
		case AST_FLUXO: cout << "AST_FLUXO"; break;
		case AST_STMT: cout << "AST_STMT"; break;
		case AST_IFST: cout << "AST_IFST"; break;
		case AST_FOREACH: cout << "AST_FOREACH"; break;
		case AST_FOR: cout << "AST_FOR"; break;
		case AST_LISTAFOR: cout << "AST_LISTAFOR"; break;
		case AST_WHILE: cout << "AST_WHILE"; break;
		case AST_DOWHILE: cout << "AST_DOWHILE"; break;
		case AST_SWITCH: cout << "AST_SWITCH"; break;
		case AST_CMDPIPE: cout << "AST_CMDPIPE"; break;
		case AST_PIPELIST: cout << "AST_PIPELIST"; break;
		case AST_PIPEOP: cout << "AST_PIPEOP"; break;
		case AST_LISTAEXPROREMPTY: cout << "AST_LISTAEXPROREMPTY"; break;
		case AST_LISTAEXPR: cout << "AST_LISTAEXPR"; break;
		case AST_VARIABLE: cout << "AST_VARIABLE"; break;
		case AST_VARIABLEINDEX: cout << "AST_VARIABLEINDEX"; break;
		case AST_VARIABLEATTRIBUTE: cout << "AST_VARIABLEATTRIBUTE"; break;
		case AST_EXPRFUNCCALL: cout << "AST_EXPRFUNCCALL"; break;
		case AST_EXPRPIPE: cout << "AST_EXPRPIPE"; break;
		case AST_UNOP: cout << "AST_UNOP"; break;
		case AST_UNARIO: cout << "AST_UNARIO"; break;
		case AST_BIOP: cout << "AST_BIOP"; break;
		case AST_BINARIO: cout << "AST_BINARIO"; break;
		case AST_RELOP: cout << "AST_RELOP"; break;
		case AST_TERNARIO: cout << "AST_TERNARIO"; break;
		case AST_LITERAL: cout << "AST_LITERAL"; break;
		case AST_LITERALNUM: cout << "AST_LITERALNUM"; break;
		case AST_LITERALCHAR: cout << "AST_LITERALCHAR"; break;
		case AST_LITERALBOOL: cout << "AST_LITERALBOOL"; break;
		case AST_TERMINAL: cout << "AST_TERMINAL"; break;
		case AST_CMDCASE: cout << "AST_CMDCASE"; break;
		case AST_EXPR: cout << "AST_EXPR"; break;
		case AST_EMPTY: cout << "AST_EMPTY"; break;
		default:
			cerr << "[ERROR] Node Type: " << this->GetType() << "\n";
			break;
	}

	lex = this->GetLexicalValue();
	if (lex != NULL){
		cout << ", " << lex->ValueToString() << ") \n";
	}
	else{
		cout << ",)\n";
	}

	//recursão para as folhas
	for (auto &leaf : this->leafs)
	{
		leaf->Print(nivel+1);
	}
}
