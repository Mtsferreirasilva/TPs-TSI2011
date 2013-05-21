#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include<stdlib.h>
#include<stdio.h>
#include "lista_invertida.h"

#define M 2
#define MM  (M * 2)
#define FALSE 0
#define TRUE  1
#define TAMANHO_PALAVRA 50

//------------------ARVORE B----------------------------

typedef char TipoChave;

typedef struct TipoRegistro {
    TipoChave Chave[TAMANHO_PALAVRA];
    lista listaInvertida;
    /*outros componentes*/
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;


//------------------------------------------------------

void inicializaArvoreB(TipoApontador *Dicionario); // inicializa

TipoRegistro* Pesquisa(TipoRegistro palavra, TipoApontador Ap);// pesquisa palavra

void InsereNaPagina(TipoApontador Ap,TipoRegistro Reg, TipoApontador ApDir,tipo_elemento_lista e);

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu,TipoRegistro *RegRetorno,  TipoApontador *ApRetorno,tipo_elemento_lista e);

void InsereB(TipoRegistro Reg, TipoApontador *Ap, int indiceArquivo);

void imprimeConteudoB(TipoRegistro registro); //Imprime todo o conteudo presente no registro do arvore

// Coloca no arquivo a lista
void arquivaB(TipoApontador arvoreB, int nivel);
void arquivaB2(TipoApontador arvoreB, int nivel, FILE *arqLista);

#endif // ARVOREB_H_INCLUDED
