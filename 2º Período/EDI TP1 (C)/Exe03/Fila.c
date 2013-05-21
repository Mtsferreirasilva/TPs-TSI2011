#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

fila cria_fila()
{
    fila f;
    f=(fila)malloc(sizeof(tipo_fila));
    if (!f)
        return NULL;
    f->fim=NULL;
    f->inicio=NULL;
    f->tamanho=0;
    return f;
}

void termina_fila(fila *f)
{
    tipo_nodo *a;
    while ((*f)->inicio)
    {
        a=(*f)->inicio;
        (*f)->inicio = (*f)->inicio->prox;
        free(a);
    }
    (*f)->tamanho=0;
    (*f)->fim=NULL;
}
int fila_cheia(fila f)
{
    tipo_nodo *a;
    a=(tipo_nodo*)malloc(sizeof(tipo_nodo));
    if (!a)
        return 1;
    free(a);
    return 0;
}
int fila_vazia(fila f)
{
    return f->inicio==NULL;
}
int enfileira(fila f, tipo_item e)
{
    tipo_nodo *a;
    a=(tipo_nodo*)malloc(sizeof(tipo_nodo));
    if (!a)
        return 0;
    a->item=e;
    a->prox=NULL;
    if (!f->inicio)
        f->inicio=a;
    else
        f->fim->prox=a;
    f->fim=a;
    f->tamanho++;
    return 1;
}
int desenfileira(fila f, tipo_item *e)
{
    tipo_nodo *a;
    if (!f->inicio)
        return 0;
    a=f->inicio;
    *e=a->item;
    f->inicio=f->inicio->prox;
    f->tamanho--;
    free(a);
    return 0;
}

int imprime(fila f)
{
    tipo_nodo *a=f->inicio;
    do
    {
        printf("ID %d",a->item.id);
        a=a->prox;
    }while(a);

    return 1;
}
