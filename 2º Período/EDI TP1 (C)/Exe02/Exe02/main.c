#include <stdio.h>
#include <stdlib.h>

#include "esparsa.h"

#define MAX_TAM 255

int main()
{
    system("title Trabalho de Estrutura de Dados I");
    system("color 0F");
	system("chcp 1252 > chcp.txt");
	system("cls");
	
	

    listaMatriz *mA, *mB, *mC;
    listaMatriz *matSoma, *matMult;
    
    int op,ok = 0;
    char nome[MAX_TAM];
    
    while(op != 6)
    {
        printf("\t\tExercicio 02");
        printf("\n\n\n");
    	printf("    1 - Abre Matriz\n");
    	printf("    2 - Imprimi Matriz\n");
    	printf("    3 - Soma Matriz\n");
    	printf("    4 - Multiplica Matriz\n");
    	printf("    5 - Apaga Matriz\n");
    	printf("    6 - Sair\n\n");
    	printf("Opção: ");
    	scanf("%d",&op);
	switch (op)
        {
               case 1 : system("cls");
                        printf("Forneça o Nome do 1º Arquivo:\n");
                   	    scanf("%s",&nome);    
                        mA = lerMatriz(nome); 
                        printf("Forneça o Nome do 2º Arquivo:\n");
                   	    scanf("%s",&nome);   
                        mB = lerMatriz(nome); 
                        system("PAUSE");
                        ok = 1;
                        break;
               
        
                        
               case 2 : system("cls");
                        if(!ok)
                        {
                            printf("Matrizes Nao Inicializadas Corretamente\n\n");
                            system("PAUSE");
                            break;
                           
                        }
                        else
                        {
                            printf("Matriz 1\n");
                            imprimeMatriz(mA);
                            printf("\nMatriz 2\n");
                            imprimeMatriz(mB);
                           
                            system("PAUSE");
                            break;
                        }
                       
                        
               case 3 : system("cls");
                        if(!ok)
                        {
                            printf("Matrizes Nao Inicializadas Corretamente\n\n");
                            system("PAUSE");
                            break;
                           
                        }
                        else
                        {
                            printf("Soma da Matriz 1 Com a Matriz 2\n\n"); 
                            printf("Matriz 1\n");
                            imprimeMatriz(mA);
                            printf("\n");
                            printf("Matriz 2\n");
                            imprimeMatriz(mB);
                            printf("\n");
                            printf("Resultado\n");
                            matSoma = somaMatriz(mA, mB);
                            imprimeMatriz(matSoma);
                            
                            system("PAUSE");
                            break;
                        }
                        
               case 4 : system("cls");
                        if(!ok)
                        {
                            printf("Matrizes Nao Inicializadas Corretamente\n\n");
                            system("PAUSE");
                            break;
                           
                        }
                        else
                        {
                            printf("Multiplicação da Matriz 1 Com a Matriz 2\n\n"); 
                            printf("Matriz 1\n");
                            imprimeMatriz(mA);
                            printf("\n");
                            printf("Matriz 2\n");
                            imprimeMatriz(mB);
                            printf("\n");
                            printf("Resultado\n");
                            matMult = multiplicaMatriz(mA,mB);
                            imprimeMatriz(matMult);
        
                            system("PAUSE");
                            break;
                        }
                        
               case 5 : system("cls");
                        if(!ok)
                        {
                            printf("Matrizes Nao Inicializadas Corretamente\n\n");
                            system("PAUSE");
                            break;
                           
                        }
                        else
                        {
                        if(apagaMatriz(mA))
                           printf("Matriz 1 Apagada Com Sucesso!");
                        else
                           printf("Erro, Nao Existe Matriz a Ser apagada.");
                        if(apagaMatriz(mB))  
                           printf("\nMatriz 2 Apagada Com Sucesso!\n\n");
                        else
                           printf("\nErro, Nao Existe Matriz a Ser apagada.\n\n");    
                        system("PAUSE");
                        break;       
                        }
        }
        system("cls");
    }
    

    system("PAUSE");
    return 0;
}
