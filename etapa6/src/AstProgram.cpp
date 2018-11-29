/* ETAPA 6 - TRABALHO DE COMPILADORES - Grupo Rho */

#include "../include/AstProgram.h"
#include "../include/CodeGenerator.h"

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

void AstProgram::GenerateCode(CodeGenerator* codeGenerator)
{
	for (unsigned int i = 0; i < this->elements.size(); i++)
	{
		this->elements.at(i)->GenerateCode(codeGenerator);
	}
}
