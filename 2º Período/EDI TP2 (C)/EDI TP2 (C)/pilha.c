#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

int cria_pilha (pilha *p) //cria pilha
{
    p->topo = NULL;
    p->tamanho = 0;
    return 1;
}

int push(pilha *p, tipo_item_pilha e) //coloca elemento no topo da pilha
{
    tipo_nodo *ant;
    ant=(tipo_nodo*)malloc(sizeof(tipo_nodo));
    if (!ant)
        return 0;
    ant->prox=p->topo;
    ant->item=e;
    p->topo=ant;
    p->tamanho++;
    return 1;
}

int pop(pilha *p, tipo_item_pilha *e) //retira elemento do topo da pilha
{
    tipo_nodo *ant;
    if (!(p->topo))
        return 0;
    ant=p->topo;
    p->topo=ant->prox;
    *e=ant->item;
    p->tamanho--;
    free(ant);
    return 1;
}

int tamanho_pilha(pilha p)
{
    return (p.tamanho);
}

int pilha_vazia(pilha p)
{
    return !(p.topo);
}

int pilha_cheia(pilha p)
{
    tipo_nodo *a = p.topo;
    a=(tipo_nodo*)malloc(sizeof(tipo_nodo));
    if (!a)
        return 1; //esta cheia
    free(a);
    return 0;
}

int termina(pilha *p)
{
    tipo_nodo *k,*a = p->topo;
    while(p->topo)
    {
       p->topo = a->prox;
       k = a;
       a = p->topo;
       free(k);
    }
    if(!p->topo)
        return 1;
    return 0;
}
