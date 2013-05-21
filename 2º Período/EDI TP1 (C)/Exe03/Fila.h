typedef struct{
    int id;
    int combustivel;
    int tempoDeEspera;
    /* outros componentes */
}tipo_item;

typedef struct nodo{
    tipo_item item;
    struct nodo *prox;
}tipo_nodo;
typedef struct {
    tipo_nodo *inicio, *fim;
    int tamanho;
}tipo_fila;
typedef tipo_fila *fila;

fila cria_fila();
void termina_fila(fila *f);
int fila_cheia(fila f);
int fila_vazia(fila f);
int enfileira(fila f, tipo_item e);
int desenfileira(fila f, tipo_item *e);
int imprime(fila f);
