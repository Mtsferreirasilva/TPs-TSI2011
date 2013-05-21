#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fila.h"
#include "Funcoes.h"

extern int prateleiraAtual = 1; // Armazena a prateleira 1 de inicio.
extern int pistaDecolagem = 3; // Armazena pista de decolagem, iniciando na 3 para melhor fluxo
extern int idPouso = 1; // Armazena o primeiro id impar para os aviões em pouso.
extern int idDecolagem = 2; // Aramazena o primeiro id par para aviões decolando.

int mediaEsperaDecolar = 0; // Para avioes que ja decolaram
int mediaEsperaPousar = 0; // Para avioes que ja pousaram
int avioesDecolados = 0; // Conta quantos decolaram
int avioesPousados = 0; // Conta quantos pousaram

int AdicionaNasPrateleiras(int n, fila p1,fila p2,fila p3,fila p4)
{
    tipo_item aviao;
    int randomCombustivel; // 1 a 20
    while(n) // Enquanto não zerar
    {
        randomCombustivel = rand()%20+1;
        aviao.combustivel = randomCombustivel;
        aviao.id = idPouso;
        aviao.tempoDeEspera=0;

        if((p1->tamanho <= p2->tamanho) && (p1->tamanho <= p3->tamanho) && (p1->tamanho <= p4->tamanho))
            prateleiraAtual = 1;

        if((p2->tamanho <= p1->tamanho) && (p2->tamanho <= p3->tamanho) && (p2->tamanho <= p4->tamanho))
            prateleiraAtual = 2;

        if((p3->tamanho <= p1->tamanho) && (p3->tamanho <= p2->tamanho) && (p3->tamanho <= p4->tamanho))
            prateleiraAtual = 3;

        if((p4->tamanho <= p1->tamanho) && (p4->tamanho <= p2->tamanho) && (p4->tamanho <= p3->tamanho))
            prateleiraAtual = 4;

        switch(prateleiraAtual)
        {
            case 1: enfileira(p1,aviao);
                    printf("\nEnfileirando Aviao ID %d - Combustivel %d - Prateleira 1", idPouso,randomCombustivel);
                    break;
            case 2: enfileira(p2,aviao);
                    printf("\nEnfileirando Aviao ID %d - Combustivel %d - Prateleira 2", idPouso,randomCombustivel);
                    break;
            case 3: enfileira(p3,aviao);
                    printf("\nEnfileirando Aviao ID %d - Combustivel %d - Prateleira 3", idPouso,randomCombustivel);
                    break;
            case 4: enfileira(p4,aviao);
                    printf("\nEnfileirando Aviao ID %d - Combustivel %d - Prateleira 4", idPouso,randomCombustivel);
                    break;
        }
        idPouso+=2;
        n--;
    }
    return 1;
}

int AdicionaParaDecolar(int n,fila d1,fila d2,fila d3)
{
    tipo_item aviao;
    //pistaDecolagem = 3; // Reinicia na pista 3 pois é a pista exclusiva para decolagens
    while(n) // Enquanto não zerar
    {
        aviao.combustivel = 20;
        aviao.id = idDecolagem;
        aviao.tempoDeEspera=0;

        if (d1->tamanho < d2->tamanho)
        {
            if (d1->tamanho < d3->tamanho)
                pistaDecolagem = 1;
            else
                pistaDecolagem = 3;
        }
        else
            if (d2->tamanho < d3->tamanho)
                pistaDecolagem = 2;
            else
                pistaDecolagem = 3;


        switch(pistaDecolagem)
        {
            case 1: enfileira(d1,aviao);
                    printf("\nEnfileirando Aviao ID %d - Combustivel 20 - Pista 1", idDecolagem);
                    break;
            case 2: enfileira(d2,aviao);
                    printf("\nEnfileirando Aviao ID %d - Combustivel 20 - Pista 2", idDecolagem);
                    break;
            case 3: enfileira(d3,aviao);
                    printf("\nEnfileirando Aviao ID %d - Combustivel 20 - Pista 3", idDecolagem);
                    break;
        }

        idDecolagem+=2;
        n--;
    }
    return 1;
}

int PousaAvioes(int pista1,int pista2,fila p1,fila p2,fila p3,fila p4,int n)
{
    tipo_item aviao;
    if(n!=2) // Explicaçao na criação da variavel pistasUsadas no main.c
        if(!pista1) // Se a pista 1 não estiver ativa, ou seja, com avião decolando.
        {
            if(!fila_vazia(p1) && !fila_vazia(p2))
            {
                if(p1->inicio->item.combustivel >= p2->inicio->item.combustivel)
                {
                    desenfileira(p2,&aviao);
                    mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                    avioesPousados++; // incrementa mais um aviao pousado
                    printf("\nPousando aviao ID %d na pista 1, pratileira 2",aviao.id);
                }
                else
                {
                    desenfileira(p1,&aviao);
                    mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                    avioesPousados++; // incrementa mais um aviao pousado
                    printf("\nPousando aviao ID %d na pista 1, pratileira 1",aviao.id);
                }
            }
            else
            if(fila_vazia(p1) && !fila_vazia(p2))
            {
                desenfileira(p2,&aviao);
                mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                printf("\nPousando aviao ID %d na pista 1, pratileira 2",aviao.id);
            }
            else
            if(fila_vazia(p2) && !fila_vazia(p1))
            {
                desenfileira(p1,&aviao);
                mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                printf("\nPousando aviao ID %d na pista 1, pratileira 1",aviao.id);
            }
        }
    if(n==0)
        if(!pista2) // Se a pista 1 não estiver ativa, ou seja, com avião decolando.
        {
            if(!fila_vazia(p3) && !fila_vazia(p4))
            {
                if(p3->inicio->item.combustivel >= p4->inicio->item.combustivel)
                {
                   desenfileira(p4,&aviao);
                   mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                   avioesPousados++; // incrementa mais um aviao pousado
                   printf("\nPousando aviao ID %d na pista 2, pratileira 4",aviao.id);
                }
                else
                {
                    desenfileira(p3,&aviao);
                    mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                    avioesPousados++; // incrementa mais um aviao pousado
                    printf("\nPousando aviao ID %d na pista 2, pratileira 3",aviao.id);
                }
            }
            else
            if(fila_vazia(p3) && !fila_vazia(p4))
            {
                desenfileira(p4,&aviao);
                mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                printf("\nPousando aviao ID %d na pista 2, pratileira 4",aviao.id);
            }
            else
            if(fila_vazia(p4) && !fila_vazia(p3))
            {
                desenfileira(p3,&aviao);
                mediaEsperaPousar += aviao.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                printf("\nPousando aviao ID %d na pista 2, pratileira 3",aviao.id);
            }

        }
    return 1;
}

int DecolaAvioes(int pista1,int pista2,int pista3,fila d1,fila d2,fila d3,int n)
{
    tipo_item aviao;
    if(n!=2) // Explicaçao na criação da variavel pistasUsadas no main.c
        if(pista1)
        {
            if(!fila_vazia(d1))
            {
                desenfileira(d1,&aviao);
                mediaEsperaDecolar += aviao.tempoDeEspera; // atribui a media o valor de espera do aviao
                avioesDecolados++; // Soma mais avioes decolados
                printf("\nDecolando aviao ID %d na pista 1",aviao.id);
            }

        }
    if(n==0) // Explicaçao na criação da variavel pistasUsadas no main.c
        if(pista2)
        {
            if(!fila_vazia(d2))
            {
                desenfileira(d2,&aviao);
                mediaEsperaDecolar += aviao.tempoDeEspera;
                avioesDecolados++;
                printf("\nDecolando aviao ID %d na pista 2",aviao.id);
            }

        }
    if(pista3)
    {
        if(!fila_vazia(d3))
        {
            desenfileira(d3,&aviao);
            mediaEsperaDecolar += aviao.tempoDeEspera;
            avioesDecolados++;
            printf("\nDecolando aviao ID %d na pista 3",aviao.id);
        }

    }
    return 1;
}

float mediaDecolar()
{
    if(avioesDecolados)
        return (float)mediaEsperaDecolar/avioesDecolados;
    return 0;
}

float mediaPousar()
{
    if(avioesPousados)
        return (float)mediaEsperaPousar/avioesPousados;
    return 0;
}

localizacaoAviao VerificaCombustivel(fila p1,fila p2,fila p3,fila p4)
{
    localizacaoAviao localizacao;
    localizacao.id=0; // Inicializar com 0 para que durante o teste no main e possa negar a existencia de aviao zerado
    localizacao.prateleira=0;

    tipo_nodo *a=p1->inicio;
    if(!fila_vazia(p1))
        do
        {
            if(a->item.combustivel == 0)
            {
                localizacao.id = a->item.id;
                localizacao.prateleira = 1;
                printf("\nALERTA: Aviao id %d,combustivel %d, prateleira 1",a->item.id,a->item.combustivel);
                return localizacao; // Retorna a ID(única para cada aviao) do avião com 0 de combustivel
            }
            a=a->prox;
        }while(a);

    a=p2->inicio;
    if(!fila_vazia(p2))
        do
        {
            if(a->item.combustivel == 0)
            {
                localizacao.id = a->item.id;
                localizacao.prateleira = 2;
                printf("\nALERTA: Aviao id %d,combustivel %d, prateleira 2",a->item.id,a->item.combustivel);
                return localizacao; // Retorna a ID(única para cada aviao) do avião com 0 de combustivel
            }

            a=a->prox;
        }while(a);

    a=p3->inicio;
    if(!fila_vazia(p3))
        do
        {
            if(a->item.combustivel == 0)
            {
                localizacao.id = a->item.id;
                localizacao.prateleira = 3;
                printf("\nALERTA: Aviao id %d,combustivel %d, prateleira 3",a->item.id,a->item.combustivel);
                return localizacao; // Retorna a ID(única para cada aviao) do avião com 0 de combustivel
            }

            a=a->prox;
        }while(a);

    a=p4->inicio;
    if(!fila_vazia(p4))
        do
        {
            if(a->item.combustivel == 0)
            {
                localizacao.id = a->item.id;
                localizacao.prateleira = 4;
                printf("\nALERTA: Aviao id %d,combustivel %d, prateleira 4",a->item.id,a->item.combustivel);
                return localizacao; // Retorna a ID(única para cada aviao) do avião com 0 de combustivel
            }

            a=a->prox;
        }while(a);

        return localizacao; // Retorna os valores nulos.
}

void DecrementaCombustivel(fila p1,fila p2,fila p3,fila p4)
{
    tipo_nodo *a=p1->inicio;
    if(!fila_vazia(p1))
        do
        {
            a->item.tempoDeEspera++; // Aproveitando função para incrementar o tempo de espera dos avioes
            a->item.combustivel--;   // nas prateleiras.
            a=a->prox;
        }while(a);

    a=p2->inicio;
    if(!fila_vazia(p2))
        do
        {
            a->item.tempoDeEspera++;
            a->item.combustivel--;
            a=a->prox;
        }while(a);

    a=p3->inicio;
    if(!fila_vazia(p3))
        do
        {
            a->item.tempoDeEspera++;
            a->item.combustivel--;
            a=a->prox;
        }while(a);

    a=p4->inicio;
    if(!fila_vazia(p4))
        do
        {
            a->item.tempoDeEspera++;
            a->item.combustivel--;
            a=a->prox;
        }while(a);
}

void IncrementaTempoEspera(fila d1,fila d2,fila d3)
{
    tipo_nodo *a=d1->inicio;
    if(!fila_vazia(d1))
        do
        {
            a->item.tempoDeEspera++;
            a=a->prox;
        }while(a);

    a=d2->inicio;
    if(!fila_vazia(d2))
        do
        {
            a->item.tempoDeEspera++;
            a=a->prox;
        }while(a);

    a=d3->inicio;
    if(!fila_vazia(d3))
        do
        {
            a->item.tempoDeEspera++;
            a=a->prox;
        }while(a);
}

float TempoEsperaDecolagem(fila d1,fila d2,fila d3)
{
    int media=0;
    int contAvioes=0;

    tipo_nodo *a=d1->inicio;
    if(!fila_vazia(d1))
        do
        {
            media = a->item.tempoDeEspera;
            contAvioes++;
            a=a->prox;
        }while(a);

    a=d2->inicio;
    if(!fila_vazia(d2))
        do
        {
            media = a->item.tempoDeEspera;
            contAvioes++;
            a=a->prox;
        }while(a);

    a=d3->inicio;
    if(!fila_vazia(d3))
        do
        {
            media = a->item.tempoDeEspera;
            contAvioes++;
            a=a->prox;
        }while(a);

    if(contAvioes)
        return (float)media/contAvioes;
    return 0;
}

float TempoEsperaPouso(fila p1,fila p2,fila p3,fila p4)
{
    int media=0;
    int contAvioes=0;

    tipo_nodo *a=p1->inicio;
    if(!fila_vazia(p1))
        do
        {
            media = a->item.tempoDeEspera;
            contAvioes++;
            a=a->prox;
        }while(a);

    a=p2->inicio;
    if(!fila_vazia(p2))
        do
        {
            media = a->item.tempoDeEspera;
            contAvioes++;
            a=a->prox;
        }while(a);

    a=p3->inicio;
    if(!fila_vazia(p3))
        do
        {
            media = a->item.tempoDeEspera;
            contAvioes++;
            a=a->prox;
        }while(a);

    a=p4->inicio;
    if(!fila_vazia(p4))
        do
        {
            media = a->item.tempoDeEspera;
            contAvioes++;
            a=a->prox;
        }while(a);

    if(contAvioes)
        return (float)media/contAvioes;
    return 0;
}

int DesenfileiraAviaoSemCombustivel(int id,int prateleira,fila p1,fila p2,fila p3,fila p4)
{
    tipo_nodo *a=p1->inicio,*ant;

    if(!fila_vazia(p1) && prateleira == 1)
        do
        {
            if(a->item.id == id)
            {
                if(p1->inicio == a)
                {
                    p1->inicio = p1->inicio->prox;
                }else
                if(p1->fim == a)
                {
                    p1->fim = ant;
                    ant->prox = NULL;
                }else
                {
                    ant->prox = a->prox;
                }
                p1->tamanho--;
                mediaEsperaPousar += a->item.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                free(a);
            }
            ant = a;
            a=a->prox;
        }while(a);

    a=p2->inicio;
    if(!fila_vazia(p2) && prateleira == 2)
        do
        {
            if(a->item.id == id)
            {
                if(p2->inicio == a)
                {
                    p2->inicio = p2->inicio->prox;
                }else
                if(p2->fim == a)
                {
                    p2->fim = ant;
                    ant->prox = NULL;
                }else
                {
                    ant->prox = a->prox;
                }
                p2->tamanho--;
                mediaEsperaPousar += a->item.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                free(a);
            }
            ant = a;
            a=a->prox;
        }while(a);

    a=p3->inicio;
    if(!fila_vazia(p3) && prateleira == 3)
        do
        {
           if(a->item.id == id)
            {
                if(p3->inicio == a)
                {
                    p3->inicio = p3->inicio->prox;
                }else
                if(p3->fim == a)
                {
                    p3->fim = ant;
                    ant->prox = NULL;
                }else
                {
                    ant->prox = a->prox;
                }
                p3->tamanho--;
                mediaEsperaPousar += a->item.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                free(a);
            }
            ant = a;
            a=a->prox;
        }while(a);

    a=p4->inicio;
    if(!fila_vazia(p4) && prateleira == 4)
        do
        {
            if(a->item.id == id)
            {
                if(p4->inicio == a)
                {
                    p4->inicio = p4->inicio->prox;
                }else
                if(p4->fim == a)
                {
                    p4->fim = ant;
                    ant->prox = NULL;
                }else
                {
                    ant->prox = a->prox;
                }
                p4->tamanho--;
                mediaEsperaPousar += a->item.tempoDeEspera; // Atribui a media o tempo de espera do aviao
                avioesPousados++; // incrementa mais um aviao pousado
                free(a);
            }
            ant = a;
            a=a->prox;
        }while(a);
    return 1;
}

void ImprimeConteudo(fila f)
{
    tipo_nodo *a=f->inicio;
    printf("IDs: ");
    if(!fila_vazia(f))
        do
        {
            printf(" %d -",a->item.id);
            a=a->prox;
        }while(a);
}
