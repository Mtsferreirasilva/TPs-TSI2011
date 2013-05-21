#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int chao(double n)
{
 return (int) n;
}

/* sobe o elemento i no heap */
void sobe(int i, int heap[MAX])
{
 int j; /* índice do pai de i */
 int temp; /* variável usada na troca (swap) */

 j = chao((i-1)/2);

 /* se i tem pai e que seja maior que i */
 if(j >= 0 && heap[i] > heap[j])
 {
   /* troca ambos */
   temp = heap[i];
   heap[i] = heap[j];
   heap[j] = temp;
   /* e continua subindo este elemento */
   sobe(j, heap);
 }
}

/* desce o elemento i no heap de tamanho n */
void desce(int i, int heap[MAX], int n)
{
 int j; /* índice do filho de i */
 int temp; /* variável usada na troca (swap) */

 j = 2*i + 1;

 if(j < n) /* se i tem filhos */
 {
   if(j < n-1) /* se i tem filho direito */
   {
     /* pega o maior filho... */
     if(heap[j] < heap[j+1])
       j++;
   }
   /* ..e compara com o pai */
   if(heap[j] > heap[i])
   {
     /* troca ambos (swap) */
     temp = heap[i];
     heap[i] = heap[j];
     heap[j] = temp;
     /* e continua descendo o mesmo elemento */
     desce(j, heap, n);
   }
 }
}

void constroiHeap(int vetor[MAX], int n)
{
 int i;
 for(i = chao(n/2); i >= 0; i--)
 {
   desce(i, vetor, n);
 }
}

/* função de ordenação */
void heapsort(int vetor[MAX], int n)
{
 int i; /* contador */
 int temp; /* usado na troca (swap) */
 int tamanhoDoHeap;

 tamanhoDoHeap = n;

 constroiHeap(vetor, n);
 for(i = n-1; i > 0; i--)
 {
   /* coloca o primeiro (que é o maior, pela definição de heap)
    no final do vetor e decrementa o tamanho do heap */
   temp = vetor[i];
   vetor[i] = vetor[0];
   vetor[0] = temp;

   tamanhoDoHeap--;

   desce(0, vetor, tamanhoDoHeap);
 }
}

void imprime(int n, int vetor[MAX])
{
 int i;
 printf("\n  ");
 for(i = 0; i < n; i++)
   printf("[%d] ", i);
 printf("\n  ");
 for(i = 0; i < n; i++)
   printf(" %d  ", vetor[i]);
 printf("\n");
}

int main()
{
 int heap[MAX];
 int n;

 n = 9;

 /* construindo um vetor desordenado */
 heap[0] = 4;
 heap[1] = 6;
 heap[2] = 2;
 heap[3] = 7;
 heap[4] = 7;
 heap[5] = 1;
 heap[6] = 3;
 heap[7] = 0;
 heap[8] = 9;

 printf("\n\n  Vetor desordenado: \n");
 imprime(n,heap);

 sobe(3, heap);
 printf("\n\n  Após subir o elemento da posição [3]: \n");
 imprime(n,heap);

 constroiHeap(heap, n);
 printf("\n\n  Vetor transformado em um heap: \n");
 imprime(n,heap);

 heapsort(heap, n);
 printf("\n\n  Vetor ordenado pelo Heapsort: \n");
 imprime(n,heap);

 printf("\n\n  ");
 system("pause");

 return 0;
}
