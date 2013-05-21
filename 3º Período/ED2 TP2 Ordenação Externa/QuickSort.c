#include "QuickSort.h"

void quickSort(int *v, int tamanho)
{
    particao(v,0,tamanho-1);
}

void particao(int *v, int esq, int dir)
{
    int i,k;
    int aux, pivo;
    pivo = v[(esq+dir)/2];
    i = esq;
    k = dir;
    do {
        while(v[i] < pivo)
            i++;
        while(v[k] > pivo)
            k--;
        if (i <= k)
        {
            aux = v[i];
            v[i] = v[k];
            v[k] = aux;
            i++;
            k--;
        }
    }while(i <= k);
    if (esq < k)
        particao(v,esq,k);
    if (i < dir)
        particao(v,i,dir);
}
