#include <stdio.h>
#include <stdlib.h>
#include "filaPrioridade.h"

fila cria_fila(int numeroRuns)
{
    fila f;
    f=(fila)malloc(sizeof(tipo_fila));
    if (!f)
        return NULL;
    f->tamanho=0;
    f->elemento = (tipo_nodo*)malloc(sizeof(tipo_nodo)*numeroRuns); //Alocando vetor dinamico de elementos com base nas runs
    return f;
}

void termina_fila(fila *f)
{
    (*f)->tamanho = 0;
    free((*f)->elemento); // Libera memoria alocada para os elementos
    free(*f); // Libera memoria alocada para a Fila.
}

int insere_fila(fila f, tipo_nodo nodo,int numeroRuns){

    int p;
    tipo_nodo aux;
    int indice;

    if(f->tamanho == numeroRuns){
        printf("\nFila cheira");
        return 0;
    }

    f->elemento[f->tamanho].chave = nodo.chave;
    f->elemento[f->tamanho].run = nodo.run;

    indice = f->tamanho;
    //Modificando as prioridades dos elementos
    f->elemento[indice].chave = nodo.chave;
    p = indice >> 1; // Divide o heap, indice

    while( indice > 0 && f->elemento[p].chave > f->elemento[indice].chave){
        aux = f->elemento[p];
        f->elemento[p] = f->elemento[indice];
        f->elemento[indice] = aux;

        indice = p;
        p = indice >> 1;
    }
    f->tamanho++; // Tamanho da fila
    //imprime_fila(f);
    return 1;
}

void imprime_fila(fila f){
    int i;
    printf("\n\nFila(%d): ",f->tamanho);
    for (i=0;i<f->tamanho;i++)
        printf("%d ",f->elemento[i].chave);
}


int fila_vazia(fila f)
{
    return f->tamanho;
}

void remove_fila(fila f,tipo_nodo *nodo){

    if (f->tamanho == 0) //se não tem elementos
        return;

 	(*nodo)=f->elemento[0]; // Pega elemento da primeira posição
 	f->elemento[0]=f->elemento[f->tamanho-1]; // Adiciona a primeira posição o ultimo item.
    f->tamanho--;

    reorganiza_heap(f,0);//Reorganizar todo o heap desde o inicio ( 0 )
}

void reorganiza_heap(fila f,int i){

    int esq = i << 1; // Divide o heap a esquerda com base na posição I
    int dir = (i << 1) + 1; // Divide o heap a direita com base na posição I
    int menorIndice;
    tipo_nodo aux;

    if (esq < f->tamanho && f->elemento[esq].chave < f->elemento[i].chave){
        menorIndice = esq;
    }
    else{
        menorIndice = i;
    }

    if (dir < f->tamanho && f->elemento[dir].chave < f->elemento[menorIndice].chave){
        menorIndice = dir;
    }

    if (menorIndice != i){

        aux = f->elemento[i];
        f->elemento[i] = f->elemento[menorIndice];
        f->elemento[menorIndice] = aux;

        reorganiza_heap(f,menorIndice);
    }
}

