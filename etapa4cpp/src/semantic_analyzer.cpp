/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
#include <iostream>
#include <cstdlib>
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

void SemanticAnalyzer::SetErrorNumber(int Err)
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

void SemanticAnalyzer::SetLineError(AbstractSyntaxTree *node)
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
    //TODO: translate pseudo codes

    int leafSize;
    int idType;
    int idSize;
    string idName;

    //AbstractSyntaxTree *child;
    //LexicalValue *lex;
    SymbolTable *scope;
    SymbolTableEntry *entry;
    SemanticAnalyzer *result, *temp, *temp2;

    //pega quantidade de folhas
    leafSize = node->GetLeafsSize() - 1; // 0 to N

    //para cada tipo de construção gramatical aplica atribuição de tipo e tamanho e insere na stack hash
    switch (node->GetType())
    {

        case AST_PROGRAMA:
            //TODO
            scope = new SymbolTable();
            //push stack
            break;
        case AST_DECGLOBAL:
            //decglobal = id ... tipo ';'
            idName = node->GetNodeLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador

            entry = scope->LookUp(idName);
            if(entry !=  NULL){
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            } 
            else{
                // pega tipo
                idType = node->GetNodeLeaf((leafSize - 1))->GetLexicalValue()->GetValueType();

                // *setSize is_vector => leafsize (6 || 7) => listget(node->leafs, 3) => size * literal
                idSize = (leafSize >= 6) ? stoi(node->GetNodeLeaf(2)->GetLexicalValue()->ValueToString()) : 1;

                // adiciona na hash_stack {nome, tipo, tamanho, natureza}
                entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_GLOBAL);
                scope->Insert(entry);
                
                // ret = 0
                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;
            break;

        case AST_DECTIPO:
            idName = node->GetNodeLeaf(1)->GetLexicalValue()->ValueToString(); //pega identificador

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
                idSize = 1;
                entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_TIPO);
                scope->Insert(entry);

                this->SetErrorNumber(0);
                this->SetLineError(0, "");

            }
                return this;
            break;

        case AST_DECFUNC:
            // cria escopo 
            scope = new SymbolTable();
            //TODO push_hash_stack

            // checkSemantic folhas
            result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(0)); //check cabecalho
            if(result->GetErrorNumber() != 0){
                return result; //erro no cabecalho
            }
            else
            {
                temp = new SemanticAnalyzer();
                temp->CheckSemantic(node->GetNodeLeaf(1)); //check corpo
                if(temp->GetErrorNumber() != 0) return temp; //erro no corpo

                //TODO pop context 

                this->SetErrorNumber(0);
                this->SetLineError(0, "");
                return this;
            }
            break;

        case AST_CABECALHOFUN:
            // pop escopo (hash da função)
            idName = node->GetNodeLeaf((leafSize - 1))->GetLexicalValue()->ValueToString(); //pega identificador

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
                idType = TIPO_IDENTIFICADOR;
                idSize = 1;

                entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_FUN);
                scope->Insert(entry);

                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;
            break;

        case AST_PARAMS:
            //TODO check TK_ID params
            idName = node->GetNodeLeaf((leafSize))->GetLexicalValue()->ValueToString();

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

                entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_FUN);
                scope->Insert(entry);

                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;
            break;

        case AST_DECVAR:
            idName = node->GetNodeLeaf(1)->GetLexicalValue()->ValueToString(); //pega identificador

            entry = scope->LookUp(idName);
            if (entry != NULL)
            {
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                idType = node->GetNodeLeaf(0)->GetLexicalValue()->GetValueType();
                if(idType == TIPO_USER) //TODO set TIPO_USER in lexvalue
                {
                    //SE tipo usuario  => já_declarado_aqui
                    entry = scope->LookUp(node->GetNodeLeaf(0)->GetLexicalValue()->ValueToString());
                    //SE inicializado ? conferir tipo
                    if (entry == NULL)
                    {
                        this->SetErrorNumber(ERR_UNDECLARED);
                        this->SetLineError(node); //preenche string de retorno com a linha que contem erro
                    }
                    //idSize = sizeUser
                }
                //adiciona na hash_stack {natureza, setType, setSize}
                idSize = 1;

                entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_VAR);
                scope->Insert(entry);

                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }   
            return this;
            break;

        case AST_CMDATR:
            idName = node->GetNodeLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador

            entry = scope->LookUp(idName);
            if (entry == NULL)
            {
                this->SetErrorNumber(ERR_UNDECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                //testa semantica da expr
                result = new SemanticAnalyzer();
                result->CheckSemantic(node->GetNodeLeaf(2));
                if (result->GetErrorNumber() != 0)
                {
                    return result; //erro no expr
                }
                else
                {
                    idSize = 1;
                    idType = 1; //TODO get type from hash COMPARE type from expr

                    entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_FUN);
                    scope->Insert(entry);

                    this->SetErrorNumber(0);
                    this->SetLineError(0, "");
                }
            }
            return this;
            break;

        case AST_CMDFUNCCALL:
            idName = node->GetNodeLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador

            entry = scope->LookUp(idName);
            if (entry == NULL)
            {
                this->SetErrorNumber(ERR_UNDECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                // conta parametros
                // checkParams
                // return ret
            }
            return this;
            break;

        case AST_CMDIN:
            // checkSemantic folhas => expr
            result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(1));
            if (result->GetErrorNumber() != 0)
            {   
                return result; //erro no expr
            }
            else
            {
                //TODO check specs E4
                // SE folhas OP != (unario || binario || terario)
                // ret = ERR_WRONG_PAR_INPUT
            }    
            break;

        case AST_CMDOUT:
            // checkSemantic folhas => expr
            result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(1));
            if (result->GetErrorNumber() != 0)
            {
                return result; //erro no expr
            }
            else
            {
                //TODO check specs E4
                // SE folhas != literal ou expr
                // ret = ERR_WRONG_PAR_OUTPUT
            }
            break;

        case AST_RBC:
            idName = node->GetNodeLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador
            //testa se é RETURN
            if(idName == "return")
            {
                // checkSemantic folhas => expr
                result = new SemanticAnalyzer();
                result->CheckSemantic(node->GetNodeLeaf(1));
                if (result->GetErrorNumber() != 0)
                {
                    return result; //erro no expr
                }
                else
                {
                    // SE folhas OP != (unario || binario || terario)
                    // ret = ERR_WRONG_PAR_RETURN
                }
            } //CASO CONTRARIO não tem validação semantica
            else
            {
                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;
            break;

        case AST_FOREACH:
            idName = node->GetNodeLeaf(2)->GetLexicalValue()->ValueToString(); //pega identificador

            entry = scope->LookUp(idName);
            if (entry == NULL)
            {
                this->SetErrorNumber(ERR_UNDECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                // checkSemantic TK_ID is vector
                //  ret = is vector(TK_ID) ? 0 : ERR_VECTOR
                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;
            break;

        case AST_BLOCO:
            // checkSemantic ALL ListComandos
            result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(1));
            return result;
            break;

        case AST_VARIABLE:
            idName = node->GetNodeLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador

            entry = scope->LookUp(idName);
            if (entry == NULL)
            {
                this->SetErrorNumber(ERR_UNDECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                // checkSemantic folhas
                result = new SemanticAnalyzer();
                result->CheckSemantic(node->GetNodeLeaf(1)); //check index
                if (result->GetErrorNumber() != 0)
                {
                    return result; //erro no index
                }
                else
                {
                    temp = new SemanticAnalyzer();
                    temp->CheckSemantic(node->GetNodeLeaf(2)); //check atribute
                    if (temp->GetErrorNumber() != 0) return temp; //erro no atribute
                    this->SetErrorNumber(0);
                    this->SetLineError(0, "");
                }
            }
            return this;
            break;

        case AST_VARIABLEINDEX:
            result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(1));
            return result;
            break;

        case AST_VARIABLEATTRIBUTE:
            idName = node->GetNodeLeaf(1)->GetLexicalValue()->ValueToString(); //pega identificador
            entry = scope->LookUp(idName);
            if (entry == NULL)
            {
                this->SetErrorNumber(ERR_UNDECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;
            break;

        case AST_UNARIO:
            result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(1));
            if (result->GetErrorNumber() != 0)
            {
                return result; //erro no expr
            }
            else
            {
                // OK  => setType
                // NOK => ERR_WRONG_TYPE
            }
            return this;
            break;

        case AST_BINARIO:
            // R op L
            result = new SemanticAnalyzer();
            temp = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(0));    // checkSemantic folha_L
            temp->CheckSemantic(node->GetNodeLeaf(2));      // checkSemantic folha_R
            if (result->GetErrorNumber() != 0)
            {
                return result; //erro no expr
            }
            else if (temp->GetErrorNumber() != 0)
            {
                return temp; //erro no expr
            }
            else
            {
                // checkType folhas
                //      OK  => setType (convert implicito)
                //      NOK => ERR_WRONG_TYPE
            }
            return this;
            break;

        case AST_TERNARIO:
            // B ? Y : N
            result = new SemanticAnalyzer();
            temp = new SemanticAnalyzer();
            temp2 = new SemanticAnalyzer();
            result->CheckSemantic(node->GetNodeLeaf(0)); // checkSemantic folha_B
            temp->CheckSemantic(node->GetNodeLeaf(2));   // checkSemantic folha_Y
            temp2->CheckSemantic(node->GetNodeLeaf(4));  // checkSemantic folha_N
            if (result->GetErrorNumber() != 0)
            {
                return result; //erro no expr
            }
            else if (temp->GetErrorNumber() != 0)
            {
                return temp; //erro no expr
            }
            else if (temp2->GetErrorNumber() != 0)
            {
                return temp2; //erro no expr
            }
            else
            {
                // checkType folhas
                //      OK  => setType (convert implicito)
                //      NOK => ERR_WRONG_TYPE
            }
            return this;
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
