#include "Fila.h"
#include <stdio.h>

fila cria_fila()
{
    fila f = (fila)malloc(sizeof(fila));
    if(!f)
    {
        return 0;
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}
void termina_fila(fila *f)
{
    tipo_nodo *a;
    while(!(*f)->inicio)
    {
        a = (*f)->inicio;
        (*f)->inicio = (*f)->inicio->prox;
        free(a);
    }
    (*f)->fim = NULL;
}
int fila_cheia(fila f)
{
    tipo_nodo *a;
    a = (tipo_nodo*)malloc(sizeof(tipo_nodo));
    if(!a)
        return 1;
    free(a);
    return 0;
}
int fila_vazia(fila f)
{
    return f->inicio == NULL;
}
int enfileira(fila f,tipo_item e)
{
    tipo_nodo *a;
    a = (tipo_nodo*)malloc(sizeof(tipo_nodo));
    if(!a)
        return 0;
    a->item = e;
    a->prox = NULL;
    if(!f->inicio)
        f->inicio = a;
    f->fim->prox = a;
    f->fim = a;
    f->tamanho++;
    return 1;
}
int desenfileira(fila f,tipo_item *e)
{
    tipo_nodo *a;
    if(fila_vazia(f))
        return 0;
    a = f->inicio;
    f->inicio = f->inicio->prox;
    *e = a->item;
    f->tamanho--;
    free(a);
    return 1;
}

