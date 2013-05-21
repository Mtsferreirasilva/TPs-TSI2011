#ifndef ARVORE_BINARIA
#define ARVORE_BINARIA

#include "lista_invertida.h"

//#include "lista_invertida.h"

#define TAMANHO_PALAVRA 50

/*
    -- ARVORE COM INSERÇÃO EM LISTA INVERTIDA --
*/

typedef char tipo_chave;
typedef struct
{
    tipo_chave palavraArvore[TAMANHO_PALAVRA];
}tipo_elemento;

typedef struct nodo
{
    lista listaInvertida;
    tipo_elemento info;
    struct nodo *esq, *dir;
}tipo_nodo;

typedef tipo_nodo *apontador;

//-------------------------------------------------

apontador inicializa(); // Inicializa arvore

void termina_arvore_binaria(apontador *p); // Termina arvore

int insere(apontador *p, tipo_elemento e,int doc_id); // Insere na arvore e em uma lista a ocorrencia da palavra

int pesquisaArvore(apontador p,tipo_chave palavra[TAMANHO_PALAVRA]); // Faz pesquisa na arvore por palavra

void imprimeArvore(apontador p,FILE *arq); // Imprime a partir da arvore a lista invertida


#endif // ARVORE_BINARIA
