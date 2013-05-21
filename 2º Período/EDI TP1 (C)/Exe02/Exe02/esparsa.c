#include <stdio.h>
#include <stdlib.h>
#include "esparsa.h"

#define LIMPA_VARIAVEIS(_string, _tamanho) memset(_string,'\0',_tamanho) //cortesia do arthir
#define TAM_NUMERO 10


listaMatriz *criaCabecalho(int l, int c)
{
    listaMatriz *mat;
	mat = (listaMatriz *)malloc(sizeof(listaMatriz));

	if (!mat || l <= 0 || c <= 0)
        return 0;

	//Cria o cabeçalho da matriz, recebendo linha e coluna
	mat->inicio = NULL;
	mat->fimLinha = NULL;
	mat->fimColuna = NULL;
	mat->linha = l;
	mat->coluna = c;

	criaMatriz(mat);

	return mat;
}

int criaMatriz(listaMatriz *mat)
{
    int i=0;

    tipo_nodo *p, *colunas, *linhas;
    p = (tipo_nodo*)malloc(sizeof(tipo_nodo));

    if (!p)
        return 0; 

    //Cria Nodo Principal
    p->coluna = -1;
    p->linha = -1;

    mat->inicio = p;
    mat->fimLinha = p;
    mat->fimColuna = p;

    //Cria Estrutura da Coluna de acordo com o nº no cabeçalho da matriz
    for (i = 1; i <= mat->coluna; i++) 
    {
        colunas = (tipo_nodo*)malloc(sizeof(tipo_nodo));

    if (!colunas)
        return 0; 

    colunas->coluna = -1;
    colunas->linha = 0;

    mat->fimColuna->prox = colunas;
    mat->fimColuna = colunas;

    colunas->prox = mat->inicio;
    colunas->baixo = colunas;
    }
    //Cria Estrutura Da Linha de acordo com o nº no cabeçalho da matriz
    for (i = 1; i <= mat->linha; i++) 
    {
        linhas = (tipo_nodo*)malloc(sizeof(tipo_nodo));

    if (!linhas)
        return 0;

    linhas->coluna = 0;
    linhas->linha = -1;

    mat->fimLinha->baixo = linhas;
    mat->fimLinha = linhas;

    linhas->baixo = mat->inicio;
    linhas->prox = linhas;
    }
    return 1;
}

int insere(listaMatriz *mat, int linha, int coluna, float valor)
{
    int i;

    if (!mat || !mat->linha || !mat->coluna)
        return 0;
    if (linha > mat->linha || coluna>mat->coluna || !valor || linha < 1 || coluna < 1)
        return 0;

    tipo_nodo *m; 
    //Nodos temporario para percorrer linhas e colunas
    tipo_nodo *mColuna; 
    tipo_nodo *mLinha; 

    m = (tipo_nodo*)malloc(sizeof(tipo_nodo));

    if (!m)
        return 0;

    m->linha = linha;
    m->coluna = coluna;
    m->valor = valor;

    //Linha e coluna recebem os primeiros nodos 
    mLinha = mat->inicio->baixo; 
    mColuna = mat->inicio->prox; 

    //Percorre as linhas da estrutura ate a linha informada
    for (i = 0; i < linha-1; i++)
    {
        mLinha = mLinha->baixo;
    }
    
    i =0 ;
    //Permite inserir nodo a esquerda e/ou aleatoriamente
    while (i < coluna && mLinha->prox->linha != -1)
    {
        if (m->coluna < mLinha->prox->coluna)
        {
            m->prox = mLinha->prox;
            mLinha->prox = m;
        }
        else
        {
            mLinha = mLinha->prox; //Continua para o prox nodo
        }
        i++;
    }
    if (mLinha->prox->linha == -1) //Se for o ultimo nodo
    {
        m->prox = mLinha->prox; //Aponta para linha cabeça
        mLinha->prox = m; //E o nodo inserido passa ser o ultimo
    }
    
    //Percorre as linhas da estrutura ate a coluna informada
    for (i = 0; i < coluna-1; i++) 
    {
        mColuna = mColuna->prox; 
    }
    
    i=0;
    //Permite inserir nodo mas a baixo e/ou aleatoriamente
    while (i < linha && mColuna->baixo->coluna != -1) 
    {
        if (m->linha < mColuna->baixo->linha)
        {
            m->baixo = mColuna->baixo; 
            mColuna->baixo = m;
        }
        else
        {
            mColuna = mColuna->baixo; //anda pelas celulas abaixo
        }
        i++;
    }
    if (mColuna->baixo->coluna == -1)
    {
        m->baixo = mColuna->baixo; //aponta para a coluna cabeca
        mColuna->baixo = m; //E o nodo inserido passa ser o ultimo
    }
    return 1;
}


int imprimeMatriz(listaMatriz *mat)
{
    int i, j;
    tipo_nodo *m;

    if (!mat || !mat->linha || !mat->coluna)
        return 0;

    m = mat->inicio->baixo;

    printf("\n");

    for (i = 1; i <= mat->linha; i++)
    {
        //Percorre a coluna imprimindo todos nodos encontrados
        for (j = 1; j <= mat->coluna; j++)
        {
            if (i == m->prox->linha && j == m->prox->coluna)
            {
                m = m->prox;
                printf("  \t%0.2f   ",m->valor);
            }
            else
            {
                printf("  \t%0.2f   ",0.0);//se nao encontro nodo imprimi nada
            }
            
        }
        printf("\n");
        m = m->prox->baixo; //Termino de imprimi, muda de linha e continua.
    }

    return 1;
}

int apagaMatriz(listaMatriz *mat)
{

    int i, j;
    tipo_nodo *p, *aux;

    if (!mat || !mat->linha || !mat->coluna)
        return 0;

    p = mat->inicio->baixo;
    p = p->prox;
    aux = p;

    // Apaga os Nodos
    while (p->coluna!=-1)//Enquanto nao for o nodo cabeça da coluna
    {
        while(p->prox->linha!=-1)//Enquanto nao for o nodo cabeça da linha
        {
            if (i == p->prox->linha && j == p->prox->coluna)
            {
                p = p->prox;
                if (aux)
                    free(aux);
                if (p->prox->linha!=-1)
                    aux = p;
            }
            else
                p = p->prox;
        }
        p = p->baixo->prox;
    }

    //Apagando a estrutura
    p = mat->inicio->prox;

    for (i = 0; i < mat->coluna; i++) //Percorre e Apaga Cabeças da estrutura coluna
    {
        aux = p;
        p = p->prox;
        free(aux);
    }

    p = mat->inicio->baixo;
    for (i = 0; i < mat->linha; i++)//Percorre e Apaga Cabeças da estrutura linha
    {
        aux = p;
        p = p->baixo;
        free(aux);
    }
    
    //Apagando nodo l -1 c -1
    p = mat->inicio;
    free(p);

    //Resetando e apagando Cabeçalho da Matriz
    mat->fimColuna = mat->fimLinha = mat->inicio = NULL;
    mat->linha = mat->coluna = 0;
    mat = NULL;
    free(mat);

    return 1;

}

listaMatriz *somaMatriz(listaMatriz *matA, listaMatriz *matB)
{
    int i, j;
    float soma;
    listaMatriz *matC;
    tipo_nodo *mA, *mB;

    //Verifica se as matrizes tem ordem diferentes
    if (matA->linha != matB->linha || matA->coluna != matB->coluna) 
    {
        printf("\nImpossivel Somar.\nMatrizes de Ordem Diferente.\n\n");
        return NULL;
    }

    //Verifica se as matrizes existem, ajuda na função apagarMatriz
    if (!matA || !matB || !matA->linha || !matA->coluna)
        return NULL;

    //Cria uma MatrizC para receber o resultado da soma
    matC = criaCabecalho(matA->linha, matA->coluna);

    //Posiciona as matrizes na cabeça linha
    mA = matA->inicio->baixo;
    mB = matB->inicio->baixo;

    for (i=1; i <= matA->linha; i++)//Percorre a linha das matrizes
    {
        for (j=1; j <= matA->coluna; j++)//Percorre a coluna das matrizes
        {
            if (j == mA->prox->coluna && j == mB->prox->coluna)
            {
                soma = mA->prox->valor + mB->prox->valor;
                //Se soma tem valor != de 0, insere na MatrizC
                if (soma)
                    insere(matC, i, j, soma);
                mA = mA->prox;
                mB = mB->prox;
            }
            else
            //Se nao existir valor para ser somado, apenas insere o valor na MatrizC
            if (j == mA->prox->coluna)
            {
                insere(matC, i, j, mA->prox->valor);
                mA = mA->prox;
            }
            else
            //Se nao existir valor para ser somado, apenas insere o valor na MatrizC
            if (j == mB->prox->coluna)
            {
                insere(matC, i, j, mB->prox->valor);
                mB = mB->prox;
            }
        }
        mA = mA->prox->baixo;
        mB = mB->prox->baixo;
    }

    return matC;
}

listaMatriz *multiplicaMatriz(listaMatriz *matA, listaMatriz *matB)
{
    int i=0, j=0, k=0;
    float total;
    listaMatriz *matC;

    //Verifica se o nº de colunas da MatrizA = ao nº de linhas da MatrizB
    if (matA->coluna != matB->linha) 
    {
        printf("Impossivel Multiplicar\nNumero De Colunas da Matriz 1 é Diferente Do Numero De Linhas Da Matriz 2.\n\n");
        return NULL;
    }

    //Verifica se as matrizes foram criadas
    if (!matA || !matB || !matA->linha || !matA->coluna || !matB->linha || !matB->coluna)
        return NULL;
       
    //MatrizC é gerada com linhas da MatrizA e de colunas da matrizB    
    matC = criaCabecalho(matA->linha, matB->coluna); 

    for (i = 1; i <= matA->linha; i++)
    {
        for (j = 1; j <= matB->coluna; j++)
        {
            total = 0;
            for (k = 1; k <= matA->coluna; k++)
            {
                total += pegaElemento(matA,i,k) * pegaElemento(matB,k,j);
            }
            if (total)
                insere(matC,i,j,total);
        }
    }
    return matC;
}

float pegaElemento(listaMatriz *mat, int linha, int coluna)
{
    tipo_nodo *p;
    int i=0;

    p = mat->inicio->prox;

    for (i = 0; i < coluna-1; i++) //Percorre ate coluna informada
    {
        p = p->prox;
    }

    do
    {
        p = p->baixo;
    
        if (p->linha == linha)
        {
            return p->valor;
        }
        
    }while(p->coluna != -1); //Enquanto nao for o nodo cabeça coluna

    return 0; 
}

listaMatriz *lerMatriz(char *nome)
{
    listaMatriz *mat;

    char linha[TAM_BUFFER];

    int l, c;
    int lin, col;
    float valor;

    FILE *arquivo;

    arquivo = fopen(nome,"r");
    if (!arquivo)
    {
      printf("\nErro, Arquivo Nao Existe.\n\n");
    
      return NULL;
    }

    //Ler primeira linha do arquivo onde contem a ordem da matriz
    fgets(linha, TAM_BUFFER, arquivo);
    sscanf(linha, "%d %d", &l, &c);
    
    //Se a ordem fornecidas no arquivo for 0x0 ou invalidas, erro
    if (l <= 0 || c <= 0)
        return 0;
        
    //Caso contrario crio cabeçalho com ordem linhaxcoluna
    mat = criaCabecalho(l, c);

    //Percorro o arquivo linha por linha pegando linha, coluna e valor
    while(fgets(linha, TAM_BUFFER, arquivo))
    {
        sscanf(linha, "%d %d %f", &lin, &col, &valor);
        insere(mat, lin, col, valor);
    }
    fclose(arquivo);
    printf("\nSucesso, Arquivo Aberto!!\n\n");
    
    return mat;
}
