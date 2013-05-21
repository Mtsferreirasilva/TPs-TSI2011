#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TADs/tabela_hash.h"
#include "TADs/funcoes.h"
#include "TADs/arvoreB.h"
#include "TADs/arvoreAVL.h"

long int memoriaDoHash;
long int memoriaDoB;
long int memoriaDoAVL;

int main()
{
    srand(time(NULL)); // zerar tempo

    system("chcp 1252 && cls"); // Abilita acento
    system("title 1° Trabalho Prático de Estrutura de Dados II");

    //----- Variaveis para as estruturas --
    tabela tabelaHash;
    TipoApontador arvoreB;
    avl_apontador arvoreAVL;
    //--------------------------------------

    char tecla;
    char diretorio[TAM_NOME_DIR];
    //FILE *arquivoEmDisco = NULL; // Verificará se há algum arquivo já aberto
    char op = '0';
    clock_t inicio,fim;
    double tempo;

    // CAMINHO ATUAL --------------------------
    char caminhoAtual[STR_TAMANHO];
    char ler[STR_TAMANHO];  // armazena as linhas
    system("cd > camAtual.txt");
    FILE *camAtul;
    camAtul=fopen("camAtual.txt","r");
    if(camAtul != NULL)
    {
        while(fgets(ler, STR_TAMANHO, camAtul))  // Armazena em ler as linhas do arquivo aberto
        {
            strcpy(caminhoAtual,ler);
        }
    }else
    {
         fclose(camAtul);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(camAtul);
    //---------------------------------------------

    //Documentos.txt do caminho disponibilizado ----------
    FILE *arqDir;
    arqDir=fopen("documentos.txt","w");
    fprintf(arqDir,"Nenhum diretorio definido");
    fclose(arqDir);
    //----------------------------------------------------

    system("color 1F");

    // While para MENU PRINCIPAL
    while(op != '4')
    {
        system("cls");
        printf("\n Diretorio atual: %s",caminhoAtual);
        printf("\n ------------------------------------ MENU ------------------------------------\n\n");
        printf(" | \t\t\t 1 - Definir diretório                                |\n\n");
        printf(" | \t\t\t 2 - Documentos presentes no diretorio                |\n\n");
        printf(" | \t\t\t 3 - Formas de armazenamento                          |\n\n");
        printf(" | \t\t\t 4 - Sair                                             |\n\n");
        printf(" | \t\t\t\t\t Programador: Mateus Ferreira Silva   |\n\n");
        printf(" ------------------------------------------------------------------------------\n\n");

        op = getch();

        switch (op)
        {
            //Definir diretorio
               case '1' : //system("cls");
                        printf(" Caminho: ");
                        scanf("%s",diretorio);

                        //-----ALTERANDO CAMINHO ATUAL ----
                        char verificaComando[100]; // Joga o comando no system para ver se é valido
                        char caminhoAtualAux[100]; // Recebe o valor temporario de caminho atual
                        if(diretorio[0] == 'C' && diretorio[1] == ':')
                        {
                            strcpy(caminhoAtualAux,caminhoAtual);// para nao mudar a variavel que grava no arquivo
                            strcpy(caminhoAtualAux,diretorio); //copia diretorio digitado para aux
                            sprintf(verificaComando,"cd %s 2> Lixo.txt",caminhoAtualAux); // redireciona msg de erro
                            if(!system(verificaComando)) // para saber se o comando com diretorio digitado funciona
                            {
                                strcpy(caminhoAtual,diretorio); //caminho atual recebe o diretorio pq foi confirmado o comando
                            }
                        }
                        else
                        {
                            strcpy(caminhoAtualAux,caminhoAtual); // para nao mudar a variavel que grava no arquivo
                            caminhoAtualAux[strlen(caminhoAtualAux)-1] = '\\'; // adiciona uma barra no fim
                            strcat(caminhoAtualAux,diretorio); //copia diretorio digitado para aux
                            sprintf(verificaComando,"cd %s 2> Lixo.txt",caminhoAtualAux); // redireciona msg de erro
                            if(!system(verificaComando)) // para saber se o comando com diretorio digitado funciona
                            {
                                caminhoAtual[strlen(caminhoAtual)-1] = '\\';  // adiciona uma barra no fim
                                strcat(caminhoAtual,diretorio);
                            }
                        }
                        //----------------------------------

                        carregarDiretorio(diretorio);
                        printf("\n ------------------------------------------------------------------------------\n\n");
                        printf("\n\n\t\t\t Pressione ENTER para continuar\n");
                        tecla = getch();
                        while(tecla != ENTER)
                           tecla = getch();
                        break;

            //Ler diretorio aberto
               case '2' : //system("cls");
                        printf(" --------------------------------- Documentos ---------------------------------\n\n");
                        imprimirArquivo("documentos.txt");
                        printf("\n\n ------------------------------------------------------------------------------\n\n");
                        printf("\n\n\t\t\t Pressione ENTER para continuar\n");
                        tecla = getch();
                        while(tecla != ENTER)
                           tecla = getch();
                        break;

               case '3' : system("cls");
                          char op2 = '0';
                          while(op2 != '4')
                          {
                              system("cls");
                              printf(" --------------------------- Formas de Armazenamento --------------------------\n\n");
                              printf(" |   1 - Hash com resolucao de conflito via Arvore Binaria sem balanceamento  |\n\n");
                              printf(" |   2 - Arvore AVL                                                           |\n\n");
                              printf(" |   3 - Arvore B                                                             |\n\n");
                              printf(" |   4 - Voltar                                                               |\n\n");
                              printf(" ------------------------------------------------------------------------------\n\n");
                              op2 = getch();

                              switch(op2)
                              {
                                  case '1' : inicio = clock();
                                             tabelaHash = cria_tabela();
                                             tokenizarDiretorioHash(caminhoAtual,tabelaHash);
                                             fim = clock();
                                             tempo = (double)(fim - inicio)*1000/CLOCKS_PER_SEC;
                                             printf("Tempo de insercao: %0.0lf ms\n",tempo);
                                             printf("Memoria utilizada: %ld bytes \n",memoriaDoHash);

                                             arquivaTabela(tabelaHash);
                                             pesquisarPalavras(tabelaHash);
                                             printf("\nPressione ENTER para continuar.");
                                             tecla = getch();
                                             while(tecla != ENTER)
                                                tecla = getch();
                                             break;

                                  case '2' : inicio = clock();
                                             arvoreAVL = inicializaArvoreAVL();
                                             tokenizarDiretorioAVL(caminhoAtual,&arvoreAVL);
                                             fim = clock();
                                             tempo = (double)(fim - inicio)*1000/CLOCKS_PER_SEC;
                                             printf("Tempo de insercao: %0.0lf ms\n",tempo);
                                             printf("Memoria utilizada: %ld bytes \n",memoriaDoAVL);

                                             arquivaAVL(arvoreAVL);
                                             pesquisarPalavrasAVL(arvoreAVL);
                                             printf("\nPressione ENTER para continuar.");
                                             tecla = getch();
                                             while(tecla != ENTER)
                                                tecla = getch();
                                             break;

                                  case '3' : inicio = clock();
                                             inicializaArvoreB(&arvoreB);
                                             tokenizarDiretorioB(caminhoAtual,&arvoreB);
                                             fim = clock();
                                             tempo = (double)(fim - inicio)*1000/CLOCKS_PER_SEC;
                                             printf("Tempo de insercao: %0.0lf ms\n",tempo);
                                             printf("Memoria utilizada: %ld bytes \n",memoriaDoB);

                                             arquivaB(arvoreB,0);
                                             pesquisarPalavrasB(arvoreB);
                                             printf("\nPressione ENTER para continuar.");
                                             tecla = getch();
                                             while(tecla != ENTER)
                                                tecla = getch();
                                             break;
                              }
                          }
                          break;
               case '0' : system("cls");
                          //tokenizarDiretorioHash(caminhoAtual);
                          //AbreArquivoTokenizando("C:/Users/Mateus/Desktop/Mateus/TP1-ED2/Arquivos/Arquivo3.txt");
                          printf("\n\n\n\t\t\t\t== FIM DO ARQUIVO ==\n");
                          printf("\nPressione ENTER para continuar.\n");
                          tecla = getch();
                          while(tecla != ENTER)
                            tecla = getch();
                          break;
        }
    }
  return 0;
}
