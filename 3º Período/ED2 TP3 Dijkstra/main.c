#include "TAD_grafo.h"

int main()
{
	grafo g;
	cria(&g);
	
	FILE *arq;
	
	char origem[100], destino [100], aux[100], palavra[100];
	char ch;
	
	int i=0, j=0;
	int dist=0, codOrigem, codDestino;
	int menor=0;

	printf("Abrindo arquivo 'cidades.txt'...\n");
	arq = fopen("cidades.txt", "r");
	if(!arq)
		printf("Arquivo não carregado.");
	else{
		palavra[i] = getc(arq);
		while(palavra[i] != EOF){
			//Primeiro token
			while(palavra[i]!= '#' && palavra[i] != EOF){
				i++;
				palavra[i] = getc(arq);
			} 
			palavra[i]= '\0';
			strcpy(origem, palavra);

			i = 0;

			if(insere_vertice(g, origem, &codOrigem) == 1)
				printf("\nInserindo vértice '%s'.", origem);
 
			palavra[i]= getc(arq);
		
			//Segundo token
			while(palavra[i]!= '#' && palavra[i] != EOF){
				i++;
				palavra[i] = getc(arq);
			}

			palavra[i]= '\0';
			strcpy(destino, palavra);
			i = 0;
			if(insere_vertice(g, destino, &codDestino) == 1)
				printf("\nInserindo vértice '%s'.", destino);

			aux[i] = getc(arq);
			
			//Terceiro token
			while(aux[i] != '\n' && aux[i] != EOF){
				i++;
				aux[i] = getc(arq);
			}

			aux[i] = '\0';
			i = 0;
			palavra[i] = getc(arq);
			dist = atoi(aux);
			insere_aresta(g, codOrigem, codDestino, dist);
		}
	}

	printf("\n");
	int medias[g->num_vertices];//Vetor de médias

	//Contando a média das distâncias
	for (i=0; i < g->num_vertices; i++) {
		medias[i] = dijkstra(g,i);
		if (medias[i] < menor || menor == 0)
			menor = medias[i];
	}
	for (i=0; i < g->num_vertices; i++)
		printf("\nDistância média de %s: %d", g->vertices[i].nomeCidade, medias[i]); 
	for (i=0; i < g->num_vertices; i++)
		if (medias[i] == menor)//Menor distância
			printf("\n\nMenor distância média: %s\n\n", g->vertices[i].nomeCidade);   

	close(arq);
	termina(&g);
	return 1;
}
