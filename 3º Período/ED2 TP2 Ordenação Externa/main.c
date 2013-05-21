#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
    //Limpa arquivo de resultado criando ele.s
    FILE *arqOrd = fopen("arqOrdenado.txt","w");
    fclose(arqOrd);

    int numerosArmazenados,deletarRuns = 0;
    printf("Digite a quantidade de numeros para ordenar: ");
    scanf("%d",&numerosArmazenados);

    gerarArquivo(numerosArmazenados);
    ordenacaoExterna(numerosArmazenados);

    printf("\n\nDeletar arquivos temporarios gerados ? (1-Sim / 0-Nao): ");
    scanf("%d",&deletarRuns);
    if(deletarRuns)
        system("del temps\\*.txt");

    return 0;
}
