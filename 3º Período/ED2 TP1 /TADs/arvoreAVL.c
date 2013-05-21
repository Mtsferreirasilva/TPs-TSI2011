#include "arvoreAVL.h"

extern long int memoriaDoAVL;

avl_apontador inicializaArvoreAVL()
{
    return NULL;
}

void rot_dir (avl_apontador *apont)
{
    avl_apontador t;
    t = (*apont)->esquerda;
    (*apont)->esquerda = t->direita;
    t->direita = *apont;
    (*apont)->fb = 0;
    *apont = t;
}

void rot_esq_dir (avl_apontador *apont)
{
    avl_apontador u,v;
    u = (*apont)->esquerda;
    v = u->direita;
    u->direita = v->esquerda;
    v->esquerda = u;
    (*apont)->esquerda = v->direita;
    v->direita = *apont;

    if (v->fb == -1)
        (*apont)->fb = 1;
    else
        (*apont)->fb = 0;

    if (v->fb == 1)
        u->fb = -1;
    else
        u->fb = 0;

    *apont = v;
}

void rot_esq (avl_apontador *apont)
{
    avl_apontador u;
    u = (*apont)->direita;
    (*apont)->direita = u->esquerda;
    u->esquerda = *apont;
    (*apont)->fb = 0;
    *apont = u;
}

void rot_dir_esq (avl_apontador *apont)
{
    avl_apontador u,v;
    u = (*apont)->direita;
    v = u->esquerda;
    u->esquerda = v->direita;
    v->direita = u;
    (*apont)->direita = v->esquerda;
    v->esquerda = *apont;

    if (v->fb == 1)
        (*apont)->fb = -1;
    else
        (*apont)->fb = 0;

    if (v->fb == -1)
        u->fb = 1;
    else
        u->fb = 0;
    *apont = v;
}

void caso1(avl_apontador *apont)
{
    /* item foi inserido à esquerda de T e causa desbalanceamento FB(T)=-2 */
    avl_apontador u;
    u = (*apont)->esquerda;
    if (u->fb == -1)
        rot_dir(&(*apont)); /* Caso 1.1 sinais iguais e negativo */
    else
        rot_esq_dir(&(*apont)); /* Caso 1.2 sinais diferentes */
    (*apont)->fb = 0;
}

void caso2(avl_apontador *apont)
{
    /* item foi inserido à direita de T e causa desbalanceamento FB(T)=2 */
    avl_apontador u;
    u = (*apont)->direita;
    if (u->fb == 1)
        rot_esq(&(*apont)); /* Caso 2.1 sinais iguais e positivo */
    else
        rot_dir_esq(&(*apont)); /* Caso 2.2 sinais diferentes */
    (*apont)->fb = 0;
}

int insereAVL(avl_apontador *ap,tipo_elemento_avl e,int doc_id)
{

    tipo_elemento_lista elementoLista;
    int retorno,deu;

    elementoLista.indiceArquivo=doc_id+1;

    if ((*ap)==NULL)
    {
        *ap=(avl_apontador)malloc(sizeof(tipo_nodo_avl));
        if (!ap)
            return 0;
        (*ap)->info_avl=e;
        (*ap)->fb=0;
        (*ap)->listaInvertida=cria_lista();
        elementoLista.ocorrencias=1;
        insere_lista((*ap)->listaInvertida,elementoLista);
        memoriaDoAVL+=sizeof(elementoLista)+sizeof(e);
        (*ap)->esquerda=NULL;
        (*ap)->direita=NULL;
        return 1;
    }
    else
    {
        if (strcmp((*ap)->info_avl.chave,e.chave)==0){
            retorno=procuraIndiceArquivoLista((*ap)->listaInvertida,elementoLista.indiceArquivo);
            if (!retorno){
                elementoLista.ocorrencias=1;
                insere_lista((*ap)->listaInvertida,elementoLista);
                memoriaDoAVL+=sizeof(e);
            }
            else
                aumentaOcorrencia((*ap)->listaInvertida,elementoLista.indiceArquivo);
            deu=0;
        }
        else
            if (strcmp((*ap)->info_avl.chave,e.chave)<0){
                deu=insereAVL(&(*ap)->direita, e, doc_id);
                if (deu)
                    switch ((*ap)->fb) {
                        case -1: (*ap)->fb = 0;
                                deu = 0;
                                break;
                        case 0 : (*ap)->fb = 1;
                                break;
                        case 1 : caso2(&(*ap));
                                deu = 0;
                                break;
                    }
            }
            else {
                deu=insereAVL(&(*ap)->esquerda, e, doc_id);
                if (deu)
                    switch ((*ap)->fb) {
                        case 1 : (*ap)->fb = 0;
                                deu = 0;
                                break;
                        case 0 : (*ap)->fb = -1;
                                break;
                        case -1: caso1(&(*ap));
                                deu = 0;
                                break;
                    }
            }
    }
    return deu;
}

int pesquisaArvoreAVL(avl_apontador p,tipo_chave_avl palavra[TAMANHO_PALAVRA])
{
    while(p != NULL)
	{
        if(strcmp(p->info_avl.chave, palavra) == 0)
        {
            printf("\nVocabulario \t\t Lista Invertida \n%s \t\t\t ", p->info_avl.chave);
            imprimirConteudoLista(p->listaInvertida);
            return 1;
        }
        else
            if(strcmp(p->info_avl.chave, palavra) > 0)
                p=p->esquerda;
            else
                p=p->direita;
	}
	printf("\nPalavra nao esta presente nos arquivos\n");
    return 0;
}

void arquivaAVL(avl_apontador p)
{
    FILE *arqLista;
    arqLista = fopen("ListaInvetidaArvoreAVL.txt","w");
    if(!arqLista || !p)
        return;
    fprintf(arqLista,"Lista Invertida Arvore AVL\n\n");

    imprimeArvoreAVL(p,arqLista);

    fclose(arqLista);
}

void imprimeArvoreAVL(avl_apontador p,FILE *arq)
{
    if(!p)
        return;
    imprimeArvoreAVL(p->esquerda,arq);
    fprintf(arq,"\n%s \t",p->info_avl.chave);
    imprimeLista(p->listaInvertida,arq);
    imprimeArvoreAVL(p->direita,arq);
}


int terminaArvoreAVL(avl_apontador *p)
{
    return 0;
}
