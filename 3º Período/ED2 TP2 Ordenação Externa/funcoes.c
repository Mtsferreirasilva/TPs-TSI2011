
#include "funcoes.h"

void gerarArquivo(int n){

    srand ( time(NULL) );

    FILE *arqDes;
    arqDes = fopen("arqDesordenado.txt","w");

    if(!arqDes)
        return;

    int i;

    for(i = 1; i<=n ; i++)
    {
        int c = rand()%100;
        fprintf(arqDes,"%d ",c);
        if(i % TAM_RUN == 0) // Cada linha representa uma Run.
             fprintf(arqDes,"\n");
    }
    fclose(arqDes);
}

void ordenacaoExterna(int numerosArmazenados){

   /* FILE *arqOrdenado;
    arqOrdenado = fopen("arqOrdenado.txt", "r"); //arquivo a ser ordenado*/
    int i = 0;
    int w = 0;
    int z = 0;
    fila fp; // Fila de prioridade
    int *bs; // Buffer de saida
    tipo_buffer *be; // Buffer de entrada
    tipo_nodo aux,auxRetirada;
    int numeroRuns = numerosArmazenados/TAM_RUN; // Runs geradas
    int inserirBufferEntrada;

    if(numerosArmazenados%TAM_RUN > 0) // Se  teve resto tem que gerar mais uma Run pro resto
        numeroRuns++;

    printf("\nQtd de Runs(50 chaves): %d",numeroRuns);

    gerar_runs(numeroRuns,numerosArmazenados);

    //Alocando memoria para os buffers
    bs = (int*)malloc(sizeof(int)*numeroRuns);
    be = (tipo_buffer*)malloc(sizeof(tipo_buffer)*numeroRuns);

    //Criando fila de prioridade
    fp = cria_fila(numeroRuns);

    //---------------------------------ADICIONAR ELEMENTOS NO BUFFER DE ENTRADA
    printf("\n\n2 - Adicionando elementos no buffer de entrada");
    for (i=0;i<numeroRuns;i++){

        be[i].posAtual=0; /* Somente para armazenar o posição corrente do arquivo.
                                Para quando pegar novamente mais um elemento pegar na posição atual */

        //Total de elementos que este buffer podera pegar da RUN
       // if( (i < numeroRuns || numeroRuns == 1) && numerosArmazenados >= 50 )
        if(i!=numeroRuns-1 || (numerosArmazenados % TAM_RUN) == 0)
            be[i].totalElementos = TAM_RUN; // Run completa
        else
            be[i].totalElementos = numerosArmazenados % TAM_RUN; // Run com menos de TAM_RUM

        //Carregando os buffers de entrada e inserindo os itens de cada Run
        inserirBufferEntrada = inserirElementosBufferEntrada(be,i);
        if (!inserirBufferEntrada){
            be[i].posAtualBuffer=-1;
        }else {
            aux.chave = be[i].chave[0];
            aux.run = i;
            be[i].posAtualBuffer++;
            //printf("\nRecebendo aux.chave %d aux.run %d",aux.chave,aux.run);
            insere_fila(fp,aux,numeroRuns); // Coloca na fila o elemento de indice 0 do buffer de entrada
        }
    }

    //-----------------------------------INICIO DA ORDENAÇÃO EXTERNA
    printf("\n\n3 - Realizando ordenação externa");
    w = 0;
    while (fila_vazia(fp)){
        imprime_fila(fp);
        remove_fila(fp,&auxRetirada);
        printf("\nElemento retirado = %d do Buffer de Entrada %d ",auxRetirada.chave,auxRetirada.run);
        bs[w]=auxRetirada.chave;
        w++;

        //verifica se o buffer de saida esta cheio e imprime no arquivo resultado
        if (w==numeroRuns){
            gravar_resultado(bs,w);
            w=0;
        }

        z=0;
        while (z<numeroRuns){
            if (z==auxRetirada.run){
                if (be[z].posAtualBuffer==TAM_BUFFER)
                    if (!carregaBE(auxRetirada.run,be)){
                        be[z].posAtualBuffer=-1;
                        printf("\nBuffer de entrada %d foi carregado!",auxRetirada.run);
                        break;
                    }
                if (be[z].posAtualBuffer < be[z].totalBuffer){
                    auxRetirada.run=z;
                    auxRetirada.chave=be[z].chave[be[z].posAtualBuffer];
                    insere_fila(fp,auxRetirada,numeroRuns);
                    be[z].posAtualBuffer++;
                    printf("\nElemento inserido = %d no Buffer de Entrada %d ",auxRetirada.chave,auxRetirada.run);
                }
                break;
            }
            z++;
        }// fim while

        //getchar();
    }

    //verifica se o buffer de saida possui algum elemento restante e salva no arquivo resultado
    if (w!=0)
        gravar_resultado(bs,w);

//---------------------------------------------------
    imprime_fila(fp);

    //Finalizando a fila de prioridade
    termina_fila(fp);

    printf("\n\Final da Ordenacao Externa");

    //fclose(arqOrdenado);
}

int carregaBE(int run, tipo_buffer *be){
    char nomeArquivo[50];
    int percorre,chave,i;
    FILE *arqTemp;

    sprintf(nomeArquivo,"temps/run%d.txt",run);
    arqTemp = fopen(nomeArquivo,"r");

    if (!arqTemp){
        return 0;
    }

    percorre=0;

    //Percorre até o ultimo
    while (percorre < be[run].posAtual){
        fscanf (arqTemp,"%d",&chave);
        percorre++;
    }

    i=0;
    while (i<TAM_BUFFER)//recarrega be
    {
        if (be[run].totalElementos==be[run].posAtual) // verifica se é possivel adicionar
            break;
        fscanf (arqTemp,"%d",&chave);
        be[run].chave[i]=chave;
        be[run].posAtual++;
        i++;
    }

    be[run].posAtualBuffer=0;
    be[run].totalBuffer=i;

    if (i==0)
        return 0;


    fclose(arqTemp);
    return 1;
}

int gravar_resultado(int *bs,int tamanho){
    FILE *arqOrdenado;
    int i;
    char caracter;
    arqOrdenado=fopen("arqOrdenado.txt","a+");
    if (!arqOrdenado)
        return 0;

    caracter=getc(arqOrdenado);
    while (caracter!=EOF){
        caracter=getc(arqOrdenado);
    }

    for (i=0;i<tamanho;i++){
        fprintf(arqOrdenado,"%d ",bs[i]);
    }
    fclose(arqOrdenado);
    return 1;
}

int inserirElementosBufferEntrada(tipo_buffer *be,int runAtual){

    FILE *arqTemp;
    char nomeRun[50];
    int i = 0;
    int k = 0;
    int elemento;

    sprintf(nomeRun,"temps/run%d.txt",runAtual); // Pega nome da RUN atual
    arqTemp = fopen(nomeRun,"r"); // Abre a run para ler dados


    while ( i < be[runAtual].posAtual ){
        fscanf (arqTemp,"%d",&elemento);
        printf("\n\nElemento - %d ",elemento);
        i++;
    }

    while ( k < TAM_BUFFER ){
        if(be[runAtual].totalElementos == be[runAtual].posAtual){// Está preenchido completamente.
            break;
        }
        fscanf (arqTemp,"%d",&elemento);
        be[runAtual].chave[k] = elemento;
        be[runAtual].posAtual++;
        k++;
    }

    be[runAtual].posAtualBuffer = 0;
    be[runAtual].totalBuffer = k;

    if (k==0){
        printf("\nBuffer não foi preenchido %d", runAtual);
        return 0;
    }
    else {
        printf("\n\tBuffer %d: ", runAtual);
        for(k = 0; k < be[runAtual].totalBuffer; k++){
            printf("%d ", be[runAtual].chave[k]);
        }
    }

    fclose(arqTemp);
    return 1;

}

void gerar_runs(int numeroRuns,int numerosArmazenados){
    FILE *arqDes;
    FILE *arqTemp;

    char nomeRun[50];
    int i,k;
    int vetorDaRun[TAM_RUN];
    int resto = numerosArmazenados % TAM_RUN;

    arqDes = fopen("arqDesordenado.txt", "r"); //arquivo a ser ordenado

    if (!arqDes){
      return;
    }

    //1 PASSO - Criando os arquivos temporarios adicionando ordenado.------------------
    printf("\n\n1 - Criando os arquivos temporarios adicionando ordenado.");
    for(i=0 ; i<numeroRuns ;i++){

        sprintf(nomeRun,"temps/run%d.txt",i); // cria nome do arquivo temp

        arqTemp = fopen(nomeRun,"w");
//Criação das runs antigo, gera erro.
/*
        // Pega as chaves e armazena no vetor
        if( (i < numeroRuns ||  numeroRuns == 1) && numerosArmazenados >= 50 ){
            for(k=0; k<TAM_RUN ;k++)
                fscanf(arqDes, "%d", &vetorDaRun[k]);
          //  printf("Numero Run: %d I: %d",numeroRuns , i);
        }else{
            k = 0;
            while(k < numerosArmazenados % TAM_RUN){
                fscanf(arqDes, "%d", &vetorDaRun[k]);
                //printf("\nValor Vetor[%d]: %d",k,vetorDaRun[k]);
                k++;
            }
        }

        //Ordena de acordo com o tamanho do vetor
        if( (i < numeroRuns ||  numeroRuns == 1) && numerosArmazenados >= 50 )
            quickSort(vetorDaRun,TAM_RUN);
        else
             quickSort(vetorDaRun,numerosArmazenados % TAM_RUN);

        // grava no arquivo temporario -----
         if(  (i < numeroRuns ||  numeroRuns == 1) && numerosArmazenados >= 50  ){
            for(k=0; k<TAM_RUN ;k++)
                fprintf(arqTemp,"%d ", vetorDaRun[k]);
        }else{
            k = 0;
            while(k < numerosArmazenados % TAM_RUN){
                fprintf(arqTemp,"%d ", vetorDaRun[k]);
                //printf("\nValor Vetor Temp[%d]: %d",k,vetorDaRun[k]);
                k++;
            }
        }
*/
         if (i<numeroRuns-1 || resto == 0){ // Sem o RESTO valores que sao divisores por TAM_RUN a ultima run fica em branco.
            for (k=0;k<TAM_RUN;k++){
                fscanf (arqDes,"%d",&vetorDaRun[k]);
                //printf("%d  ",numero);
            }
            quickSort(vetorDaRun,TAM_RUN);
            for (k=0;k<TAM_RUN;k++)
                fprintf(arqTemp,"%d ",vetorDaRun[k]);
        }
        else{
            //printf("Entrou ELSE");
            for (k=0;k<resto;k++){
                fscanf (arqDes,"%d",&vetorDaRun[k]);
            }
            quickSort(vetorDaRun,resto);
            for (k=0;k<resto;k++)
                fprintf(arqTemp,"%d ",vetorDaRun[k]);
        }
        fprintf(arqTemp,"\n");

        fclose(arqTemp);
    }

    printf("\n * Arquivos temporarios criados.");

    fclose(arqDes);
}

