#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "QuickSort.h"
#include "filaPrioridade.h"

#define TAM_RUN 50
#define TAM_BUFFER 3

typedef struct {
    int chave[TAM_BUFFER];
    int posAtualBuffer;
    int posAtual;
    int totalBuffer;
    int totalElementos;
}tipo_buffer;

void gerarArquivo();

void ordenacaoExterna();

void gerar_runs();

int inserirElementosBufferEntrada();


#endif // FUNCOES_H_INCLUDED
