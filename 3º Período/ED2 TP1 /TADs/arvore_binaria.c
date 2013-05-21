#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_binaria.h"

extern long int memoriaDoHash;

apontador inicializa()
{
    return NULL;
}

void termina_arvore_binaria(apontador *p)
{

}

int pesquisaArvore(apontador p,tipo_chave palavra[TAMANHO_PALAVRA])
{
    //printf("Entrou na pesquisaArvore\n");
    while(p != NULL)
	{
        if(strcmp(p->info.palavraArvore, palavra) == 0)
        {
            printf("\nVocabulario \t\t Lista Invertida \n%s \t\t\t ", p->info.palavraArvore);
            imprimirConteudoLista(p->listaInvertida);
            return 1;
        }
        else
            if(strcmp(p->info.palavraArvore, palavra) > 0)
                p=p->esq;
            else
                p=p->dir;
	}
	printf("\nPalavra nao esta presente nos arquivos\n");
    return 0;
}

int insere(apontador *p, tipo_elemento e,int doc_id)
{
    //printf("Entrou no insere arvore\n");
    //printf("Arvore recebeu: %s \n",e.palavraArvore);
    tipo_elemento_lista elementoLista;
    int r; // Somente para pegar o retorno da funçao

    //Adicionando o doc_id
    elementoLista.indiceArquivo = doc_id+1;

    if (!(*p))
    {
        *p = (apontador)malloc(sizeof(tipo_nodo));
        (*p)->info = e;
        (*p)->listaInvertida = cria_lista(); // Inicializa a lista invertida para este nodo
        // Primeiros nodos
        (*p)->esq = NULL;
        (*p)->dir = NULL;
        //Primeira ocorrencia
        elementoLista.ocorrencias = 1;
        //Insere na lista
        insere_lista((*p)->listaInvertida,elementoLista);
        memoriaDoHash += sizeof(e) + sizeof(elementoLista);
        return 1;
    }
    else
    {
        //verifica se já houve ocorrencia da palavra
        if ( strcmp( (*p)->info.palavraArvore, e.palavraArvore ) == 0)
        {
            //printf("Palavra repetida: %s\n", e.palavraArvore);
            r = procuraIndiceArquivoLista((*p)->listaInvertida,elementoLista.indiceArquivo);

            if(!r)
            {
                elementoLista.ocorrencias = 1;
                insere_lista((*p)->listaInvertida,elementoLista); // Mais uma palavra a lista
                memoriaDoHash += sizeof(elementoLista);
            }
            else
                aumentaOcorrencia((*p)->listaInvertida,elementoLista.indiceArquivo);
            return 0;
        }
        else
            if (strcmp((*p)->info.palavraArvore,e.palavraArvore) > 0)
            {
                //printf("Entrou no esq\n");
                return insere(&(*p)->esq, e, doc_id);
            }
            else
            {
                //printf("Entrou no dir\n");
                return insere(&(*p)->dir, e, doc_id);
            }

    }
}

void imprimeArvore(apontador p,FILE *arq)
{
    if(!p)
        return;
    imprimeArvore(p->esq,arq);
    fprintf(arq,"\n%s \t",p->info.palavraArvore);
    imprimeLista(p->listaInvertida,arq);
    imprimeArvore(p->dir,arq);
}
