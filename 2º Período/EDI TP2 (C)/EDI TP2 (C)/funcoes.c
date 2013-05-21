#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "busca_ordenadores.h"

int vetoresCriados = 0; //Para verificar se os vetores ja foram criados ou nao


item vetor1Tam1,vetor2Tam1,vetor3Tam1,
     vetor1Tam2,vetor2Tam2,vetor3Tam2,
     vetor1Tam3,vetor2Tam3,vetor3Tam3,           //3 Vetores para todos os tamanhos definidos
     vetor1Tam4,vetor2Tam4,vetor3Tam4,
     vetor1Tam5,vetor2Tam5,vetor3Tam5,
     vetor1Tam6,vetor2Tam6,vetor3Tam6;

void menu() // Menu Principal
{
    int op;
    FILE *arq,*arq2;
    arq = fopen("Vetores.bin","w");
    arq2 = fopen("Resultados.bin","w");

    do
    {
        system("cls");

        printf("\t\t\tTRABALHO DE ESTRUTURA DE DADOS I\n");
        printf("\t\t\t      METODOS DE ORDENACAO\n\n");

        if(vetoresCriados)
            printf(" 1 - Gerar Vetores (Vetores Gerados e Arquivados)\n");
        else
            printf(" 1 - Gerar Vetores\n");
        printf(" 2 - Ordenadores\n");
        printf(" 0 - Sair\n\n");

        printf("Opcao: ");
        scanf("%d",&op);

        switch(op)
        {
            case 1: //Gerar Vetores;
                    if(!vetoresCriados) // Caso ja tenha criado nao criar denovo
                    {
                        //Inicializando Vetores d

                        //--------------------------TAM 1
                         vetor1Tam1=geraVetor(TAM_1,arq);

                         vetor2Tam1=alocaVetor(TAM_1);//aloca vetor
                        copiaVetor(vetor1Tam1,vetor2Tam1,TAM_1);//copia conteudo do vetor 1
                        quickSort(vetor2Tam1,TAM_1);//ordena vetor 2

                         vetor3Tam1=alocaVetor(TAM_1);
                        copiaVetor(vetor1Tam1,vetor3Tam1,TAM_1);//copia conteudo do vetor 1
                        quickSortInvertido(vetor3Tam1,TAM_1);//ordena vetor 2



                        //--------------------------TAM 2
                         vetor1Tam2=geraVetor(TAM_2,arq);

                         vetor2Tam2=alocaVetor(TAM_2);//aloca vetor
                        copiaVetor(vetor1Tam2,vetor2Tam2,TAM_2);//copia conteudo do vetor 1
                        quickSort(vetor2Tam2,TAM_2);//ordena vetor 2

                         vetor3Tam2=alocaVetor(TAM_2);
                        copiaVetor(vetor1Tam2,vetor3Tam2,TAM_2);//copia conteudo do vetor 1
                        quickSortInvertido(vetor3Tam2,TAM_2);//ordena vetor 2

                        //--------------------------TAM 3
                         vetor1Tam3=geraVetor(TAM_3,arq);

                         vetor2Tam3=alocaVetor(TAM_3);//aloca vetor
                        copiaVetor(vetor1Tam3,vetor2Tam3,TAM_3);//copia conteudo do vetor 1
                        quickSort(vetor2Tam3,TAM_3);//ordena vetor 2

                         vetor3Tam3=alocaVetor(TAM_3);
                        copiaVetor(vetor1Tam3,vetor3Tam3,TAM_3);//copia conteudo do vetor 1
                        quickSortInvertido(vetor3Tam3,TAM_3);//ordena vetor 2

                        //--------------------------TAM 4
                         vetor1Tam4=geraVetor(TAM_4,arq);

                         vetor2Tam4=alocaVetor(TAM_4);//aloca vetor
                        copiaVetor(vetor1Tam4,vetor2Tam4,TAM_4);//copia conteudo do vetor 1
                        quickSort(vetor2Tam4,TAM_4);//ordena vetor 2

                         vetor3Tam4=alocaVetor(TAM_4);
                        copiaVetor(vetor1Tam4,vetor3Tam4,TAM_4);//copia conteudo do vetor 1
                        quickSortInvertido(vetor3Tam4,TAM_4);//ordena vetor 2

                        //--------------------------TAM 5
                         vetor1Tam5=geraVetor(TAM_5,arq);

                         vetor2Tam5=alocaVetor(TAM_5);//aloca vetor
                        copiaVetor(vetor1Tam5,vetor2Tam5,TAM_5);//copia conteudo do vetor 1
                        quickSort(vetor2Tam5,TAM_5);//ordena vetor 2

                         vetor3Tam5=alocaVetor(TAM_5);
                        copiaVetor(vetor1Tam5,vetor3Tam5,TAM_5);//copia conteudo do vetor 1
                        quickSortInvertido(vetor3Tam5,TAM_5);//ordena vetor 2

                        //--------------------------TAM 6
                         vetor1Tam6=geraVetor(TAM_6,arq);

                         vetor2Tam6=alocaVetor(TAM_6);//aloca vetor
                        copiaVetor(vetor1Tam6,vetor2Tam6,TAM_6);//copia conteudo do vetor 1
                        quickSort(vetor2Tam6,TAM_6);//ordena vetor 2

                         vetor3Tam6=alocaVetor(TAM_6);
                        copiaVetor(vetor1Tam6,vetor3Tam6,TAM_6);//copia conteudo do vetor 1
                        quickSortInvertido(vetor3Tam6,TAM_6);//ordena vetor 2

                        vetoresCriados = 1;
                        //Teste
                        /*
                        imprimirVetor(vetor1Tam1,TAM_1);
                        quickSortInsert(vetor2Tam1,TAM_1);
                        imprimirVetor(vetor2Tam1,TAM_1);
                        system("pause");
                            */
                    }
                    break;
            case 2: //Ordenadores;
                    menuOrdenadores(arq2);
                    break;
        }
    }while(op);
    printf("\n\t\t      Programador: Mateus Ferreira Silva\n\n");

    Sleep(1500); // Delay de 1.5 segundos

    if(vetor1Tam1) // Verifica se os vetores foram inicializados
    {
        terminaVetor(vetor1Tam1);
        terminaVetor(vetor2Tam1);
        terminaVetor(vetor3Tam1);

        terminaVetor(vetor1Tam2);
        terminaVetor(vetor2Tam2);
        terminaVetor(vetor3Tam2);

        terminaVetor(vetor1Tam3);
        terminaVetor(vetor2Tam3);
        terminaVetor(vetor3Tam3);

        terminaVetor(vetor1Tam4);
        terminaVetor(vetor2Tam4);
        terminaVetor(vetor3Tam4);

        terminaVetor(vetor1Tam5);
        terminaVetor(vetor2Tam5);
        terminaVetor(vetor3Tam5);

        terminaVetor(vetor1Tam6);
        terminaVetor(vetor2Tam6);
        terminaVetor(vetor3Tam6);
    }

    fclose(arq);
    fclose(arq2);
}

void terminaVetores() //Termina todos os vetores case inicializados
{
    if(vetoresCriados)//Caso os vetores forem criados
    {
        terminaVetor(vetor1Tam1);
        terminaVetor(vetor2Tam1);
        terminaVetor(vetor3Tam1);
        terminaVetor(vetor1Tam2);
        terminaVetor(vetor2Tam2);
        terminaVetor(vetor3Tam2);
        terminaVetor(vetor1Tam3);
        terminaVetor(vetor2Tam3);
        terminaVetor(vetor3Tam3);
        terminaVetor(vetor1Tam4);
        terminaVetor(vetor2Tam4);
        terminaVetor(vetor3Tam4);
        terminaVetor(vetor1Tam5);
        terminaVetor(vetor2Tam5);
        terminaVetor(vetor3Tam5);
        terminaVetor(vetor1Tam6);
        terminaVetor(vetor2Tam6);
        terminaVetor(vetor3Tam6);
    }
}

void resultadoOrdenacao(int op,FILE *arq2)
{
     item vetor1Tam12,vetor2Tam12,vetor3Tam12,
          vetor1Tam22,vetor2Tam22,vetor3Tam22,
          vetor1Tam32,vetor2Tam32,vetor3Tam32,//copia dos 3 vetores para todos os tamanhos definidos
          vetor1Tam42,vetor2Tam42,vetor3Tam42,
          vetor1Tam52,vetor2Tam52,vetor3Tam52,
          vetor1Tam62,vetor2Tam62,vetor3Tam62;

     //Alocando memoria para as variaveis
     vetor1Tam12=alocaVetor(TAM_1);
     vetor2Tam12=alocaVetor(TAM_1);
     vetor3Tam12=alocaVetor(TAM_1);

     vetor1Tam22=alocaVetor(TAM_2);
     vetor2Tam22=alocaVetor(TAM_2);
     vetor3Tam22=alocaVetor(TAM_2);

     vetor1Tam32=alocaVetor(TAM_3);
     vetor2Tam32=alocaVetor(TAM_3);
     vetor3Tam32=alocaVetor(TAM_3);

     vetor1Tam42=alocaVetor(TAM_4);
     vetor2Tam42=alocaVetor(TAM_4);
     vetor3Tam42=alocaVetor(TAM_4);

     vetor1Tam52=alocaVetor(TAM_5);
     vetor2Tam52=alocaVetor(TAM_5);
     vetor3Tam52=alocaVetor(TAM_5);

     vetor1Tam62=alocaVetor(TAM_6);
     vetor2Tam62=alocaVetor(TAM_6);
     vetor3Tam62=alocaVetor(TAM_6);

     // Copiando vetores
     //printf("\nCopiando vetores de tamanho 5000");
     copiaVetor(vetor1Tam1,vetor1Tam12,TAM_1);
     copiaVetor(vetor2Tam1,vetor2Tam12,TAM_1);
     copiaVetor(vetor3Tam1,vetor3Tam12,TAM_1);

     //printf("\nCopiando vetores de tamanho 10000");
     copiaVetor(vetor1Tam2,vetor1Tam22,TAM_2);
     copiaVetor(vetor2Tam2,vetor2Tam22,TAM_2);
     copiaVetor(vetor3Tam2,vetor3Tam22,TAM_2);

     //printf("\nCopiando vetores de tamanho 50000");
     copiaVetor(vetor1Tam3,vetor1Tam32,TAM_3);
     copiaVetor(vetor2Tam3,vetor2Tam32,TAM_3);
     copiaVetor(vetor3Tam3,vetor3Tam32,TAM_3);

     //printf("\nCopiando vetores de tamanho 100000");
     copiaVetor(vetor1Tam4,vetor1Tam42,TAM_4);
     copiaVetor(vetor2Tam4,vetor2Tam42,TAM_4);
     copiaVetor(vetor3Tam4,vetor3Tam42,TAM_4);

     //printf("\nCopiando vetores de tamanho 500000");
     copiaVetor(vetor1Tam5,vetor1Tam52,TAM_5);
     copiaVetor(vetor2Tam5,vetor2Tam52,TAM_5);
     copiaVetor(vetor3Tam5,vetor3Tam52,TAM_5);

     //printf("\nCopiando vetores de tamanho 1000000");
     copiaVetor(vetor1Tam6,vetor1Tam62,TAM_6);
     copiaVetor(vetor2Tam6,vetor2Tam62,TAM_6);
     copiaVetor(vetor3Tam6,vetor3Tam62,TAM_6);

     //system("cls");
     fprintf(arq2,"-------------------------------------------------------------------------\n");

     fprintf(arq2,"\n\t\t\tVETORES DE TAMANHO 5000\n");
     printf("\t\t\tVETORES DE TAMANHO 5000\n");
     fprintf(arq2,"\nNao ordenado: ");
     printf("\nNao ordenado: ");
     buscaOrdenadores(vetor1Tam12,TAM_1,op,arq2);
     fprintf(arq2,"Ordenado crescentemente: ");
     printf("Ordenado crescentemente: ");
     buscaOrdenadores(vetor2Tam12,TAM_1,op,arq2);
     fprintf(arq2,"Ordenado decrescentemente: ");
     printf("Ordenado decrescentemente: ");
     buscaOrdenadores(vetor3Tam12,TAM_1,op,arq2);
     printf("\n");

     fprintf(arq2,"\n\t\t\tVETORES DE TAMANHO 10000\n");
     printf("\t\t\tVETORES DE TAMANHO 10000\n");
     fprintf(arq2,"\nNao ordenado: ");
     printf("\nNao ordenado: ");
     buscaOrdenadores(vetor1Tam22,TAM_2,op,arq2);
     fprintf(arq2,"Ordenado crescentemente: ");
     printf("Ordenado crescentemente: ");
     buscaOrdenadores(vetor2Tam22,TAM_2,op,arq2);
     fprintf(arq2,"Ordenado decrescentemente: ");
     printf("Ordenado decrescentemente: ");
     buscaOrdenadores(vetor3Tam22,TAM_2,op,arq2);
     printf("\n");

     fprintf(arq2,"\n\t\t\tVETORES DE TAMANHO 50000\n");
     printf("\t\t\tVETORES DE TAMANHO 50000\n");
     fprintf(arq2,"\nNao ordenado: ");
     printf("\nNao ordenado: ");
     buscaOrdenadores(vetor1Tam32,TAM_3,op,arq2);
     fprintf(arq2,"Ordenado crescentemente: ");
     printf("Ordenado crescentemente: ");
     buscaOrdenadores(vetor2Tam32,TAM_3,op,arq2);
     fprintf(arq2,"Ordenado decrescentemente: ");
     printf("Ordenado decrescentemente: ");
     buscaOrdenadores(vetor3Tam32,TAM_3,op,arq2);
     printf("\n");

     fprintf(arq2,"\n\t\t\tVETORES DE TAMANHO 100000\n");
     printf("\t\t\tVETORES DE TAMANHO 100000\n");
     fprintf(arq2,"\nNao ordenado: ");
     printf("\nNao ordenado: ");
     buscaOrdenadores(vetor1Tam42,TAM_4,op,arq2);
     fprintf(arq2,"Ordenado crescentemente: ");
     printf("Ordenado crescentemente: ");
     buscaOrdenadores(vetor2Tam42,TAM_4,op,arq2);
     fprintf(arq2,"Ordenado decrescentemente: ");
     printf("Ordenado decrescentemente: ");
     buscaOrdenadores(vetor3Tam42,TAM_4,op,arq2);
     printf("\n");

     fprintf(arq2,"\n\t\t\tVETORES DE TAMANHO 500000\n");
     printf("\t\t\tVETORES DE TAMANHO 500000\n");
     fprintf(arq2,"\nNao ordenado: ");
     printf("\nNao ordenado: ");
     buscaOrdenadores(vetor1Tam52,TAM_5,op,arq2);
     fprintf(arq2,"Ordenado crescentemente: ");
     printf("Ordenado crescentemente: ");
     buscaOrdenadores(vetor2Tam52,TAM_5,op,arq2);
     fprintf(arq2,"Ordenado decrescentemente: ");
     printf("Ordenado decrescentemente: ");
     buscaOrdenadores(vetor3Tam52,TAM_5,op,arq2);
     printf("\n");

     fprintf(arq2,"\n\t\t\tVETORES DE TAMANHO 1000000\n");
     printf("\t\t\tVETORES DE TAMANHO 1000000\n");
     fprintf(arq2,"\nNao ordenado: ");
     printf("\nNao ordenado: ");
     buscaOrdenadores(vetor1Tam62,TAM_6,op,arq2);
     fprintf(arq2,"Ordenado crescentemente: ");
     printf("Ordenado crescentemente: ");
     buscaOrdenadores(vetor2Tam62,TAM_6,op,arq2);
     fprintf(arq2,"Ordenado decrescentemente: ");
     printf("Ordenado decrescentemente: ");
     buscaOrdenadores(vetor3Tam62,TAM_6,op,arq2);
     printf("\n");
     printf("\t\t\t     FIM DA ANALISE\n");
     printf("\n");
     fprintf(arq2,"\n-------------------------------------------------------------------------");

    //Termina Vetores alocados
    terminaVetor(vetor1Tam12);
    terminaVetor(vetor2Tam12);
    terminaVetor(vetor3Tam12);

    terminaVetor(vetor1Tam22);
    terminaVetor(vetor2Tam22);
    terminaVetor(vetor3Tam22);

    terminaVetor(vetor1Tam32);
    terminaVetor(vetor2Tam32);
    terminaVetor(vetor3Tam32);

    terminaVetor(vetor1Tam42);
    terminaVetor(vetor2Tam42);
    terminaVetor(vetor3Tam42);

    terminaVetor(vetor1Tam52);
    terminaVetor(vetor2Tam52);
    terminaVetor(vetor3Tam52);

    terminaVetor(vetor1Tam62);
    terminaVetor(vetor2Tam62);
    terminaVetor(vetor3Tam62);
}

void menuOrdenadores(FILE *arq2) //Menu para escolha de um ordenador
{
    int op;
    do
    {
        system("cls");
        printf("\t\t\t\t   ORDENADORES\n\n");
        printf(" 1 - BubbleSort\n");
        printf(" 2 - SelectSort\n");
        printf(" 3 - InsertSort\n");
        printf(" 4 - ShellSort\n");
        printf(" 5 - HeapSort\n");
        printf(" 6 - QuickSort (Pivo = elemento do meio)\n");
        printf(" 7 - QuickSort (Pivo = numero de linhas de 3)\n");
        printf(" 8 - QuickSort (Pivo = segmento <= 20 usa InsertSort)\n");
        printf(" 9 - QuickSort (Sem Recursao)\n");
        printf("\n 0 - Voltar\n");

        printf("\nOpcao: ");
        scanf("%d",&op);

        //op=9; // RETIRAR
//do // RETIRAR
//{ // RETIRAR e DESCOMENTAR OS SYSTEM("PAUSE");
        switch(op)
        {
            case 1: //BubbleSort
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t\t\tBUBBLESORT\n\n");
                         fprintf(arq2,"\n>>\t\t\t\tBUBBLESORT\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 2: //SelectSort
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t\t\tSELECTSORT\n\n");
                         fprintf(arq2,"\n>>\t\t\t\tSELECTSORT\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 3: //InsertSort
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t\t\tINSERSORT\n\n");
                         fprintf(arq2,"\n>>\t\t\t\tINSERSORT\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 4: //ShellSort
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t\t\tSHELLSORT\n\n");
                         fprintf(arq2,"\n>>\t\t\t\tSHELLSORT\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 5: //HeapSort
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t\t\tHEAPSORT\n\n");
                         fprintf(arq2,"\n>>\t\t\t\tHEAPSORT\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 6: //QuickSort (Pivo = elemento do meio)
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t      QUICKSORT PIVO ELEMENTO DO MEIO\n\n");
                         fprintf(arq2,"\n>>\t\t      QUICKSORT PIVO ELEMENTO DO MEIO\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 7: //QuickSort (Pivo = numero de linhas de 3)
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t    QUICKSORT PIVO ELEMENTO NUMERO DE 3\n\n");
                         fprintf(arq2,"\n>>\t\t    QUICKSORT PIVO ELEMENTO NUMERO DE 3\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 8: //QuickSort (Pivo = segmento <= 20 * IsertSort)
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t  QUICKSORT PIVO SEGMENTO <= 20 C/ INSERTSORT\n\n");
                         fprintf(arq2,"\n>>\t\t  QUICKSORT PIVO SEGMENTO <= 20 C/ INSERTSORT\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                     system("pause");
                     break;
            case 9: //QuickSort (Sem Recursao)
                    system("cls");
                    if(vetoresCriados) //Somente se os vetores ja foram criados
                    {
                         printf("\t\t\t QUICKSORT SEM RECURSAO\n\n");
                         fprintf(arq2,"\n>>\t\t\t QUICKSORT SEM RECURSAO\n");
                         resultadoOrdenacao(op,arq2);
                    }
                    else
                        printf("\nVetores nao foram gerados\n\n");
                    system("pause");
                    break;
        }
     //  op--; // RETIRAR
//}while(op>=1); // RETIRAR
    }while(op);

}

item geraVetor(int tamanho,FILE *arq) //Gera e aloca memoria para vetor do tipo item... usado para o primeiro vetor aleatorio
{
    item vetor = (item)malloc(sizeof(tipo_item)*tamanho);
    int i;

    if(!vetor)
        return 0;

    srand(time(NULL)); // Zerar o time

    fprintf(arq,"\n\n>>Tamanho: %d\n\n",tamanho);
    for (i=0; i < tamanho; i++)
    {
        vetor[i].chave = (tipo_chave)rand();
        fprintf(arq,"%d ",vetor[i].chave);
    }
    return vetor;
}

item alocaVetor(int tamanho) // Aloca memoria para um vetor de tamanho n
{
    item vetor = (item)malloc(sizeof(tipo_item)*tamanho);
    if(!vetor)
        return NULL;
    return vetor;
}

void copiaVetor(item v1,item v2,int tamanho) //Faz uma copia de conteudo de 1 vetor
{
    int i;
    /*if(!v2)
        v2=alocaVetor(tamanho);
*/
    for (i=0; i < tamanho; i++)
    {
        v2[i].chave = v1[i].chave;
    }
}


void terminaVetor(item v) // Finaliza um vetor do tipo item
{
    free(v);
}

int imprimirVetor(item v, int tamanho) // Imprime um vetor do tipo item
{
    if (tamanho<=0)
        return 0;

    int i;
    printf("\n\n");
    for (i=0; i<tamanho; i++)
    {
        printf("%d\t",v[i].chave);
    }
    printf("\n\n");
    return 1;
}

double calculaTempo(double inicio, double fim) //Calcula o tempo com base nos tempos de inicio e fim de execucao
{
    return ((fim-inicio)/CLOCKS_PER_SEC); //obtem valor em segundos
}
