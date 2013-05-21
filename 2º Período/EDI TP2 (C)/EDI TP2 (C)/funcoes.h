#ifndef FUNCOES
#define FUNCOES

#include "estruturas_de_ordenacao.h"
#include <stdio.h>

#define TAM_1 5000
#define TAM_2 10000
#define TAM_3 50000
#define TAM_4 100000
#define TAM_5 500000
#define TAM_6 1000000

//Gera e aloca memoria para vetor do tipo item... usado para o primeiro vetor aleatorio
item geraVetor(int tamanho,FILE *arq);

// Imprime um vetor do tipo item
int imprimirVetor(item v, int tamanho);

//Calcula o tempo com base nos tempos de inicio e fim de execucao
double calculaTempo(double inicio, double fim);

// Finaliza um vetor do tipo item
void terminaVetor(item v);

//Menu principal
void menu();

//Menu para escolha de um ordenador
void menuOrdenadores(FILE *arq2);

//Faz uma copia de conteudo de 1 vetor
void copiaVetor(item v1,item v2,int tamanho);

// Aloca memoria para um vetor de tamanho n
item alocaVetor(int tamanho);

//Termina todos os vetores case inicializados
void terminaVetores();

//Apresenta Resultados de tempo
void resultadoOrdenacao(int op,FILE *arq2);


#endif
