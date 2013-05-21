#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"
#include "arvoreAVL.h"
#include "arvoreB.h"

#define TAM_NOME_DIR 255  // Definição de tamanho máximo para nome do diretorio
#define ENTER 13
#define STR_TAMANHO 1000
#define TAM_NOME_ARQUIVO 255

typedef struct {
    char nome[TAM_NOME_ARQUIVO];
}tipo_arquivo;

typedef tipo_arquivo *lista_arquivos;

// -- Protótipos --
int imprimirArquivo(char nomeArquivo[]); // Imprime conteudo de um arquivo txt

int carregarDiretorio(char diretorio[]); // Carrega diretório e lista em um arquivo todos os arquivos .txt

int AbreArquivoTokenizandoHash(char nomeArquivo[],int doc_id, tabela t);  // Tokeniza um arquivo e invia palavra para hash
int tokenizarDiretorioHash(char caminhoAtual[], tabela t); // Faz a abertuda de um diretorio e faz a inserção por tabela hash já com DOC_ID

int tokenizarDiretorioB(char caminhoAtual[], TipoApontador *p);
int AbreArquivoTokenizandoB(char nomeArquivo[], int doc_id, TipoApontador *p);

int tokenizarDiretorioAVL(char caminhoAtual[], avl_apontador *p);
int AbreArquivoTokenizandoAVL(char nomeArquivo[], int doc_id, avl_apontador *p);

int contaLinhasArquivo(); // Conta as linhas do arquivos documentos.txt para fazer os DOC_IDs

void pesquisarPalavras(tabela t); // Faz uma pesquisa por palavra na tabela. (INICIO)

void pesquisarPalavrasB(TipoApontador p); // Faz uma pesquisa por palavra na B. (INICIO)

void tiraAcento(char* palavra);

int palavraValida(char* palavra); // Verifica se começou com um numero
// -----------------

#endif // FUNCOES_H_INCLUDED
