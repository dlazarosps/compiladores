/* ETAPA 4 - TRABALHO DE COMPILADORES - Grupo Rho */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "ast.h"
#include "list.h"
#include "valor_lexico.h"

/* void hashInit()
{
    int i;
    
    for(int i = 0; i < HASH_SIZE; i++){
        table[i] = NULL;
    }
    
} */

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

HASH hashInsert(char *texto, TValorLexico * lex)
{
    HASH *hash_node = malloc(sizeof(HASH));
    int index;
    
    // TODO check if exist => hashFind()
    index = hashIndex(texto);

    strcpy(hash_node->text, texto);
    hash_node->valor_lexico = lex;
    hash_node->next = table[index];
    table[index] = hash_node;

    return hash_node;
}