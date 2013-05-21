#ifndef FUNCOES_C_INCLUDED
#define FUNCOES_C_INCLUDED

#include "funcoes.h"



int contaLinhasArquivo()
{
    FILE *arquivo = fopen("documentos.txt", "r");  // abrir arquivo para leitura
    char ler[STR_TAMANHO];  // armazena as linhas
    int linhas;
    linhas = 0;

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            linhas++;
        }
    }else
    {
         fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    return linhas;  // Operaзгo bem sucedida
}

void pesquisarPalavras(tabela t)
{
    char palavra[TAMANHO_PALAVRA];
    char continua = 's';
    int i;
    while(continua != 'n')
    {
        printf("\nDigite uma palavra para a pesquisa: ");
        scanf("%s",palavra);
        tiraAcento(palavra);
            for(i = 0; i < strlen(palavra); i++)
                palavra[i] = tolower(palavra[i]); //Deixa toda a palavra minuscula

        pesquisaHash(t,palavra);
        printf("\n\nDeseja pesquisar mais alguma palavra ? (s/n) ");
        continua = getch();
        continua = tolower(continua);
    }
}

// Pega o que tem em CaminhoAtual -> envia para tokenizador de arquivo -> adiciona na hash
int tokenizarDiretorioHash(char caminhoAtual[], tabela t)
{
    // aloca memoria para a quantidade arquivos encontrada no diretorio documentos.txt
    lista_arquivos arquivos = (lista_arquivos)malloc(sizeof(tipo_arquivo)*contaLinhasArquivo());
    int indiceArquivos = 0; // ESTE Й O DOC_ID DE CADA DOCUMENTO

    FILE *arquivo = fopen("documentos.txt", "r");  // abrir arquivo para leitura
    char ler[STR_TAMANHO];  // armazena as linhas
    char caminhoAtualComArquivo[STR_TAMANHO]; // Armazena conteudo do caminhoAtual e futuramente + arquivo.txt

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            sprintf(arquivos[indiceArquivos].nome,"%s",ler); // arquivo[indice] recebe um nome de um arquivo

            memset(caminhoAtualComArquivo,'\0',strlen(caminhoAtualComArquivo)); // Limpando variavel
            sprintf(caminhoAtualComArquivo,"%s\\%s",caminhoAtual,ler); //caminho atual com arquivo recebe o diretorio atual + arquivo.txt

            int w;
            for(w=0;w<sizeof(caminhoAtualComArquivo);w++) //Inverte as barras
            {
                if(caminhoAtualComArquivo[w] == '\\')
                    caminhoAtualComArquivo[w] = '/';
            }
            //printf("\n\ncamAtualComArquivo: %s",caminhoAtualComArquivo);
            caminhoAtualComArquivo[strlen(caminhoAtualComArquivo)-1] = '\0'; // Codigo mais FDP do programa, finaliza string
            AbreArquivoTokenizandoHash(caminhoAtualComArquivo, indiceArquivos,t); //Tokeniza arquivo selecionado
            indiceArquivos++; // Proximo arquivo do documentos.txt
        }
    }else
    {
         fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    printf("Lista Invertida completa\n\n");
    return 1;  // Operaзгo bem sucedida
}

// Abre arquivos e os tokeniza -------------------------------------------------------------------------
int AbreArquivoTokenizandoHash(char nomeArquivo[], int doc_id, tabela t)
{
    //printf("\n\nnomeArquivo: %s",nomeArquivo);

    int i;
    //int temPalavra = 0;
    //Ler Palavra
    FILE *arquivo = NULL ;
    arquivo = fopen(nomeArquivo, "r"); // abrir arquivo para leitura

    char ler[STR_TAMANHO];  // armazena as linhas
    char *palavra; // Armazena palavra
    //char caracteres[] = " ,«.=-*/+_-!@#$%Ё&:;~}{()?\'[]№ў¬§°Є<>\\|'\n'\"^`"; // Caracteres invalios para palavra.
    char caracteres[] = "  '«'\015'\012'\040'\011'*}{+_/]['\\''\"''\'')(.-,!=|&@#?$%;:'\n''\0'«"; // Com octal funciona melhor

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            palavra = strtok(ler,caracteres);
            while(palavra!=NULL)
            {
                tiraAcento(palavra);
                for(i = 0; i < strlen(palavra); i++)
                    palavra[i] = tolower(palavra[i]); //Deixa toda a palavra minuscula

                //printf("Palavra enviada p/ hash: %s \n",palavra);
                //getchar();
                //Envia palavra para a tabela hash
                if(palavra != NULL && palavraValida(palavra)) // Se tiver palavra
                {
                    //printf("chamou insere tabela enviando %s\n",palavra);
                    insere_tabela(&t,palavra,doc_id);
                }

                palavra = strtok(NULL,caracteres);
            }
        }
    }else
    {
        // fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    return 1;  // Operaзгo bem sucedida
}

// Pega o que tem em CaminhoAtual -> envia para tokenizador de arquivo -> adiciona na hash
int tokenizarDiretorioB(char caminhoAtual[], TipoApontador *p)
{
    // aloca memoria para a quantidade arquivos encontrada no diretorio documentos.txt
    lista_arquivos arquivos = (lista_arquivos)malloc(sizeof(tipo_arquivo)*contaLinhasArquivo());
    int indiceArquivos = 0; // ESTE Й O DOC_ID DE CADA DOCUMENTO

    FILE *arquivo = fopen("documentos.txt", "r");  // abrir arquivo para leitura
    char ler[STR_TAMANHO];  // armazena as linhas
    char caminhoAtualComArquivo[STR_TAMANHO]; // Armazena conteudo do caminhoAtual e futuramente + arquivo.txt

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            sprintf(arquivos[indiceArquivos].nome,"%s",ler); // arquivo[indice] recebe um nome de um arquivo

            memset(caminhoAtualComArquivo,'\0',strlen(caminhoAtualComArquivo)); // Limpando variavel
            sprintf(caminhoAtualComArquivo,"%s\\%s",caminhoAtual,ler); //caminho atual com arquivo recebe o diretorio atual + arquivo.txt

            int w;
            for(w=0;w<sizeof(caminhoAtualComArquivo);w++) //Inverte as barras
            {
                if(caminhoAtualComArquivo[w] == '\\')
                    caminhoAtualComArquivo[w] = '/';
            }
            //printf("\n\ncamAtualComArquivo: %s",caminhoAtualComArquivo);
            caminhoAtualComArquivo[strlen(caminhoAtualComArquivo)-1] = '\0'; // Codigo mais FDP do programa, finaliza string
            AbreArquivoTokenizandoB(caminhoAtualComArquivo, indiceArquivos,p); //Tokeniza arquivo selecionado
            indiceArquivos++; // Proximo arquivo do documentos.txt
        }
    }else
    {
         fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    printf("Lista Invertida completa\n\n");
    return 1;  // Operaзгo bem sucedida
}

// Abre arquivos e os tokeniza -------------------------------------------------------------------------
int AbreArquivoTokenizandoB(char nomeArquivo[], int doc_id, TipoApontador *p)
{
    //printf("\n\nnomeArquivo: %s",nomeArquivo);

    TipoRegistro registro;
    int i;
    //int temPalavra = 0;
    //Ler Palavra
    FILE *arquivo = NULL ;
    arquivo = fopen(nomeArquivo, "r"); // abrir arquivo para leitura

    char ler[STR_TAMANHO];  // armazena as linhas
    char *palavra; // Armazena palavra
    //char caracteres[] = " ,«.=-*/+_-!@#$%Ё&:;~}{()?\'[]№ў¬§°Є<>\\|'\n'\"^`"; // Caracteres invalios para palavra.
    char caracteres[] = "  '«'\015'\012'\040'\011'*}{+_/]['\\''\"''\'')(.-,!=|&@#?$%;:'\n''\0'«"; // Com octal funciona melhor

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            palavra = strtok(ler,caracteres);
            while(palavra!=NULL)
            {
                tiraAcento(palavra);
                for(i = 0; i < strlen(palavra); i++)
                    palavra[i] = tolower(palavra[i]); //Deixa toda a palavra minuscula

                //printf("Palavra enviada p/ arvoreB: %s \n",palavra);
                //getchar();
                //Envia palavra para a arvoreB
                if(palavra != NULL && palavraValida(palavra)) // Se tiver palavra
                {
                    //printf("chamou insereB enviando %s\n",palavra);
                    strcpy(registro.Chave,palavra); // Copia a palavra para registro para enviar para ArvoreB
                    InsereB(registro,&(*p),doc_id);
                }

                palavra = strtok(NULL,caracteres);
            }
        }
    }else
    {
         //fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    return 1;  // Operaзгo bem sucedida
}

int tokenizarDiretorioAVL(char caminhoAtual[], avl_apontador *p)
{
    // aloca memoria para a quantidade arquivos encontrada no diretorio documentos.txt
    lista_arquivos arquivos = (lista_arquivos)malloc(sizeof(tipo_arquivo)*contaLinhasArquivo());
    int indiceArquivos = 0; // ESTE Й O DOC_ID DE CADA DOCUMENTO

    FILE *arquivo = fopen("documentos.txt", "r");  // abrir arquivo para leitura
    char ler[STR_TAMANHO];  // armazena as linhas
    char caminhoAtualComArquivo[STR_TAMANHO]; // Armazena conteudo do caminhoAtual e futuramente + arquivo.txt

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            sprintf(arquivos[indiceArquivos].nome,"%s",ler); // arquivo[indice] recebe um nome de um arquivo

            memset(caminhoAtualComArquivo,'\0',strlen(caminhoAtualComArquivo)); // Limpando variavel
            sprintf(caminhoAtualComArquivo,"%s\\%s",caminhoAtual,ler); //caminho atual com arquivo recebe o diretorio atual + arquivo.txt

            int w;
            for(w=0;w<sizeof(caminhoAtualComArquivo);w++) //Inverte as barras
            {
                if(caminhoAtualComArquivo[w] == '\\')
                    caminhoAtualComArquivo[w] = '/';
            }
            //printf("\n\ncamAtualComArquivo: %s",caminhoAtualComArquivo);
            caminhoAtualComArquivo[strlen(caminhoAtualComArquivo)-1] = '\0'; // Codigo mais FDP do programa, finaliza string
            AbreArquivoTokenizandoAVL(caminhoAtualComArquivo, indiceArquivos,p); //Tokeniza arquivo selecionado
            indiceArquivos++; // Proximo arquivo do documentos.txt
        }
    }else
    {
         fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    printf("Lista Invertida completa\n\n");
    return 1;  // Operaзгo bem sucedida
}

// Abre arquivos e os tokeniza -------------------------------------------------------------------------
int AbreArquivoTokenizandoAVL(char nomeArquivo[], int doc_id, avl_apontador *p)
{
    //printf("\n\nnomeArquivo: %s",nomeArquivo);

    tipo_elemento_avl registro;
    int i;
    //int temPalavra = 0;
    //Ler Palavra
    FILE *arquivo = NULL ;
    arquivo = fopen(nomeArquivo, "r"); // abrir arquivo para leitura

    char ler[STR_TAMANHO];  // armazena as linhas
    char *palavra; // Armazena palavra
    //char caracteres[] = " ,«.=-*/+_-!@#$%Ё&:;~}{()?\'[]№ў¬§°Є<>\\|'\n'\"^`"; // Caracteres invalios para palavra.
    char caracteres[] = "  '«'\015'\012'\040'\011'*}{+_/]['\\''\"''\'')(.-,!=|&@#?$%;:'\n''\0'«"; // Com octal funciona melhor

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            palavra = strtok(ler,caracteres);
            while(palavra!=NULL)
            {
                tiraAcento(palavra);
                for(i = 0; i < strlen(palavra); i++)
                    palavra[i] = tolower(palavra[i]); //Deixa toda a palavra minuscula

                //printf("Palavra enviada p/ arvoreB: %s \n",palavra);
                //getchar();
                //Envia palavra para a arvoreB
                if(palavra != NULL && palavraValida(palavra))// Se tiver palavra
                {
                    //printf("chamou insereB enviando %s\n",palavra);
                    strcpy(registro.chave,palavra); // Copia a palavra para registro para enviar para ArvoreB
                    insereAVL(&(*p),registro,doc_id);
                }

                palavra = strtok(NULL,caracteres);
            }
        }
    }else
    {
         //fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    return 1;  // Operaзгo bem sucedida
}


void pesquisarPalavrasB(TipoApontador p)
{
    char palavra[TAMANHO_PALAVRA];
    char continua = 's';
    TipoRegistro registro;
    int i;
    while(continua != 'n')
    {
        printf("\nDigite uma palavra para a pesquisa: ");
        scanf("%s",palavra);
        tiraAcento(palavra);
        for(i = 0; i < strlen(palavra); i++)
            palavra[i] = tolower(palavra[i]); //Deixa toda a palavra minuscula

        strcpy(registro.Chave, palavra);
        TipoRegistro *verifica = Pesquisa(registro, p);
        if (verifica != NULL)
            imprimeConteudoB(*verifica);

        printf("\n\nDeseja pesquisar mais alguma palavra ? (s/n) ");
        continua = getch();
        continua = tolower(continua);
    }
}

void pesquisarPalavrasAVL(avl_apontador p)
{
    char palavra[TAMANHO_PALAVRA];
    char continua = 's';
    int i;
    while(continua != 'n')
    {
        printf("\nDigite uma palavra para a pesquisa: ");
        scanf("%s",palavra);
        tiraAcento(palavra);
        for(i = 0; i < strlen(palavra); i++)
            palavra[i] = tolower(palavra[i]); //Deixa toda a palavra minuscula

        pesquisaArvoreAVL(p,palavra);

        printf("\n\nDeseja pesquisar mais alguma palavra ? (s/n) ");
        continua = getch();
        continua = tolower(continua);
    }
}

//Carrega diretуrio e lista em um arquivo todos os arquivos .txt -------------------------------------------
int carregarDiretorio(char diretorio[])
{
    char comando[100];
    sprintf(comando,"dir /B %s\\*.txt > documentos.txt",diretorio);
    //printf("\n%s\n",&comando);
    system(comando);
    return 0;
}

// Função para imprimir conteudo de um arquivo na tela ------------------------------------------------------
int imprimirArquivo(char nomeArquivo[])
{
    // Ler o Arquivo
    int doc_id = 1;

    FILE *arquivo = fopen(nomeArquivo, "r");  // abrir arquivo para leitura
    char ler[STR_TAMANHO];  // armazena as linhas

    printf("DOC_ID \t Documento\n\n");

    if(arquivo != NULL)
    {
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {
            printf("%d \t %s",doc_id, ler);
            doc_id++;
        }
    }else
    {
         fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo
    }
    fclose(arquivo);
    return 1;  // Operaзгo bem sucedida

}

void tiraAcento(char* palavra)
{
    int i;
    for(i=0;i<strlen(palavra);i++)
        switch(palavra[i])
        {
                case 'á':
                case 'Á':
                case 'à':
                case 'À':
                case 'ã':
                case 'Ã':
                case 'â':
                case 'Â':
                    palavra[i] = 'a';
                    break;

                case 'é':
                case 'É':
                case 'ê':
                case 'Ê':
                    palavra[i] = 'e';
                    break;

                case 'í':
                case 'Í':
                    palavra[i] = 'i';
                    break;

                case 'ó':
                case 'Ó':
                case 'ô':
                case 'Ô':
                    palavra[i] = 'o';
                    break;

                case 'ú':
                case 'Ú':
                    palavra[i] = 'u';
                    break;
                case 'ç':
                    palavra[i] = 'c';
                    break;
        }
}

int palavraValida(char* palavra)
{
    if (palavra[0] >= 48 && palavra[0] <= 57){
        return 0; //não é valida
    }
    return 1;
}

#endif // FUNCOES_C_INCLUDED
