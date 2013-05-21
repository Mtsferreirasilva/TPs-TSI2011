#include <stdio.h>
#include <stdlib.h>
#include "estruturas_de_ordenacao.h"


//BubbleSort-----------------------------------------------------
void bubbleSort(tipo_item *v, int tamanho)
{
	int i, ultima_troca, ultima_posicao;
	tipo_item aux;
	ultima_posicao=tamanho;
	do{
		ultima_troca = 0;
		for( i = 0 ; i < ultima_posicao-1 ; i++ )
			if (v[i].chave > v[i+1].chave)
			{
				aux = v[i];
				v[i] = v[i+1];
				v[i+1] = aux;
				ultima_troca = i+1;
			}
		ultima_posicao = ultima_troca;
	}while(ultima_posicao>0);
}

//SelectSort-----------------------------------------------------
void selectSort(tipo_item *v, int tamanho)
{
	int i, j, posicao_menor;
	tipo_item aux;
	for (i = 0; i < tamanho - 1; i++)
	{
		posicao_menor = i;
		for (j = i + 1 ; j < tamanho; j++)
		if ( v[j].chave < v[posicao_menor].chave)
			posicao_menor = j;
		aux = v[posicao_menor];
		v[posicao_menor] = v[i];
		v[i] = aux;
	}
}

//InsertSort-----------------------------------------------------
void insertSort(tipo_item *v, int tamanho)
{
	int i,j;
	tipo_item aux;
	for (i = 1; i < tamanho; i++)
	{
		aux = v[i];
		j = i - 1;
		while ( ( j >= 0 ) && ( aux.chave < v[j].chave ) )
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = aux;
	}
}

//ShellSort-----------------------------------------------------
void shellSort(tipo_item *v, int tamanho)
{
	int i, j;
	int h = 1;
	tipo_item aux;
	do
        h = h * 3 + 1;
	while (h < tamanho);
	do {
			h /= 3;
			for( i = h ; i < tamanho ; i++ )
			{
				aux = v[i];
				j = i;
				while (v[j-h].chave > aux.chave)
				{
					v[j] = v[j-h];
					j -= h;
					if (j < h)
						break;
				}
				v[j] = aux;
			}
	} while (h != 1);
}

//HeapSort-----------------------------------------------------
void heapSort(tipo_item *v, int tamanho)
{
     int i;
     tipo_item aux;

     //Construindo o Heap
     for(i = tamanho/2; i >= 0; i--)
        constroi(v,i,tamanho-1); // O(log n), v=vetor, i=posicao, tamanho-1=ultimo elemento do vetor

    //ordenando o vetor x
    for(i = tamanho-1; i > 0; i--)
     {
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        constroi(v,0,i-1);
     }
}

void constroi(tipo_item *v, int posicao, int fim) //fim = indice da ultima posicao
{
     int trocou, h, i;
     tipo_item aux;
     i = posicao;
     trocou = 1;

     do
     {
        if(2 * i > fim)
           trocou = 0;
        else
        {
           if(2 * i + 1 > fim)
              h = 2 * i;
           else
              if(v[2*i].chave > v[2*i+1].chave)
                 h = 2 * i;
              else
                 h = 2 * i + 1;
           if(v[i].chave < v[h].chave)
           {
              aux = v[i];
              v[i] = v[h];
              v[h] = aux;
              i = h;
           }
           else
              trocou = 0;
        }
     }while(trocou);
}

//QuickSort (pivo elemento do meio)------------------------------------------------
void quickSort(tipo_item *v, int tamanho)
{
	particao(v,0,tamanho-1);
}

void particao(tipo_item *v, int esq, int dir)
{
	int i,k;
	tipo_item aux, pivo;
	pivo = v[(esq+dir)/2];
	i = esq;
	k = dir;
	do {
		while(v[i].chave < pivo.chave)
			i++;
        while(v[k].chave > pivo.chave)
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

//QuickSort (pivo elemento do meio)------------------------------------------------
void quickSortInvertido(tipo_item *v, int tamanho)
{
	particaoInvertida(v,0,tamanho-1);
}

void particaoInvertida(tipo_item *v, int esq, int dir)
{
	int i,k;
	tipo_item aux, pivo;
	pivo = v[(esq+dir)/2];
	i = esq;
	k = dir;
	do {
		while(v[i].chave > pivo.chave)
			i++;
        while(v[k].chave < pivo.chave)
			k--;
		if (i <= k)
		{
			aux = v[k];
			v[k] = v[i];
			v[i] = aux;
			i++;
			k--;
		}
	}while(i <= k);
	if (esq < k)
		particaoInvertida(v,esq,k);
	if (i < dir)
		particaoInvertida(v,i,dir);
}

//QuickSort (pivo elemento numero de 3)------------------------------------------------
void quickSortNum3(tipo_item *v, int tamanho)
{
	particaoNum3(v,0,tamanho-1);
}

void particaoNum3(tipo_item *v, int esq, int dir)
{
	int i,k;
	tipo_item aux, pivo;
	pivo = v[(esq+dir+(esq+dir)/2)/3];
	i = esq;
	k = dir;
	do {
		while(v[i].chave < pivo.chave)
			i++;
        while(v[k].chave > pivo.chave)
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
		particaoNum3(v,esq,k);
	if (i < dir)
		particaoNum3(v,i,dir);
}
//QuickSort (pivo elemento <= 20 insert)------------------------------------------------
void quickSortInsert(tipo_item *v, int tamanho)
{
	particaoInsert(v,0,tamanho-1);
}

void particaoInsert(tipo_item *v, int esq, int dir)
{
	int i,k;
	tipo_item aux, pivo;
	pivo = v[(esq+dir+(esq+dir)/2)/3];
	i = esq;
	k = dir;
	do {
		while(v[i].chave < pivo.chave)
			i++;
        while(v[k].chave > pivo.chave)
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
	if( (k-i) <= 20 )
    {
        insertSortLimitado(v,i,k);
    }
	if (esq < k)
		particaoInsert(v,esq,k);
	if (i < dir)
		particaoInsert(v,i,dir);
}

void insertSortLimitado(tipo_item *v, int esq, int dir)
{
	int i,j;
	tipo_item aux;
	for (i = esq+1; i < dir; i++)
	{
		aux = v[i];
		j = i - 1;
		while ( ( j >= esq ) && ( aux.chave < v[j].chave ) )
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = aux;
	}
}

//QuickSort sem recursão -----------------------------------------------
void QuickSortNaoRec(tipo_item *v, int tamanho)
{
     pilha p; tipo_item_pilha item;
     int esq, dir, i, j;

     cria_pilha(&p);
     esq = 0;
     dir = tamanho-1;
     item.dir = dir;
     item.esq = esq;
     push(&p,item);
     do
     {
       if (dir > esq)
        {
          ParticaoNaoRec(v,esq,dir,&i, &j);
          if ((j-esq)>(dir-i))
          {
             item.dir = j;
             item.esq = esq;
             push(&p,item);
             esq = i;
          }
          else
          {
              item.esq = i;
              item.dir = dir;
              push(&p,item);
              dir = j;
          }
       }
       else
       {
        pop(&p,&item);
        dir = item.dir;
        esq = item.esq;
       }
     }while (!pilha_vazia(p));
}

void ParticaoNaoRec(tipo_item *v,int Esq, int Dir,int *i, int *j)
{
  tipo_item pivo, aux;
  *i = Esq;
  *j = Dir;
  pivo = v[(*i + *j)/2];
  do
  {
    while (pivo.chave > v[*i].chave) (*i)++;
    while (pivo.chave < v[*j].chave) (*j)--;
    if (*i <= *j)
    {
      aux = v[*i];
      v[*i] = v[*j];
      v[*j] = aux;
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

