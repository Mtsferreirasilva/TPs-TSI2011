#include "arvoreB.h"

extern long int memoriaDoB;

void inicializaArvoreB(TipoApontador *Dicionario)
{
    *Dicionario = NULL;
}

void InsereNaPagina(TipoApontador Ap,TipoRegistro Reg, TipoApontador ApDir,tipo_elemento_lista e){
    short NaoAchouPosicao;
    int k;
    tipo_elemento_lista tel;
    //tel=e;
    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao)
    {
        if (strcmp(Reg.Chave,Ap->r[k-1].Chave)>=0)
        {
            NaoAchouPosicao = FALSE;
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoAchouPosicao = FALSE;
    }


    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu,
         TipoRegistro *RegRetorno,  TipoApontador *ApRetorno,tipo_elemento_lista e)
{
    long i = 1;
    long j,r;
    TipoApontador ApTemp;
    tipo_elemento_lista elemento;

    elemento = e;

    if (Ap == NULL)
    {
        Reg.listaInvertida=cria_lista();
        insere_lista(Reg.listaInvertida,elemento);
        memoriaDoB+=sizeof(Reg)+sizeof(elemento);//calcula tamanho apos insercao
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }
    while (i < Ap->n && (strcmp(Reg.Chave,Ap->r[i-1].Chave)>0))  i++;

    if (!strcmp(Reg.Chave,Ap->r[i-1].Chave))
    {
        r=procuraIndiceArquivoLista(Ap->r[i-1].listaInvertida,elemento.indiceArquivo);
        if (!r){
            insere_lista(Ap->r[i-1].listaInvertida,elemento);
            memoriaDoB+=sizeof(elemento); //calcula tamanho apos insercao
        }
        else
            aumentaOcorrencia(Ap->r[i-1].listaInvertida,elemento.indiceArquivo);
        *Cresceu = FALSE;
        return;
    }

    if (strcmp(Reg.Chave,Ap->r[i-1].Chave)<0) i--;

    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno,e);

    if (!*Cresceu)
        return;
    if (Ap->n < MM)   // Pagina tem espaco
    {
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno,e);
        *Cresceu = FALSE;
        return;
    }

    // Divisao da pagina
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < M + 1)
    {
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM],e);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno,e);
    }
    else
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno,e);

    for (j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j],e);

    Ap->n = M;
    ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}


void InsereB(TipoRegistro Reg, TipoApontador *Ap,int doc_id)
{
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    tipo_elemento_lista e;

    // Lista
    e.indiceArquivo=doc_id+1;
    e.ocorrencias=1;

    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno,e);

    if (Cresceu)
    {

        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

TipoRegistro* Pesquisa(TipoRegistro palavra, TipoApontador Ap){
   long i = 1;
   if (Ap == NULL){
       printf("\nPalavra nao esta presente nos arquivos\n");
       return NULL;
   }
   while (i < Ap->n && strcmp(palavra.Chave, Ap->r[i-1].Chave) > 0)
       i++;
   if (strcmp(palavra.Chave, Ap->r[i-1].Chave) == 0) {
       return &(Ap->r[i-1]);
   }
   if (strcmp(palavra.Chave, Ap->r[i-1].Chave) < 0)
       return Pesquisa(palavra, Ap->p[i-1]);
   else
       return Pesquisa(palavra, Ap->p[i]);
}

void imprimeConteudoB(TipoRegistro registro)
{
    printf("\nVocabulario \t\t Lista Invertida \n%s \t\t\t ",registro.Chave);
    imprimirConteudoLista(registro.listaInvertida);
}

void arquivaB(TipoApontador arvoreB, int nivel)
{
    FILE *arqLista;
    arqLista = fopen("ListaInvetidaArvoreB.txt","w");
    if(!arqLista || !arvoreB)
        return;
    fprintf(arqLista,"Lista Invertida Arvore B\n\n");

    arquivaB2(arvoreB,nivel,arqLista);

    fclose(arqLista);
}

void arquivaB2(TipoApontador arvoreB, int nivel, FILE *arqLista)
{
    if(!arvoreB)
        return;
    int i;
    for(i = 0; i < arvoreB->n ; i++)
    {
        fprintf(arqLista,"\n%s \t",arvoreB->r[i].Chave);
        imprimeLista(arvoreB->r[i].listaInvertida,arqLista);
    }
    nivel++;
    for(i = 0; i <= arvoreB->n ; i++)
    {
        arquivaB2(arvoreB->p[i],nivel,arqLista);
    }
}


