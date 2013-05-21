#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MEMBRO 1
#define NAOMEMBRO 0
#define INFINITO 100000

enum tipo_status {espera, pronto, processado};

typedef int tipo_chave;

typedef int tipo_peso;

typedef struct
{
    tipo_chave chave;
    char nomeCidade[50];
    enum tipo_status status;
}
tipo_elemento;

typedef  struct
{
    int conectado;
    tipo_peso peso;
    enum tipo_status status;
}
tipo_aresta;

struct tipo_grafo
{
    tipo_elemento vertices[MAX];
    tipo_aresta arestas[MAX][MAX];
    int num_vertices;
};

typedef struct tipo_grafo *grafo;

int cria(grafo *g);

int termina(grafo *g);

int busca_vertice(grafo g, char cidade[]);

int insere_vertice(grafo g, char cidade[], int *cod);

int insere_aresta(grafo g,tipo_chave ch1,tipo_chave ch2,tipo_peso peso);

int djkstra(grafo g, tipo_chave origem);

int cria(grafo *g)
{
    int i, j;
    
    if(!(*g = (grafo)malloc(sizeof(struct tipo_grafo))))
        return 0;
    (*g)->num_vertices = 0;
    
    for(i = 0; i < MAX; i++)
        for(j = 0; j < MAX; j++)
        {
            (*g)->arestas[i][j].conectado = 0;
            (*g)->arestas[i][j].peso = 0;
            (*g)->arestas[i][j].status = pronto;
        }
    return 1;
}

int termina(grafo *g)
{
    free(*g);
    return 1;
}

int busca_vertice(grafo g, char cidade[])
{
    int i;
    
    for(i = 0; i < MAX && i < g->num_vertices; i++)
        if(strcmp(g->vertices[i].nomeCidade, cidade) == 0)
            return i;
            
    return -1;
}

int insere_vertice(grafo g, char cidade[], int *cod)
{
    int pesquisa;
    if(g->num_vertices<MAX)
    {
        pesquisa = busca_vertice(g,cidade);                   
        if(pesquisa == -1)
        {
            strcpy(g->vertices[g->num_vertices].nomeCidade, cidade);
            g->vertices[g->num_vertices].chave = g->num_vertices;
            *cod = g->num_vertices;
            g->num_vertices++;
            return 1;
        }
        else
        {
            *cod = g->vertices[pesquisa].chave; 
            return -1;// Alterado para -1 para diferenciar os 3 estados 
        }
    }
    return 0;
}

int insere_aresta(grafo g,tipo_chave ch1,tipo_chave ch2,tipo_peso peso)
{
    g->arestas[ch1][ch2].conectado = 1;
    g->arestas[ch1][ch2].peso = peso;
    g->arestas[ch1][ch2].status = espera;
    g->arestas[ch2][ch1].conectado = 1;
    g->arestas[ch2][ch1].peso = peso;
    g->arestas[ch2][ch1].status = espera;
    return 1;
}
// fim Grafos --------------------------------------------

int dijkstra(grafo g, tipo_chave origem)
{
    int dist[MAX], perm[MAX], path[MAX];
    int corrente, i, k, dc, testados=0, aux=0;
    int menor_dist, nova_dist;

    for (i = 0; i < g->num_vertices; i++) {
        perm[i] = NAOMEMBRO;
        dist[i] = INFINITO;
    }
   
    perm[origem] = MEMBRO;
    dist[origem] = 0;
    
    corrente = origem;
    k = corrente;

    while (testados != (g->num_vertices-1)){
        menor_dist = INFINITO;
        dc = dist[corrente];

        for (i = 0; i < g->num_vertices; i++){
            if (perm[i] == NAOMEMBRO){
		        if (g->arestas[corrente][i].conectado){
		            nova_dist = dc + g->arestas[corrente][i].peso;
		            if (nova_dist < dist[i]){
		                dist[i] = nova_dist;
		                path[i] = corrente;
		            }
		      	}
	            if (dist[i] < menor_dist) 
	            {
	                menor_dist = dist[i];
	                k = i;
	            }
            }
        } 
 
        corrente = k;
        perm[corrente] = MEMBRO;
        aux += dist[corrente];  
        testados++;          
    } 
	return aux;
}

