#include <stdio.h>
#include <stdlib.h>
#include "TAD/pilha.h"
#include <string.h>
#include "conio.h"

#define TAM_NOME_ARQ 30  // Definição de tamanho máximo para nome de arquivo
#define ENTER 13
#define TAM_TAG 50   // Define tamanho máximo para cada TAG 

int imprimirArquivo(char nomeArquivo[]); // Imprime conteudo de arquivo
int verificaArquivoXML(char nomeArquivo[]);

int main()
{
    
    char arquivo[TAM_NOME_ARQ],tecla;  
    FILE *arquivoEmDisco = NULL; // Verificará se há algum arquivo já aberto
    int op = -1;
    
    window(1,1,20,20);
    
    system("color 0F");
    // While para MENU PRINCIPAL 
    while(op != 4)
    {
        system("cls");    
        printf("\n 1 - Abrir arquivo\n\n");
        printf(" 2 - Ler arquivo aberto\n\n");
        printf(" 3 - Verificar consistencia de arquivo XML\n\n");
        printf(" 4 - Sair\n\n");
        printf(" Opcao: ");
        scanf("%d",&op);
              
        switch (op)
        {
               case 1 : system("cls");
                        printf("Nome do arquivo a ser aberto: ");
                        scanf("%s",arquivo);
                        arquivoEmDisco = fopen(arquivo,"r");
                        if (!arquivoEmDisco)
                        {
                          printf("Problema na abertura do arquivo.\n");
                          arquivoEmDisco = NULL;                                
                        }else
                          printf("Arquivo aberto com sucesso.\n");
                        printf("\nPressione ENTER para continuar.\n");
                        tecla = getch();
                        while(tecla != ENTER)
                           tecla = getch(); 
                        break;
                        
               case 2 : system("cls");
                        if (!arquivoEmDisco)
                           printf("Nenhum arquivo aberto em disco.\n");        
                        else
                        {
                           imprimirArquivo(arquivo);
                           printf("\n\n\n\t\t\t\t== FIM DO ARQUIVO ==\n"); 
                        }
                        printf("\nPressione ENTER para continuar.\n");
                        tecla = getch();
                        while(tecla != ENTER)
                           tecla = getch();
                        break; 
                           
               case 3 : system("cls");
                        if (!arquivoEmDisco)
                           printf("Nenhum arquivo aberto em disco.\n");        
                        else
                        {
                           verificaArquivoXML(arquivo);
                           //printf("\n\n\n\t\t\t\t== FIM DO ARQUIVO ==\n"); 
                        }    
                        printf("\nPressione ENTER para continuar.\n");
                        tecla = getch();
                        while(tecla != ENTER)
                           tecla = getch();
                        break;                         
        }
        
        // Caso exista um arquivo carregado, isto irá fecha-lo
        if(arquivoEmDisco)       
           fclose(arquivoEmDisco);

    }	
  return 0;
}

// Função para imprimir conteudo de um arquivo na tela -------------------------
int imprimirArquivo(char nomeArquivo[])  
{  
    // Ler o Arquivo  
    const int STR_TAMANHO = 255;  // Tamanho max para linha
    int linha = 1; // Total de Linhas
  
    FILE *arquivo = fopen(nomeArquivo, "r");  // abrir arquivo para leitura
    char ler[STR_TAMANHO];  // armazena as linhas
  
    if(arquivo != NULL)  
    {  
        while(fgets(ler, STR_TAMANHO, arquivo))  // Armazena em ler as linhas do arquivo aberto
        {  
            printf("%d: %s",linha, ler);  
            linha++;
        }  
    }else
    {
         fclose(arquivo);
         return 0; // Se deu erro ao abrir arquivo  
    }        
    fclose(arquivo);  
    return 1;  // Operação bem sucedida
  
}  

int verificaArquivoXML(char nomeArquivo[])
{   
    const int STR_TAMANHO = 255; // Tamanho max da linha
    tipo_item tag;  // Armazenará a tag a ser enviada a pilha
    tipo_item tagPop; // Armazenará a tag retirada da pilha
   
    int i=0,k=0;
    int fimDaTag = 0; // Verifica fim de tag para não pegar os parametros do codigo
    int fimDaLinha = 0; // Verifica se chegou no final da linha atual
    int push_pop = 0; // Armazena ação para pilha, 1 para push 2 para pop.
    int barrado = 0; // Se a tag possui barra;
    int primeiraLinha = 1; // Verifica se é a primeira linha, ou seja o ?xml
    int erros = 0; // Contador para erros.
    int linha = 1; // total de linhas 
    int encontrouFechado = 0; // Verifica se ao abrir tag encontrou um fechado
    int tagAberta = 0;  // Verifica se ao fechar tag, possui um aberto
    
    FILE *arquivo = fopen(nomeArquivo, "r"); // Abrir arquivo para leitura  
    char ler[STR_TAMANHO]; // Armazena conteudo de linha 
    
    //------ PILHA
    pilha p;   
    cria_pilha(&p);
    //------------
    
    if(arquivo != NULL)  
    {  
        while(fgets(ler, STR_TAMANHO, arquivo))  
        {  
            i=0;
            k=0;
            tagAberta = 0;
            encontrouFechado = 0;
            barrado=0;
            fimDaTag = 0;            // Reinicia variaveis 
            fimDaLinha = 0; 
            memset(tag.chave,'\0',TAM_TAG);  // Limpa variavel tag.
            memset(tagPop.chave,'\0',TAM_TAG);  // Limpa variavel tag.
            while(!fimDaLinha)
            { 
              push_pop = 0;  // Inicializa o push_pop para não fazer nada caso n haja tag                                            
              if( ler[i] == '<' ) // Abriu tag
              {
                  tagAberta =1;
                  push_pop = 0; // Inicializa o push_pop para não fazer nada caso n haja tag        
                   if(primeiraLinha) // Verifica o cabeçalho no formato <?xml ?>
                   {
                        if(ler[i+1] == '?' && ler[i+2] == 'x' && ler[i+3] == 'm' &&
                         ler[i+4] == 'l')
                        {
                            i+=5;
                            while (ler[i]!='?' && ler[i+1]!='\n')
                                i++;
                            if (!(ler[i]=='?' && ler[i+1]=='>')) //nao tem ? ou >
                            {
                                printf("Erro no cabecalho do xml");
                                erros++;
                                primeiraLinha = 0;
                            }else
                            {
                                //printf("Nao tem erro no cabecalho do xml");
                                primeiraLinha = 0;
                                encontrouFechado = 1; // consta que a tag aberta foi fechada
                            }
                        } 
                        else
                        {
                            erros++;
                            printf("Erro no cabecalho do xml");                            
                            primeiraLinha = 0;
                        }                        
                   }                        
                   else // Saiu do Cabeçalho
                  while(ler[i] != '>' && !fimDaLinha && !primeiraLinha) // Inicia verificação de tags
                  {
                      i++;
                      if(ler[i] == '>')
                         encontrouFechado=1; // consta que a tag aberta foi fechada
                      if(ler[i] == ' ')
                           fimDaTag = 1; // Para não armazenar o que tiver apos o espaço da tag
                      if(ler[i] != '>' && !fimDaTag)
                      {       
                         // Aqui se descobre o conteudo das tags já filtradas                                 
                         if(ler[i] == '/') 
                         {
                            barrado = 1;  // Verifica se será uma tag barrada 
                         }
                         else
                         {
                            tag.chave[k] = ler[i]; // Armazenando tags , sem /, na variavel tag 
                            k++;                           
                         }
                         if(barrado) // Descide ação da pilha com base no barrado
                           push_pop = 2;
                         else
                           push_pop = 1;
                            
                      }
                      else
                      { 
                          k = 0; // Reinicia variavel para adicionar tag em tag.chave                                              
                      }
                                           
                      if(i==strlen(ler)) // Verifica Fim da linha
                         fimDaLinha = 1;
                  }
                  fimDaTag = 0;   // Reinicia fim da tag   
                  if(!encontrouFechado)
                  {
                     erros++;
                     printf("\nTag aberta na linha %d, mas nao fechada", linha);
                  }                          
              }
              else
              {   
                  if(!tagAberta && ler[i] == '>')
                  {
                    erros++;            
                    printf("\nTag fechada na linha %d, mas nao aberta", linha); 
                  }                                           
                  i++;  //Incrementa i para verificar proximo caracter da linha                        
              }           
                  switch (push_pop) // Empilha e desempilha
                  {
                         case 1: if(!pilha_cheia(p))
                                 {
                                      push(&p,tag); 
                                 //Descomentar caso queira ver o que esta sendo empilhado
                                     // printf("\nEmpilhou %s",tag.chave);                  
                                 }else
                                 {
                                      printf("\nErro !!!Tentativa de empilhar com Pilha Cheia");
                                      //erros++; // Comentado pois não consiste em erro 
                                 }
                                 break;
                         case 2: if(!pilha_vazia(p))
                                 {
                                      pop(&p,&tagPop);
                                 //Descomentar caso queira ver o que esta sendo desempilhado     
                                     // printf("\nDesempilhou %s",tagPop.chave);
                                      if (strcmp(tagPop.chave, tag.chave))
                                      {
                                        printf("\nTag '%s'(linha:%d) inconsistente com a tag '%s' retirada da pilha",tag.chave,linha,tagPop.chave);
                                        erros++;
                                      }
                                      
                                 }else
                                 {
                                      printf("\nErro !!!Tentativa de desempilhar com Pilha Vazia");
                                      erros++;
                                 }
                                 break;
                  }                                
              if(i==strlen(ler))//Verifica se chegou ao fim de linha 
                fimDaLinha = 1;
           }            
           linha++; // Armazena linha verificada.                        
        }
        if(!pilha_vazia(p)) // Caso ao fim do arquivo ainda haja itens empilhados
        {
              printf("\nPilha nao esta vazia!!! Existem Tags abertas ");
              erros++;
        }
        printf("\n\nErros: %d\n",erros);
        if(!erros)
           printf("\n\t\t ARQUIVO CONSISTENTE\n\n\n\n\n\n\n ");
        else
           printf("\n\n\t\t ARQUIVO INCONSISTENTE\n\n\n\n\n\n\n ");
        //printf("\nTamanho da pilha> %d",p.tamanho);  
    }
    else
    {
         fclose(arquivo); 
         return 0;   // Se deu erro ao abrir arquivo  
    } 
           
    fclose(arquivo);
    //----- TERMINA PILHA
    termina(&p); 
    //-------------------
    return 1;  // Operação bem sucedida
  
} 





