#include "lista_invertida.h"

// funções lista

lista cria_lista()
{
	lista l;
	l=(lista)malloc(sizeof(lista));
	if (!l)
	   return 0;
	l->inicio=NULL;
	l->tamanhoLista=0;
	return l;
}

int termina_lista (lista *l)
{
	tipo_nodo_lista *p;
	p=(*l)->inicio;
	while (p)
	{
		(*l)->inicio=p->prox;
		free(p);
		p=(*l)->inicio;
	}
	free(*l);
	(*l)=NULL;
	return 1;
}

/*int pesquisaPalavraLista (lista l,FILE *arq,arquivo *arquivosUsados)
{
	tipo_nodo_lista *p;

	p=l->inicio;
	if (p){
		do
		{
            fprintf(arq,"%d %d\t\t",p->info_lista.indiceArquivo,p->info_lista.ocorrencias);
			printf ("\nArquivo= %s\tNúmero de vezes=%d",arquivosUsados[p->info_lista.indiceArquivo].nome,p->info_lista.ocorrencias);
			p=p->prox;
		}while (p);
	}
	else
		return 0;
	return 1;
}

int pesquisaPalavraLista2 (lista l,arquivo *arquivosUsados)
{
	tipo_nodo_lista *p;
	p=l->inicio;
	if (p){
		do
		{
			printf ("\nArquivo= %s\tNúmero de vezes=%d",arquivosUsados[p->info_lista.indiceArquivo].nome,p->info_lista.ocorrencias);
			p=p->prox;
		}while (p);
	}
	else
		return 0;
	return 1;
}

int imprimeListaPalavra (lista l,arquivo *arquivosUsados,FILE *arq)
{
	tipo_nodo_lista *p;

	p=l->inicio;
	if (p){
		do
		{
            fprintf(arq,"%d %d\t\t",p->info_lista.ocorrencias,p->info_lista.indiceArquivo);
			p=p->prox;
		}while (p);
	}
	else
		return 0;
	return 1;
}

int imprimeListaPalavra2 (lista l,arquivo *arquivosUsados)
{
	tipo_nodo_lista *p;
	p=l->inicio;
	if (p){
		do
		{
			printf ("\nArquivo= %s\tNÃºmero de vezes=%d",arquivosUsados[p->info_lista.indiceArquivo].nome,p->info_lista.ocorrencias);
			p=p->prox;
		}while (p);
	}
	else
		return 0;
	return 1;
}
*/
int imprimirConteudoLista (lista l)
{
    tipo_nodo_lista *a;
    a = l->inicio;
    while (a != NULL)
    {
      printf("%d %d \t", a->info_lista.ocorrencias, a->info_lista.indiceArquivo);
      a = a->prox;
    }
    return 0;
}

int insere_lista (lista l, tipo_elemento_lista e)
{
    //printf("Entrou no insere lista\n");
	tipo_nodo_lista *p,*ant,*at;
	p=(tipo_nodo_lista *)malloc(sizeof(tipo_nodo_lista));

	if (!p)
		return 0;

	p->info_lista=e;

	at=l->inicio;

		while (at)
		{
			if  (p->info_lista.indiceArquivo < at->info_lista.indiceArquivo)
				break;
			ant=at;
			at=at->prox;
		}

		if (at==l->inicio)
		{
			p->prox=l->inicio;
			l->inicio=p;
		}
		else
		{
			ant->prox=p;
			p->prox=at;
		}

	l->tamanhoLista++;
	return 1;
}

void aumentaOcorrencia(lista l,int indice){
    tipo_nodo_lista *p;

	p=l->inicio;

    while (p->info_lista.indiceArquivo!=indice)
        p=p->prox;

    p->info_lista.ocorrencias++;

}

int procuraIndiceArquivoLista (lista l, int ch)
{
	tipo_nodo_lista *p;
	int i=1;

	p=l->inicio;

    if (p)
        do {
            if (p->info_lista.indiceArquivo == ch)
                return i;
            p=p->prox;
            i++;
        } while (p);
    else
        return 0;
    return 0;
}

void imprimeLista(lista l,FILE *arq)
{
    tipo_nodo_lista *a;
    a = l->inicio;
    while (a != NULL)
    {
      fprintf(arq,"%d %d \t", a->info_lista.ocorrencias, a->info_lista.indiceArquivo);
      a = a->prox;
    }
}
