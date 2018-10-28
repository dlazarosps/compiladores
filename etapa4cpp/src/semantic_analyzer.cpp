/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <map>
#include <string>
#include <stack>
#include "../include/semantic_analyzer.h"
#include "../include/ast.h"
#include "../include/scope_stack.h"
#include "../include/symbol_table.h"

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
    this->lineError = (rowNumber > 0) ? "[ERRO] on line " + to_string(rowNumber) + " : " + rowText : "";
}

void SemanticAnalyzer::SetLineError(AbstractSyntaxTree node)
{
    int rowNumber;
    string rowText;
    LexicalValue* lex;

    lex = node->GetLexicalValue();

    rowNumber = lex->GetLine();
    //rowText = node->Descompilation(); //TODO get 1 row text

    this->SetLineError(rowNumber, rowText);
}

SemanticAnalyzer *SemanticAnalyzer::CheckSemantic(AbstractSyntaxTree *node)
{
    //TODO: convert C++
    //TODO: translate pseudo codes

    int leafSize;
    int idType;
    int idSize;
    string idName;

    AbstractSyntaxTree *child;
    LexicalValue *lex;
    SymbolTable *scope;
    SymbolTableEntry* entry;
    SemanticAnalyzer* result, temp;

    //pega quantidade de folhas
    leafSize = node->GetLeafsSize() - 1; // 0 to N

    //para cada tipo de construção gramatical aplica atribuição de tipo e tamanho e insere na stack hash
    switch (node->GetType())
    {

        case AST_PROGRAMA:
            //TODO
            //inicializada hash
            //push stack
            break;
        case AST_DECGLOBAL:
            //decglobal = id ... tipo ';'
            //pega identificador
            idName = node->GetNodeLeaf(0)->GetLexicalValue()->GetValue();

            entry = scope->LookUp(idName);
            if(entry !=  NULL){
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            } 
            else{
                // pega tipo
                idType = node->GetNodeLeaf((leafSize - 1))->GetLexicalValue()->GetValueType();

                // *setSize is_vector => leafsize (6 || 7) => listget(node->leafs, 3) => size * literal
                idSize = (leafSize >= 6) ? node->GetNodeLeaf(2)->GetLexicalValue()->GetValue() : 1;

                // adiciona na hash_stack {nome, tipo, tamanho, natureza}
                entry = SymbolTableEntry(idName, idType, idSize, NATUREZA_GLOBAL);
                scope->Insert(entry);
                
                // ret = 0
                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;
            break;

        case AST_DECTIPO:
            //pega identificador
            idName = node->GetNodeLeaf(1)->GetLexicalValue()->GetValue();

            entry = scope->LookUp(idName);
            if (entry != NULL)
            {
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                idType = TIPO_USER;
                //TODO conta_campos => "AST_listTipo" => listget(nodo->leafs, 4) => setSize
                //idSize = conta_campos SIZE

                entry = SymbolTableEntry(idName, idType, idSize, NATUREZA_TIPO);
                scope->Insert(entry);

                // ret = 0
                this->SetErrorNumber(0);
                this->SetLineError(0, "");

            }
                return this;
            break;

        case AST_DECFUN:
            // cria escopo 
            scope = SymbolTable();
            //TODO push_hash_stack

            // checkSemantic folhas
            result->CheckSemantic(node->GetNodeLeaf(0)); //check cabecalho
            if(result->GetErrorNumber() != 0){
                return result; //erro no cabecalho
            }
            else
            {
                temp->CheckSemantic(node->GetNodeLeaf(1)); //check corpo
                if(temp->GetErrorNumber() != 0) return temp; //erro no corpo

                //TODO pop context 
                // ret = 0
                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }

            break;

        case AST_CABECALHOFUN:
            // pop escopo (hash da função)
            //pega identificador
            idName = node->GetNodeLeaf((leafSize - 1))->GetLexicalValue()->GetValue();

            entry = scope->LookUp(idName);
            if (entry != NULL)
            {
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                //      conta_argumentos => "AST_listfun" => listget(nodo->leafs, leafSize) => add hash
                //      push hash
                //      checkSemantic argumentos ? AST_listfun => "PARAMSFUN" => PARAMS (add hash)

                entry = SymbolTableEntry(idName, idType, idSize, NATUREZA_TIPO);
                scope->Insert(entry);
                //      return ret
            }
            break;

        case AST_PARAMS:
            //TODO check TK_ID params
            idName = node->GetNodeLeaf((leafSize))->GetLexicalValue()->GetValue();

            entry = scope->LookUp(idName);
            if (entry != NULL)
            {
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                // pega tipo
                idType = node->GetNodeLeaf(leafSize -1)->GetLexicalValue()->GetValueType();

                // pega tamanho
                idSize = 1;

                entry = SymbolTableEntry(idName, idType, idSize, NATUREZA_FUN);
                scope->Insert(entry);

                // ret = 0
                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            
            break;

        case AST_DECVAR:
            // TESTA já_declarado_aqui (hash scopo corrente)
            // SE sim
            //      ret = ERR_DECLARED
            // SENÃO
            //      pega tipo
            // child = listGet(node->leafs, 1);
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
            // child = listGet(node->leafs, 3);
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
            cerr << "[ERROR] Node Type:" << node->GetType() << "\n";
            break;
    }
    return NULL;
}
