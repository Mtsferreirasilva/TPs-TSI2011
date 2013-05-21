#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fila.h"
#include "Funcoes.h"

#define ENTER 13
#define ESC 27

int idPouso;
int prateleiraAtual;
int pistaDecolagem;
int idDecolagem;

int main()
{
    system("color 0F");
    srand(time(NULL)); // Para sempre gerar sequancias diferentes

    int pista1,pista2,pista3; // Recebe 1 ativa(decolagem em andamento), 0 para liberada para pouso
    pista1 = 0;
    pista2 = 0;
    pista3 = 1;

    fila p1,p2,p3,p4; // Filas das plataformas 1 2 3 4 para aterrisagem
    //Sendo p1 e p2 para pista 1 e p3 e p4 para pista 2
    fila d1,d2,d3; // Filas para decolagem 1 2 3 para cada pista

    // Fila -------------
    p1 = cria_fila();
    p2 = cria_fila();
    p3 = cria_fila();
    p4 = cria_fila();
    d1 = cria_fila();
    d2 = cria_fila();
    d3 = cria_fila();
    // -------------------

    int randomNumAvioesChegando, randomNumAvioesSaindo; // 0 a 3
    char tecla; // Para saber quando usuario clicou ESC
    localizacaoAviao idSemCombustivel; // Armazena localizaçao de aviao com comb 0 para retirar da fila
    int contPousos1 = 0,contPousos2 = 0; // conta quantos pousos ocorreram
    int numAvioesZerados = 0; // Conta quantos avioes com combustibel zero foram encontrados.
    int pistasUsadas = 0; /* Usado para retornar 0 1 ou 2, caso utilize as pistas 1 e 2 durante aterrisagem de
                            aviao com combustivel 0. Se 1 eu sei que a pista 2 esta sendo usada, por isso nenhuma
                            ação de pouso ou decolagem nao pode ocorrer na pista 2, se 2, nao pode usar a pista 1 e 2*/
    int caiu = 0; // Conta avioes que nao entram na lista dos 3 permitidos para pouso com combustivel 0.
    float medias; // Medias dos avies já pousados ou já decolados.

    // Cabeçalho do programa ------------------------------------------------------------------
    printf("\t\t\tSimulacao de Pousos e Aterrisagens \n");
    printf("--------------------------------------------------------------------------------");
    printf("Os valores de entrada serao atribuidos automaticamente.");
    printf("\nPressione qualquer tecla para avancar 1 unidade de tempo e ESC para finalizar.\n");
    printf("--------------------------------------------------------------------------------");

    // Loop das ações--------------------------------------------------------------------------
    do{
        idSemCombustivel.id=0;
        idSemCombustivel.prateleira=0;

        randomNumAvioesChegando = rand()%4;
        randomNumAvioesSaindo = rand()%4;

        printf("\n>>Numero de avioes chegando p/ pouso: %d",randomNumAvioesChegando);
        printf("\n>>Numero de avioes saindo p/ decolagem: %d\n",randomNumAvioesSaindo);

        printf("\n>>Avioes pousados devido falta combustivel: %d\n",numAvioesZerados);

        printf("\n>>Tempo medio de espera na fila para pouso: %0.2f",TempoEsperaPouso(p1,p2,p3,p4));
        printf("\n>>Tempo medio de espera na fila para decolagem: %0.2f",TempoEsperaDecolagem(d1,d2,d3));
        printf("\n>>Tempo medio de espera para avioes que ja decolaram: %0.2f",mediaDecolar());
        printf("\n>>Tempo medio de espera para avioes que ja pousaram: %0.2f\n",mediaPousar());

        printf("\n>>Caiu: %d\n",caiu); // Descomentar caso queira descobrir quantos cairam.

        printf("\n>>Acoes de enfileiramento nas prateleiras");
        AdicionaNasPrateleiras(randomNumAvioesChegando,p1,p2,p3,p4);

        printf("\n\n>>Acoes de enfileiramento nas pistas de decolagem");
        AdicionaParaDecolar(randomNumAvioesSaindo,d1,d2,d3);

        printf("\n\n>>Acoes de avioes com combustivel zerado ");

        idSemCombustivel = VerificaCombustivel(p1,p2,p3,p4);
        if(idSemCombustivel.id>0)//Possui avioes com 0 de combustivel
        {
            printf("\nPousando aviao ID %d da pratileira %d na pista 3\n",idSemCombustivel.id,idSemCombustivel.prateleira);
            DesenfileiraAviaoSemCombustivel(idSemCombustivel.id,idSemCombustivel.prateleira,p1,p2,p3,p4);
            pista3 = 0;
            pistasUsadas = 0;

            idSemCombustivel = VerificaCombustivel(p1,p2,p3,p4);
            if(idSemCombustivel.id>0)//Possui avioes com 0 de combustivel
            {
                printf("\nPousando aviao ID %d da pratileira %d na pista 2\n",idSemCombustivel.id,idSemCombustivel.prateleira);
                DesenfileiraAviaoSemCombustivel(idSemCombustivel.id,idSemCombustivel.prateleira,p1,p2,p3,p4);
                pista2=0;
                pistasUsadas = 1;

                idSemCombustivel = VerificaCombustivel(p1,p2,p3,p4);
                if(idSemCombustivel.id>0)//Possui avioes com 0 de combustivel
                {
                    printf("\nPousando aviao ID %d da pratileira %d na pista 1\n",idSemCombustivel.id,idSemCombustivel.prateleira);
                    DesenfileiraAviaoSemCombustivel(idSemCombustivel.id,idSemCombustivel.prateleira,p1,p2,p3,p4);
                    pista1=0;
                    pistasUsadas = 2;

                    idSemCombustivel = VerificaCombustivel(p1,p2,p3,p4);
                    if(idSemCombustivel.id>0)//Possui avioes com 0 de combustivel
                    {
                        caiu++; // Caso haja um 4º avião, ele não pode pousar em lugar nenhum, ou seja, morre :).
                    }
                }
            }
            numAvioesZerados++;
        }
        else
        {
            pista3 = 1;
            pistasUsadas = 0;
        }

        printf("\n\n>>Acoes de pouso");
        PousaAvioes(pista1,pista2,p1,p2,p3,p4,pistasUsadas);

        printf("\n\n>>Acoes de decolagem");
        DecolaAvioes(pista1,pista2,pista3,d1,d2,d3,pistasUsadas);

        printf("\n\n>>Estados das Prateleiras");
        printf("\nTamanho da Prateleira 01: %d\n",p1->tamanho);
        ImprimeConteudo(p1);
        printf("\nTamanho da Prateleira 02: %d\n",p2->tamanho);
        ImprimeConteudo(p2);
        printf("\nTamanho da Prateleira 03: %d\n",p3->tamanho);
        ImprimeConteudo(p3);
        printf("\nTamanho da Prateleira 04: %d\n",p4->tamanho);
        ImprimeConteudo(p4);

        printf("\n\n>>Estados das filas de Decolagem");
        printf("\nTamanho da fila 01: %d\n",d1->tamanho);
        ImprimeConteudo(d1);
        printf("\nTamanho da fila 02: %d\n",d2->tamanho);
        ImprimeConteudo(d2);
        printf("\nTamanho da fila 03: %d\n",d3->tamanho);
        ImprimeConteudo(d3);

        printf("\n\n>>Estados das Pistas (0- Livre Pouso, 1- Decolagem em Andamento)");
        printf("\nPista 1: %d",pista1);
        printf("\nPista 2: %d",pista2);
        printf("\nPista 3: %d",pista3);

        printf("\n\n");
        printf(" -------------------------Fim da Unidade de Tempo------------------------------");

        if(contPousos1 >= 5) // A cada x pousos realizados fazer uma verificação se há aviões para decolar
        {
            if(pista1 && fila_vazia(d1))
            {
                pista1 = 0;
                contPousos1 = 0;
            }
            else
            {
               // if(!fila_vazia(d1))
                pista1 = 1;
                //contPousos1 = 0;
            }
        }else
        contPousos1++;

        if(contPousos2 >= 5) // A cada x pousos realizados fazer uma verificação se há aviões para decolar
        {
            if(pista2 && fila_vazia(d2))
            {
                pista2 = 0;
                contPousos2=0;
            }
            else
            {
               // if(!fila_vazia(d2))
                pista2 = 1;
                //contPousos2=0;
            }
        }else
        contPousos2++;

        //Faz com que uma unidade de combustivel seja decrementada de todos os avioes.
        DecrementaCombustivel(p1,p2,p3,p4);
        //Incrementa o tempo de espera para as filas de decolagem somente.
        IncrementaTempoEspera(d1,d2,d3);

        tecla = getch();
    }while(tecla != ESC);


    // Fila --------------
    termina_fila(&p1);
    termina_fila(&p2);
    termina_fila(&p3);
    termina_fila(&p4);
    termina_fila(&d1);
    termina_fila(&d2);
    termina_fila(&d3);
    // -------------------

    return 1;
}
