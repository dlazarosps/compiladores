/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <iostream>
#include "../include/AstProgram.h"

using namespace std;

AstProgram::AstProgram()
{
	this->astType = AST_TYPE_PROGRAM;
}

AstProgram::~AstProgram()
{
	for (unsigned int i = 0; i < this->elements.size(); i++)
	{
		delete this->elements.at(i);
	}
}

void AstProgram::addElement(AbstractSyntaxTree* element)
{
	this->elements.push_back(element);
}

void AstProgram::addElements(vector<AbstractSyntaxTree*> *listOfElements)
{
	for (unsigned int i = 0; i < listOfElements->size(); i++)
	{
		this->elements.push_back(listOfElements->at(i));
	}
}

void AstProgram::SemanticAnalysis(SemanticAnalyzer* semanticAnalyzer)
{
	for (unsigned int i = 0; i < this->elements.size(); i++)
	{
		this->elements.at(i)->SemanticAnalysis(semanticAnalyzer);
	}
}
