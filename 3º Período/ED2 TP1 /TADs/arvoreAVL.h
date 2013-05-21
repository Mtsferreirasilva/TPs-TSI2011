#ifndef ARVOREAVL_H_INCLUDED
#define ARVOREAVL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "lista_invertida.h"

#define TAMANHO_PALAVRA 50

//--------------ARVORE AVL----------------

typedef char tipo_chave_avl;

typedef struct {
	tipo_chave_avl chave[TAMANHO_PALAVRA];
	/* outros componentes*/
} tipo_elemento_avl;

typedef struct nodo_avl{
    tipo_elemento_avl info_avl;
    int fb;
    struct nodo_avl *esquerda, *direita;
    lista listaInvertida;
} tipo_nodo_avl;

typedef tipo_nodo_avl *avl_apontador;

//--------------------------------------

avl_apontador inicializaArvoreAVL(); //inicializa

int insereAVL (avl_apontador *ap,tipo_elemento_avl e,int indice); // insere na arvore AVL

int terminaArvoreAVL(avl_apontador *ap); // Libera memoria

int pesquisaArvoreAVL(avl_apontador p,tipo_chave_avl palavra[TAMANHO_PALAVRA]); // pesquisa palavra na arvore

//Coloca lista no arquivo txt
void imprimeArvoreAVL(avl_apontador p,FILE *arq);
void arquivaAVL(avl_apontador p);

#endif // ARVOREAVL_H_INCLUDED
