#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "estruturas_de_ordenacao.h"
#include "busca_ordenadores.h"

void buscaOrdenadores(item vetor,int tamanho,int op,FILE *arq2)
{
    double tempoInicio, tempoFim, tempo;
    int tempoMin,tempoHora;

    if(vetor)
    {
        switch(op)
        {
            case 1:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                bubbleSort(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 2:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                selectSort(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 3:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                insertSort(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 4:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                shellSort(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 5:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                heapSort(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 6:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                quickSort(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 7:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                quickSortNum3(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 8:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                quickSortInsert(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
            case 9:
                tempoInicio = clock(); // armazena o tempo antes de executar o ordenador
                QuickSortNaoRec(vetor, tamanho);
                tempoFim = clock();  // armazena o tempo após  executar o ordenador
                break;
        }

        tempo = calculaTempo(tempoInicio, tempoFim); // Recebe tempo total em segundos
        printf("Tempo de execucao %0.3lf segundo(s)\n",tempo);
        fprintf(arq2,"Tempo de execucao %0.3lf segundo(s)\n",tempo);
        //Descomentar para imprimir o tempo na forma de Hora:Minuto:Segundo
        /*
        if(tempo < 60)
        {
            printf("Tempo de execucao %0.3lf segundo(s)\n",tempo);
            fprintf(arq2,"Tempo de execucao %0.3lf segundo(s)\n",tempo);
        }
        else
        if(tempo < 3600)
        {
            tempoMin=(int)tempo/60;
            tempo -= (tempoMin*60);
            printf("Tempo de execucao %d minuto(s) e %0.3lf segundo(s) \n",tempoMin,tempo);
            fprintf(arq2,"Tempo de execucao %d minuto(s) e %0.3lf segundo(s) \n",tempoMin,tempo);
        }
        else
        {
            tempoHora=(int)tempo/3600;
            tempo -= (tempoHora*3600);
            tempoMin=(int)tempo/60;
            tempo -= (tempoMin*60);
            printf("Tempo de execucao %d hora(s), %d minuto(s) e %0.3lf segundo(s) \n",tempoHora,tempoMin,tempo);
            fprintf(arq2,"Tempo de execucao %d hora(s), %d minuto(s) e %0.3lf segundo(s) \n",tempoHora,tempoMin,tempo);
        }
        */
    }
    else
        printf("Erro ao ler vetor");



}
