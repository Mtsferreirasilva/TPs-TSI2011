// Pilha

typedef struct{
    int dir,esq;
    /* outros componentes */
}tipo_item_pilha;

typedef struct nodo{
    tipo_item_pilha item;
    struct nodo *prox;
}tipo_nodo;

typedef struct{
    tipo_nodo *topo;
    int tamanho;
}tipo_pilha;

typedef tipo_pilha pilha;

//-----------------------------------
int cria_pilha (pilha *p); //cria pilha

int push(pilha *p, tipo_item_pilha e); //coloca elemento no topo da pilha

int pop(pilha *p, tipo_item_pilha *e); //retira elemento do topo da pilha

int tamanho_pilha(pilha p); // retorna o tamanho final da pilha

int pilha_vazia(pilha p); // retorna True para pilha vazia

int pilha_cheia(pilha p); // retorna True para pilha cheia

int termina(pilha *p); // retirna todos os apontadores de uma pilha
