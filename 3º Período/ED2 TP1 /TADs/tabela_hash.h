#ifndef TABELA_HASH_H_INCLUDED
#define TABELA_HASH_H_INCLUDED

#include "arvore_binaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_HASH 900001 // Palavras na linha portuguesa = 600k +- logo 600k + 600k/2 = 900k
#define TAMANHO_PALAVRA 50
/*
    -- TABELA HASH COM INSERÇÃO EM ARVORE BINÁRIA --
*/
typedef apontador arvore;

typedef struct{
    arvore elementos[TAMANHO_HASH];
    int tamanho;
}tipo_tabela;

typedef tipo_tabela *tabela;

// ------------------------------------------
tabela cria_tabela(); // inicializa tabela

int termina_tabela(tabela *t); // termina tabela

int insere_tabela(tabela *t, char *palavra, int doc_id); // insere já enviando para a arvore

int stringParaInt(char *palavra); //tranforma palavra em codigo int

int hash(int valorInt); //gera HashCode com base no codigo String

int pesquisaHash(tabela t,char palavra[]); // faz uma pesquisa na tabela, procurando uma palavra

void arquivaTabela(tabela t); // Gera arquivo de lista invertida no diretorio principal

#endif // TABELA_HASH_H_INCLUDED
