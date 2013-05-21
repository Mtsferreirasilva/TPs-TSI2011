#ifndef LISTA_INVERTIDA_H_INCLUDED
#define LISTA_INVERTIDA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_NOME_ARQUIVO 255

//---------LISTA INVERTIDA-------------------------------

typedef struct
{
	int indiceArquivo;
	int ocorrencias;
	/*outros elementos*/
} tipo_elemento_lista;

typedef struct nodo_lista
{
	tipo_elemento_lista info_lista;
	struct nodo_lista *prox;
} tipo_nodo_lista;

typedef struct
{
	tipo_nodo_lista *inicio/*,*fim*/;
	int tamanhoLista;
} tipo_lista;

typedef tipo_lista *lista;


//--------------------------------------------------------

lista cria_lista(); // Cria a lista

int insere_lista (lista l, tipo_elemento_lista e); // insere na lista invertida

int termina_lista (lista *l); // termina lista

void aumentaOcorrencia(lista l,int indice); // incrementa ocorrencia de palavra caso encontrada

int imprimirConteudoLista (lista l); // Imprime o conteudo da lista como resultado na tela

int procuraIndiceArquivoLista (lista l, int ch); // Faz uma pesquisa por indice na lista

void imprimeLista(lista l,FILE *arq); // Imprime o conteudo da lista no arquivo de lista invertida

#endif // LISTA_H_INCLUDED
