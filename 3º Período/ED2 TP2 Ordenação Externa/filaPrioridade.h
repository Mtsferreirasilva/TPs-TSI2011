#ifndef FILA_PRIORIDADE
#define FILA_PRIORIDADE

typedef struct{
    int run;
    int chave;
}tipo_nodo;

typedef struct {
    tipo_nodo *elemento; // Alocação dinamica de elementos com base na quantidade de RUNs geradas.
    int tamanho;
}tipo_fila;

typedef tipo_fila *fila;


fila cria_fila();
void termina_fila();
void imprime_fila();
int insere_fila();
int fila_vazia();
void reorganiza_heap();

#endif
