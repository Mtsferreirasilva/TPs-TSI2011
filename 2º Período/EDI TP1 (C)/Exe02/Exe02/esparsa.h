#ifndef ESPARSA_H
#define ESPARSA_H

#define TAM_BUFFER 255

typedef struct nodo{
    struct nodo *prox, *baixo;
    int linha, coluna;
    float valor;
}tipo_nodo;

typedef struct{
    int linha, coluna;
    tipo_nodo *inicio, *fimLinha, *fimColuna;
}lista;

typedef lista listaMatriz;


listaMatriz *criaCabecalho(int m, int n);
int criaMatriz(listaMatriz *mat);
int insere(listaMatriz *mat, int linha, int coluna, float valor);
int imprimeMatriz(listaMatriz *mat);
int apagaMatriz(listaMatriz *mat);
listaMatriz *somaMatriz(listaMatriz *matA, listaMatriz *matB);
listaMatriz *multiplicaMatriz(listaMatriz *matA, listaMatriz *matB);
float pegaElemento(listaMatriz *mat, int linha, int coluna);

//Função de ler do arquivo
listaMatriz *lerMatriz(char *nome); 

#endif
