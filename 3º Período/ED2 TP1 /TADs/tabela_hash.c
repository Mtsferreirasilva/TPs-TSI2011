#include "tabela_hash.h"

tabela cria_tabela()
{
    tabela T = (tabela)malloc(sizeof(tipo_tabela));
    int i;
    if (!T)
        return NULL;
    T->tamanho = 0;
    for (i=0; i<TAMANHO_HASH; i++){
        T->elementos[i] = NULL;
    }
    return T;
}

int termina_tabela(tabela *t)
{
    int i;
    if (!t)
        return 0;

    for (i=0;i<=TAMANHO_HASH;i++){
        if ((*t)->elementos[i])
            termina_arvore_binaria(&(*t)->elementos[i]);
    }
    free(*t);
    return 1;
}

int insere_tabela(tabela *t, char *palavra, int doc_id)
{
    //printf("Entrou no insere tabela\n");
    //printf("Hash recebeu: %s \n",palavra);

    tipo_elemento elementoArvore;
    int codigoPalavra,codigoHash;

    codigoPalavra = stringParaInt(palavra); // Somente pega o codigo para a palavra
    codigoHash = hash(codigoPalavra); // Tranforma o codigo da palavra em codigo hash

    //printf("codigoPalavra: %d\n codigoHash: %d\n", codigoPalavra, codigoPalavra);

    if(codigoHash < 0)
        return 0;

    // Se não houve nenhum conflito não há arvore inicializada , entao inicializa
    if(!(*t)->elementos[codigoHash])
        (*t)->elementos[codigoHash] = inicializa();

    //Mandar palavra para a arvore
    strcpy(elementoArvore.palavraArvore,palavra);
    insere(&((*t)->elementos[codigoHash]),elementoArvore,doc_id);
    return 1;
}

// Transforma a palavra em indice
int stringParaInt(char *palavra)
{
    int i;
    int tamanho = strlen(palavra);
    int valor = 0;
    for (i=0; i < strlen(palavra); i++){
        if(i == 1)
            valor += (tamanho * palavra[i]);
        else
            valor += palavra[i]; // Obtem o codigo das letras
    }
    return valor;
}
// Gera hascode
int hash(int valorInt)
{
    return valorInt % TAMANHO_HASH;
}

int pesquisaHash(tabela t,char palavra[])
{
    //printf("Entrou na pesquisaHash\n");
    int codigoPalavra, codigoHash;

    codigoPalavra = stringParaInt(palavra);
    codigoHash = hash(codigoPalavra); // Encontrar o hashcode desta palavra.

    if(codigoHash < 0)
        return 0;
    if(!t)
        return 0;

    //Pesquisa na arvore binaria
    pesquisaArvore(t->elementos[codigoHash],palavra);
    return 1;
}

void arquivaTabela(tabela t)
{
    FILE *arqLista;
    arqLista = fopen("ListaInvetida.txt","w");
    if(!arqLista || !t)
        return;
    fprintf(arqLista,"Lista Invertida Tabela Hash\n\n");
    int i;
    for(i = 0; i < TAMANHO_HASH; i++)
    {
        if(t->elementos[i])
            imprimeArvore(t->elementos[i],arqLista);
    }
    fclose(arqLista);

}


