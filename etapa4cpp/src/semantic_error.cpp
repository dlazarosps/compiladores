#include <string>
#include <vector>

#include "semantic_error.h"

using namespace std;

SemanticError::SemanticError(int code, int line)
{
    this->code = code;
    this->line = line;
}

SemanticError::~SemanticError()
{

}

int SemanticError::GetCode()
{
    return this->code;
}

int SemanticError::GetLine()
{
    return this->line;
}

void SemanticError::Print()
{
    // TODO: print error
}
