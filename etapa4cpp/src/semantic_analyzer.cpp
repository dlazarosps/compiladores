/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include <stack>
#include "ast.h"
#include "scope_stack.h"
#include "symbol_table.h"

using namespace std;

/*
 * SemanticAnalyzer functions
 */

SemanticAnalyzer::SemanticAnalyzer()
{

}

SemanticAnalyzer::~SemanticAnalyzer()
{
    // TODO: clean up
}

int SemanticAnalyzer::GetErrorNumber()
{
    return this->errorNumber;
}

void SetErrorNumber(int Err)
{
    this->errorNumber = Err;
}

string SemanticAnalyzer::GetLineError()
{
    return this->lineError;
}

void SemanticAnalyzer::SetLineError(int rowNumber, string rowText)
{
    this->lineError = "line " + to_string(rowNumber) + " : " + rowText;
}

void SemanticAnalyzer::SetLineError(AbstractSyntaxTree node)
{
    int rowNumber;
    string rowText;

    // rowNumber = node->GetLineFromValorLexico(); //TODO get private value
    // rowText = node->PrintASTDescompNode(); //TODO print one line code

    this->SetLineError(rowNumber, rowText);
}

SymbolTableEntry *SemanticAnalyzer::CheckSemantic(AbstractSyntaxTree node)
{
    //TODO: convert C++
    //TODO: translate pseudo codes
    /* 
    int leafsize;
    AST *child;

    //pega quantidade de folhas
    leafsize = listSize(node->lefts);

    //para cada tipo de construção gramatical aplica atribuição de tipo e tamanho e insere na stack hash
    switch (node->type)
    {

    case AST_DECGLOBAL:
        // TESTA já_declarado_aqui (hash scopo corrente)
        // SE sim
        //      ret = ERR_DECLARED
        // SENÃO
        //      pega tipo
        child = listGet(node->leafs, (leafsize - 1)); //decglobal = id ... tipo ';'
        //      *setSize is_vector => leafsize (6 || 7) => listget(node->leafs, 3) => size * literal
        //      adiciona na hash_stack {natureza, setType, setSize}
        //      ret = 0
        break;

    case AST_DECTIPO:
        // TESTA já_declarado_aqui (hash scopo corrente)
        // SE sim
        //      ret = ERR_DECLARED
        // SENÃO
        //      conta_campos => "AST_listTipo" => listget(nodo->leafs, 4) => setSize
        //      adiciona na hash_stack {natureza, setType, setSize}
        //      ret = 0
        break;

    case AST_DECFUN:
        // cria escopo push_hash_stack
        // checkSemantic folhas
        //      AST_CABECALHOFUN => ret
        //      SE ret == 0
        //          AST_CORPOFUN => ret
        // return ret
        break;

    case AST_CABECALHOFUN:
        // pop escopo (hash da função)
        // TESTA já_declarado_aqui
        // SE sim
        //      ret = ERR_DECLARED
        // SENÃO
        //      adiciona na hash_stack {natureza, setType, setSize}
        //      conta_argumentos => "AST_listfun" => listget(nodo->leafs, leafSize) => add hash
        //      push hash
        //      checkSemantic argumentos ? AST_listfun => "PARAMSFUN" => PARAMS (add hash)
        //      return ret
        break;

    case AST_PARAMS:
        //TODO check TK_ID params
        // ? case de cima
        break;

    case AST_DECVAR:
        // TESTA já_declarado_aqui (hash scopo corrente)
        // SE sim
        //      ret = ERR_DECLARED
        // SENÃO
        //      pega tipo
        child = listGet(node->leafs, 1);
        //          SE tipo usuario  => já_declarado_aqui
        //          SE inicializado ? conferir tipo
        //      adiciona na hash_stack {natureza, setType, setSize}
        //      ret = 0
        break;

    case AST_CMDATR:
        // TESTA já_declarado_aqui
        // SE não
        //      ret = ERR_UNDECLARED
        // SENÃO
        //      checkSemantic => expr
        // return ret
        break;

    case AST_CMDFUNCCALL:
        // TESTA já_declarado_aqui
        // SE não
        //      ret = ERR_UNDECLARED
        // SENÃO
        //      conta parametros
        //          checkParams
        // return ret
        break;

    case AST_CMDIN:
        // checkSemantic folhas => expr
        // SE folhas OP != (unario || binario || terario)
        // ret = ERR_WRONG_PAR_INPUT
        break;

    case AST_CMDIN:
        // checkSemantic folhas => expr
        // SE folhas != literal ou expr
        // ret = ERR_WRONG_PAR_OUTPUT
        break;

    case AST_CMDRBC:
        // SE RETURN
        // checkSemantic folhas => expr
        // SE folhas OP != (unario || binario || terario)
        // ret = ERR_WRONG_PAR_RETURN
        break;

    case AST_FOREACH:
        // checkSemantic TK_ID is vector
        child = listGet(node->leafs, 3);
        // hash_search child
        //  ret = is vector(TK_ID) ? 0 : ERR_VECTOR
        break;

    case AST_BLOCO:
        // checkSemantic ALL ListComandos
        break;

    case AST_VARIABLE:
        // TESTA já_declarado_aqui
        // SE não
        //      ret = ERR_UNDECLARED
        // SENÃO
        //      checkSemantic folhas
        // return ret
        break;

        //SUB CASE VARIABLE
    case AST_VARIABLEINDEX:
        // TESTA já_declarado_aqui
        // SE não
        //      ret = ERR_UNDECLARED
        // SENÃO
        //      checkSemantic index
        //      checkSemantic folhas
        // return ret
        break;
    case AST_VARIABLEATTRIBUTE:
        // TESTA já_declarado_aqui
        // SE não
        //      ret = ERR_UNDECLARED
        // SENÃO
        //      checkSemantic folhas
        // return ret
        break;
        // --

    case AST_UNARIO:
        // checkSemantic folha
        // checkType folha
        //      OK  => setType
        //      NOK => ERR_WRONG_TYPE
        break;

    case AST_BINARIO:
        // R op L
        // checkSemantic folha_R
        // checkSemantic folha_L
        // checkType folhas
        //      OK  => setType (convert implicito)
        //      NOK => ERR_WRONG_TYPE
        break;

    case AST_TERNARIO:
        // B ? Y : N
        // checkSemantic folha_B
        // checkSemantic folha_Y
        // checkSemantic folha_N
        // checkType folhas
        //      OK  => setType (convert implicito)
        //      NOK => ERR_WRONG_TYPE
        break;

    case AST_LITERAL:
        // já teve tipo atribuido no getlexico (scanner)
        break;

    default:
        fprintf(stderr, "[ERROR] Node Type: %d", node->type);
        break;
    } 
    */
}
