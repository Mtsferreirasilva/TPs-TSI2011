#ifndef ESTRUTURA_DE_ORDENACAO
#define ESTRUTURA_DE_ORDENACAO

#include "pilha.h"

typedef int tipo_chave;

typedef struct{
    tipo_chave chave;
    char endereco[100];
}tipo_item;

typedef tipo_item *item;

void bubbleSort(tipo_item *v, int tamanho);

void selectSort(tipo_item *v, int tamanho);

void insertSort(tipo_item *v, int tamanho);

void shellSort(tipo_item *v, int tamanho);

void heapSort(tipo_item *v, int tamanho);

void constroi(tipo_item *v, int posicao, int fim);

void quickSort(tipo_item *v, int tamanho);

void particao(tipo_item *v, int esq, int dir);

void quickSortInvertido(tipo_item *v, int tamanho);

void particaoInvertida(tipo_item *v, int esq, int dir);

void quickSortNum3(tipo_item *v, int tamanho);

void particaoNum3(tipo_item *v, int esq, int dir);

void quickSortInsert(tipo_item *v, int tamanho);

void particaoInsert(tipo_item *v, int esq, int dir);

void insertSortLimitado(tipo_item *v, int esq, int dir);

void QuickSortNaoRec(tipo_item *v, int tamanho);

void ParticaoNaoRec(tipo_item *v,int Esq, int Dir,int *i, int *j);

#endif

