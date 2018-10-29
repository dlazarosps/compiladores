/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <stack>
#include "../include/semantic_analyzer.h"
#include "../include/parser.tab.h"
#include "../include/ast.h"
#include "../include/scope_stack.h"
#include "../include/symbol_table.h"

using namespace std;

/*
 * SemanticAnalyzer functions
 */

SemanticAnalyzer::SemanticAnalyzer(AbstractSyntaxTree *root)
{
    this->root = root;
}

SemanticAnalyzer::~SemanticAnalyzer()
{
    // TODO: clean up
}

// TODO: get first error?
int SemanticAnalyzer::GetErrorNumber()
{
    return this->errorNumber;
}

// TODO: make a list of errors?
void SemanticAnalyzer::SetErrorNumber(int Err)
{
    this->errorNumber = Err;
}

// TODO: get first error?
string SemanticAnalyzer::GetLineError()
{
    return this->lineError;
}

// TODO: make a list of errors?
void SemanticAnalyzer::SetLineError(int rowNumber, string rowText)
{
    this->lineError = (rowNumber > 0) ? "[ERRO] on line " + to_string(rowNumber) + " : " + rowText : "";
}

// TODO: make a list of errors?
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

bool SemanticAnalyzer::Analyze()
{
    // Initialize variables
    this->scopeStack = new ScopeStack();

    // Begin algorithm
    this->AnalyzeNode(this->root);

    // Clean up
    delete this->scopeStack;
    this->scopeStack = NULL;

    // TODO: check if errors
    return true;
}

bool SemanticAnalyzer::AnalyzeNode(AbstractSyntaxTree *node)
{
    // Para cada tipo de construção gramatical aplica atribuição de tipo e tamanho e insere na stack hash
    switch (node->GetType())
    {
        case AST_PROGRAMA:
            return this->AnalyzeAstPrograma(node);
            break;
        case AST_ELEMENTO:
            return this->AnalyzeAstElemento(node);
            break;
        case AST_DECGLOBAL:
            return this->AnalyzeAstDecGlobal(node);
            break;
        case AST_DECTIPO:
            return this->AnalyzeAstDecTipo(node);
            break;
        case AST_DECFUNC:
            return AnalyzeAstDecFunc(node);
            break;
        case AST_CABECALHOFUN:
            return AnalyzeAstCabecalhoFun(node);
            break;
        case AST_PARAMS:
            //TODO check TK_ID params
            /*idName = node->GetLeaf((leafSize))->GetLexicalValue()->ValueToString();

            entry = scope->LookUp(idName);
            if (entry != NULL)
            {
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                // pega tipo
                idType = node->GetLeaf(leafSize -1)->GetLexicalValue()->GetValueType();

                // pega tamanho
                idSize = 1;

                entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_FUN);
                scope->Insert(entry);

                this->SetErrorNumber(0);
                this->SetLineError(0, "");
            }
            return this;*/
            break;

        case AST_DECVAR:
            /*idName = node->GetLeaf(1)->GetLexicalValue()->ValueToString(); //pega identificador

            entry = scope->LookUp(idName);
            if (entry != NULL)
            {
                this->SetErrorNumber(ERR_DECLARED);
                this->SetLineError(node); //preenche string de retorno com a linha que contem erro
            }
            else
            {
                idType = node->GetLeaf(0)->GetLexicalValue()->GetValueType();
                if(idType == TIPO_USER) //TODO set TIPO_USER in lexvalue
                {
                    //SE tipo usuario  => já_declarado_aqui
                    entry = scope->LookUp(node->GetLeaf(0)->GetLexicalValue()->ValueToString());
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
            return this;*/
            break;

        case AST_CMDATR:
            /*idName = node->GetLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador

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
                result->CheckSemantic(node->GetLeaf(2));
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
            return this;*/
            break;

        case AST_CMDFUNCCALL:
            /*idName = node->GetLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador

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
            return this;*/
            break;

        case AST_CMDIN:
            // checkSemantic folhas => expr
            /*result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetLeaf(1));
            if (result->GetErrorNumber() != 0)
            {
                return result; //erro no expr
            }
            else
            {
                //TODO check specs E4
                // SE folhas OP != (unario || binario || terario)
                // ret = ERR_WRONG_PAR_INPUT
            }*/
            break;

        case AST_CMDOUT:
            // checkSemantic folhas => expr
            /*result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetLeaf(1));
            if (result->GetErrorNumber() != 0)
            {
                return result; //erro no expr
            }
            else
            {
                //TODO check specs E4
                // SE folhas != literal ou expr
                // ret = ERR_WRONG_PAR_OUTPUT
            }*/
            break;

        case AST_RBC:
            /*idName = node->GetLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador
            //testa se é RETURN
            if(idName == "return")
            {
                // checkSemantic folhas => expr
                result = new SemanticAnalyzer();
                result->CheckSemantic(node->GetLeaf(1));
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
            return this;*/
            break;

        case AST_FOREACH:
            /*idName = node->GetLeaf(2)->GetLexicalValue()->ValueToString(); //pega identificador

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
            return this;*/
            break;

        case AST_BLOCO:
            /*// checkSemantic ALL ListComandos
            result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetLeaf(1));
            return result;*/
            break;

        case AST_VARIABLE:
            /*idName = node->GetLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador

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
                result->CheckSemantic(node->GetLeaf(1)); //check index
                if (result->GetErrorNumber() != 0)
                {
                    return result; //erro no index
                }
                else
                {
                    temp = new SemanticAnalyzer();
                    temp->CheckSemantic(node->GetLeaf(2)); //check atribute
                    if (temp->GetErrorNumber() != 0) return temp; //erro no atribute
                    this->SetErrorNumber(0);
                    this->SetLineError(0, "");
                }
            }
            return this;*/
            break;

        case AST_VARIABLEINDEX:
            /*result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetLeaf(1));
            return result;*/
            break;

        case AST_VARIABLEATTRIBUTE:
            /*idName = node->GetLeaf(1)->GetLexicalValue()->ValueToString(); //pega identificador
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
            return this;*/
            break;

        case AST_UNARIO:
            /*result = new SemanticAnalyzer();
            result->CheckSemantic(node->GetLeaf(1));
            if (result->GetErrorNumber() != 0)
            {
                return result; //erro no expr
            }
            else
            {
                // OK  => setType
                // NOK => ERR_WRONG_TYPE
            }
            return this;*/
            break;

        case AST_BINARIO:
            // R op L
            /*result = new SemanticAnalyzer();
            temp = new SemanticAnalyzer();
            result->CheckSemantic(node->GetLeaf(0));    // checkSemantic folha_L
            temp->CheckSemantic(node->GetLeaf(2));      // checkSemantic folha_R
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
            return this;*/
            break;

        case AST_TERNARIO:
            // B ? Y : N
            /*result = new SemanticAnalyzer();
            temp = new SemanticAnalyzer();
            temp2 = new SemanticAnalyzer();
            result->CheckSemantic(node->GetLeaf(0)); // checkSemantic folha_B
            temp->CheckSemantic(node->GetLeaf(2));   // checkSemantic folha_Y
            temp2->CheckSemantic(node->GetLeaf(4));  // checkSemantic folha_N
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
            return this;*/
            break;

        case AST_LITERAL:
            // já teve tipo atribuido no getlexico (scanner)
            break;

        default:
            cerr << "[ERROR] Node Type:" << node->GetType() << "\n";
            return false;
            break;
    }

    return false;
}

bool SemanticAnalyzer::AnalyzeAstPrograma(AbstractSyntaxTree *node)
{
    // programa: elemento
    // programa: %empty

    this->scopeStack->push(new SymbolTable());
    if(node->GetLeaf(0)->GetType() == AST_EMPTY) {
        return true;
    }
    else {
        return this->AnalyzeNode(node->GetLeaf(0));
    }
}

bool SemanticAnalyzer::AnalyzeAstElemento(AbstractSyntaxTree *node)
{
    // elemento: elemento decGlobal
    // elemento: decGlobal
    // elemento: elemento decTipo
    // elemento: decTipo
    // elemento: elemento decFunc
    // elemento: decFunc

    bool ret = true;
    int leafSize = node->GetLeafsSize(); // Pega a quantidade de nodos filhos
    for(int i = 0; i < leafSize; i++) {
        ret = ret && this->AnalyzeNode(node->GetLeaf(i));
    }
    return ret;
}

bool SemanticAnalyzer::AnalyzeAstDecGlobal(AbstractSyntaxTree *node)
{
    // decglobal = TK_IDENTIFICADOR TK_PR_STATIC tipo ';'
    // decglobal = TK_IDENTIFICADOR '[' TK_LIT_INT ']' TK_PR_STATIC tipo ';'
    // decglobal = TK_IDENTIFICADOR tipo ';'
    // decglobal = TK_IDENTIFICADOR '[' TK_LIT_INT ']' tipo ';'

    int leafSize = node->GetLeafsSize(); // Pega a quantidade de nodos filhos
    string idName = node->GetLeaf(0)->GetLexicalValue()->ValueToString(); // Pega identificador
    int idType;
    int idSize;

    SymbolTableEntry *entry = this->scopeStack->LookUp(idName); // Procura no escopo
    if(entry !=  NULL){
        this->SetErrorNumber(ERR_DECLARED);
        this->SetLineError(node); //preenche string de retorno com a linha que contem erro
        return false;
    }
    else{
        // pega tipo
        idType = this->GetTypeFromAstTipo(node->GetLeaf(leafSize - 2));

        // *setSize is_vector => leafsize (6 || 7) => listget(node->leafs, 3) => size * literal
        // TODO: verificar isto
        idSize = (leafSize >= 5) ? stoi(node->GetLeaf(2)->GetLexicalValue()->ValueToString()) : 1;

        // adiciona no escopo {nome, tipo, tamanho, natureza}
        entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_GLOBAL);
        this->scopeStack->Top()->Insert(entry);

        return true;
    }
}

bool SemanticAnalyzer::AnalyzeAstDecTipo(AbstractSyntaxTree *node)
{
    // decTipo = TK_PR_CLASS TK_IDENTIFICADOR '[' listaTipo ']' ';'
    // listaTipo: campoTipo
    // listaTipo: listaTipo ':' campoTipo
    // campoTipo: encaps tipoSimples TK_IDENTIFICADOR
    // campoTipo: tipoSimples TK_IDENTIFICADOR
    // encaps: TK_PR_PROTECTED
    // encaps: TK_PR_PRIVATE
    // encaps: TK_PR_PUBLIC

    string idName = node->GetLeaf(1)->GetLexicalValue()->ValueToString(); //pega identificador
    int idType;
    int idSize;

    SymbolTableEntry *entry = scope->LookUp(idName);
    if (entry != NULL)
    {
        this->SetErrorNumber(ERR_DECLARED);
        this->SetLineError(node); //preenche string de retorno com a linha que contem erro
        return false;
    }
    else
    {
        idType = TIPO_USER;
        //TODO conta_campos => "AST_listTipo" => listget(nodo->leafs, 4) => setSize
        //idSize = conta_campos SIZE
        idSize = 1;
        entry = new SymbolTableEntry(idName, idType, idSize, NATUREZA_TIPO);
        scope->Insert(entry);

        return true;
    }
}

bool SemanticAnalyzer::AnalyzeAstDecFunc(AbstractSyntaxTree *node)
{
    // decFunc: cabecalhoFun corpoFun
    // corpoFun: bloco

    this->scopeStack->push(new SymbolTable()); // Cria escopo

    AbstractSyntaxTree *nodeCabecalho = node->GetLeaf(0);
    AbstractSyntaxTree *nodeBloco = node->GetLeaf(1)->GetLeaf(0);

    bool ret = true;

    ret = ret && this->AnalyzeAstCabecalhoFun(nodeCabecalho);
    ret = ret && this->AnalyzeNode(nodeBloco);

    this->scopeStack->pop();

    return ret;
}

bool SemanticAnalyzer::AnalyzeAstCabecalhoFun(AbstractSyntaxTree *node)
{
    // cabecalhoFun: TK_PR_STATIC tipoSimples TK_IDENTIFICADOR listaFun
    // cabecalhoFun: tipo TK_IDENTIFICADOR listaFun
    // cabecalhoFun: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
    // cabecalhoFun: TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
    // listaFun: '(' paramsFun ')'
    // listaFun: '(' ')'
    // paramsFun: params
    // paramsFun: paramsFun ',' params
    // params: TK_PR_CONST tipo TK_IDENTIFICADOR
    // params: tipo TK_IDENTIFICADOR

    string idName = node->GetLeaf((leafSize - 1))->GetLexicalValue()->ValueToString(); //pega identificador

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
}

int SemanticAnalyzer::GetTypeFromAstTipo(AbstractSyntaxTree *node)
{
    LexicalValue *lex = node->GetLexicalValue();
    switch(node->GetType()) {
        case AST_TERMINAL:
            if(lex->GetType() == TIPO_LITERAL) {
                switch(lex->GetValueType()) {
                    case VALOR_STRING:
                        return SYMBOL_TYPE_STRING;
                        break;
                    case VALOR_CHAR:
                        return SYMBOL_TYPE_CHAR;
                        break;
                    case VALOR_INT:
                        return SYMBOL_TYPE_INT;
                        break;
                    case VALOR_FLOAT:
                        return SYMBOL_TYPE_FLOAT;
                        break;
                    case VALOR_BOOL:
                        return SYMBOL_TYPE_BOOL;
                        break;
                }
            }
            else {
                return SYMBOL_TYPE_USER;
            }
            break;
        case AST_TIPO:
        case AST_TIPOSIMPLES:
            return this->GetTypeFromAstTipo(node->GetLeaf(0));
            break;
        default:
            return -1; // TODO: throw error properly
            break;
    }
}

string SemanticAnalyzer::GetValueFromAstTipo(AbstractSyntaxTree *node)
{
    switch(node->GetType()) {
        case AST_TERMINAL:
            return node->GetLexicalValue()->ValueToString();
            break;
        case AST_TIPO:
        case AST_TIPOSIMPLES:
            return this->GetValueFromAstTipo(node->GetLeaf(0));
            break;
        default:
            return "ERRO"; // TODO: throw error properly
            break;
    }
}
