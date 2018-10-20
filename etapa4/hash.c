/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

void hashInit()
{
    int i;
    for(int i = 0; i < HASH_SIZE; i++){
        tabela_hash[i] = NULL;
    }
}

int hashIndex(char* id)
{
    int i;
    int index = 1;

    for(int i = 0; i < strlen(id); i++){
        index = (index * id[i]) % HASH_SIZE + 1;    //gera indice unico para cada identificador
                                                    //da para fazer usando shift com os bits
    }
    
    return index - 1;
}

HASH* hashFind(char *id)
{
    int index = hashIndex(id);
    HASH* hash_node = tabela_hash[index];
    
    while(hash_node != NULL){
        if(strcmp(id, hash_node->text) == 0) //compara texto 
            return hash_node; //retorna ponteiro
        else
            hash_node = hash_node->next; //avança para proximo encademento com mesmo index
    }
    
    return NULL; //não encontrado
}

HASH* hashInsert(char *texto, TValorLexico * lex)
{
    HASH *hash_node = malloc(sizeof(HASH));
    int index;
    
    // check if exist
    if((hash_node = hashFind(texto)) != NULL)
        return hash_node; //retorna ponteiro caso exista

    //create
    index = hashIndex(texto);

    strcpy(hash_node->text, texto);
    hash_node->valor_lexico = lex;
    hash_node->next = tabela_hash[index];
    tabela_hash[index] = hash_node;

    return hash_node;
}

void hashPrint()
{
    int i;
    HASH *hash_node;
    
    for(int i = 0; i < HASH_SIZE; i++){
        for(hash_node = tabela_hash[i]; hash_node; hash_node hash_node->next){
             fprintf(stdout, "tabela_hash [%d] = %s \n", i, hash_node->text);
        }   
    }    
}