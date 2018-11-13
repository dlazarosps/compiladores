/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <stack>
#include "../include/semantic_analyzer.h"
#include "../include/semantic_error.h"
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

void SemanticAnalyzer::AddError(SemanticError* error)
{
    this->errors.push_back(error);
}

void SemanticAnalyzer::ClearErrors()
{
    // TODO: clean up
    this->errors.clear();
}

int SemanticAnalyzer::GetNumberOfErrors()
{
    return this->errors.size();
}

SemanticError* SemanticAnalyzer::GetError(int index)
{
    return this->errors.at(index);
}

SemanticError* SemanticAnalyzer::GetFirstError()
{
    if(this->GetNumberOfErrors() > 0)
        return this->errors.at(0);
    else
        return NULL;
}

bool SemanticAnalyzer::Analyze()
{
    // Initialize variables
    this->scopeStack = new ScopeStack();
    this->ClearErrors();
    bool ret;

    // Begin algorithm
    ret = this->AnalyzeNode(this->root);

    // Clean up
    //delete this->scopeStack;
    //this->scopeStack = NULL;

    // Return true if ok, return false if it has errors
    return ret;
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
        case AST_DECFUNC:
            return this->AnalyzeAstDecFunc(node);
            break;
        case AST_CABECALHOFUN:
            return this->AnalyzeAstCabecalhoFun(node);
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
        case AST_BLOCO:
            return this->AnalyzeNode(node->GetLeaf(1));
            break;
        case AST_LISTACOMANDOS:
            return this->AnalyzeAstListaComandos(node);
            break;
        case AST_CORPOFUN:
        case AST_CMDSTERMINADOSPONTOVIRGULA:
            return this->AnalyzeNode(node->GetLeaf(0));
            break;
        case AST_CMDSTERMINADOSDOISPONTOS:
            return this->AnalyzeNode(node->GetLeaf(0));
            break;
        case AST_CMDSIMPLESFOR:
        case AST_CMDBLOCO:
            return this->AnalyzeNode(node->GetLeaf(0));
            break;
        case AST_CMDDECVAR:
            return this->AnalyzeNode(node->GetLeaf(0));
            break;
        case AST_DECVAR:
            return this->AnalyzeAstDecVar(node);
            break;
        case AST_CMDATR:
            return this->AnalyzeAstCmdAtr(node);
            break;
        case AST_CMDFUNCCALL:
            return this->AnalyzeAstCmdFunCall(node);
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

    SymbolTable* table = new SymbolTable();
    this->scopeStack->push(table);
    this->globalScope = table;
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
    // decglobal = TK_IDENTIFICADOR tipo ';'

    string idName = node->GetLeaf(0)->GetLexicalValue()->ValueToString(); // Pega identificador
    int line = node->GetLeaf(0)->GetLexicalValue()->GetLine();

    SymbolTable *top = this->scopeStack->Top();

    // Procura no escopo
    if(top->LookUp(idName) !=  NULL) {
        this->AddError(new SemanticError(ERR_DECLARED, line));
        return false;
    }
    else {
        // adiciona no escopo {nome, tipo, tamanho, natureza}
        top->Insert(new SymbolTableEntry(idName, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_GLOBAL, top->GetSize()*QUATRO_BYTE));
        return true;
    }
}

bool SemanticAnalyzer::AnalyzeAstDecFunc(AbstractSyntaxTree *node)
{
    // decFunc: cabecalhoFun corpoFun
    // corpoFun: bloco

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
    // cabecalhoFun: TK_PR_STATIC tipo TK_IDENTIFICADOR listaFun
    // cabecalhoFun: tipo TK_IDENTIFICADOR listaFun
    // cabecalhoFun: TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun
    // cabecalhoFun: TK_IDENTIFICADOR TK_IDENTIFICADOR listaFun

    string idName = node->GetLeaf(1)->GetLexicalValue()->ValueToString(); // Pega identificador
    int line = node->GetLeaf(1)->GetLexicalValue()->GetLine();
    SymbolTableEntry* entry;
    SymbolTable* table;

    SymbolTable *top = this->scopeStack->Top();

    if (top->LookUp(idName) != NULL)
    {
        this->AddError(new SemanticError(ERR_DECLARED, line));
        return false;
    }
    else
    {
        entry = new SymbolTableEntry(idName, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_FUN, top->GetSize()*QUATRO_BYTE);
        top->Insert(entry); // Adiciona função ao escopo
        table = new SymbolTable();
        this->scopeStack->push(table); // Cria novo escopo para a função
        entry->setAssociatedSymbolTable(table);
        this->GetDecFuncParams(node->GetLeaf(2));
        return true;
    }
}

bool SemanticAnalyzer::GetDecFuncParams(AbstractSyntaxTree *node)
{
    // listaFun: '(' paramsFun ')'
    // listaFun: '(' ')'
    // paramsFun: params
    // paramsFun: paramsFun ',' params
    // params: TK_PR_CONST tipo TK_IDENTIFICADOR
    // params: tipo TK_IDENTIFICADOR

    string idName;
    int line;
    SymbolTable *top;

    switch(node->GetType())
    {
        case AST_LISTAFUN:
            if(node->GetLeafsSize() == 3) {
                return this->GetDecFuncParams(node->GetLeaf(1));
            }
            else {
                return true;
            }
            break;
        case AST_PARAMSFUN:
            if(node->GetLeafsSize() == 3) {
                return this->GetDecFuncParams(node->GetLeaf(0)) && this->GetDecFuncParams(node->GetLeaf(2));
            }
            else {
                return this->GetDecFuncParams(node->GetLeaf(0));
            }
            break;
        case AST_PARAMS:
            idName = node->GetLeaf(1)->GetLexicalValue()->ValueToString(); // Pega identificador
            line = node->GetLeaf(1)->GetLexicalValue()->GetLine();
            top = this->scopeStack->Top();
            if (top->LookUp(idName) != NULL)
            {
                this->AddError(new SemanticError(ERR_DECLARED, line));
                return false;
            }
            else
            {
                top->Insert(new SymbolTableEntry(idName, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_VAR, top->GetSize()*QUATRO_BYTE));
                return true;
            }
            break;
        default:
            return false;
            break;
    }

    return false;
}

bool SemanticAnalyzer::AnalyzeAstListaComandos(AbstractSyntaxTree *node)
{
    //  listaComandos cmdsTerminadosPontoVirgula ';'
    //  listaComandos cmdsTerminadosDoisPontos ':'
    //  %empty

    int leafSize = node->GetLeafsSize(); // Pega a quantidade de nodos filhos
    if(leafSize >= 2)
    {
        return (this->AnalyzeNode(node->GetLeaf(0)) && this->AnalyzeNode(node->GetLeaf(1)));
    }
    return true;
}


bool SemanticAnalyzer::AnalyzeAstDecVar(AbstractSyntaxTree *node)
{
    //  tipoSimples TK_IDENTIFICADOR
    //  tipoSimples TK_IDENTIFICADOR TK_OC_LE variable
    //  tipoSimples TK_IDENTIFICADOR TK_OC_LE literal
    //  TK_IDENTIFICADOR TK_IDENTIFICADOR

    string idName = node->GetLeaf(1)->GetLexicalValue()->ValueToString(); //pega identificador
    int line = node->GetLeaf(1)->GetLexicalValue()->GetLine();

    SymbolTable *top = this->scopeStack->Top();

    if (top->LookUp(idName) != NULL)
    {
        this->AddError(new SemanticError(ERR_DECLARED, line));
        return false;
    }
    else
    {
        top->Insert(new SymbolTableEntry(idName, SYMBOL_TYPE_INT, QUATRO_BYTE, NATUREZA_VAR, top->GetSize()*QUATRO_BYTE));
        return true;
    }
}

bool SemanticAnalyzer::AnalyzeAstCmdAtr(AbstractSyntaxTree *node)
{
    // cmdAtr: variable '=' expr
    // variable: TK_IDENTIFICADOR variableIndex variableAttribute

    /*
    string idName = node->GetLeaf(0)->GetLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador
    int line = node->GetLeaf(0)->GetLexicalValue()->GetLine();

    if (this->scopeStack->LookUp(idName) == NULL)
    {
        this->AddError(new SemanticError(ERR_UNDECLARED, line));
        return false;
    }
    else
    {
        //testa semantica da expr
        return this->AnalyzeNode(node->GetLeaf(2));
    }
    */
    return true;
}

bool SemanticAnalyzer::AnalyzeAstCmdFunCall(AbstractSyntaxTree *node)
{
    /*
    bool ret = true;
    string idName = node->GetLeaf(0)->GetLexicalValue()->ValueToString(); //pega identificador
    int line = node->GetLeaf(0)->GetLexicalValue()->GetLine();
    SymbolTableEntry *entry = this->scopeStack->LookUp(idName);
    if (entry == NULL)
    {
        this->AddError(new SemanticError(ERR_UNDECLARED, line));
        return false;
    }
    else
    {
        // conta parametros
        // checkParams
        // return ret
    }
    return ret;
    */
    return true;
}

void SemanticAnalyzer::PrintScopes()
{
    cout << "Printando o escopo global: \n\n";
    this->globalScope->Print();
}

SymbolTable* SemanticAnalyzer::GetGlobalScope()
{
    return this->globalScope;
}
