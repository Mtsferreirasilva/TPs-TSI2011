typedef struct localizacaoAviao{
    int id;
    int prateleira;
}localizacaoAviao; // Armazena id e prateleira do avião com combustivel 0

//Adiciona os avioes nas prateleiras, passando somente as filas e a quantidade de avioes chegando.
int AdicionaNasPrateleiras(int n, fila p1,fila p2,fila p3,fila p4);

//Adiciona os avioes para decolar, passando somente as filas e a quantidade de avioes chegando.
int AdicionaParaDecolar(int n,fila d1,fila d2,fila d3);

//Verifica disponibilidade das pistas 1 e 2, verifica combustivel e escolhe o melhor aviao para pousar.
int PousaAvioes(int pista1,int pista2,fila p1,fila p2,fila p3,fila p4,int n);

//Verifica disponibilidade das pistas 1 e 2,  escolhe o melhor aviao para decolar.
int DecolaAvioes(int pista1,int pista2,int pista3,fila d1,fila d2,fila d3,int n);

//Verifica se avião possui 0 de combustivel, retornando sua ID, caso não haja nenhum, retorna 0
localizacaoAviao VerificaCombustivel(fila p1,fila p2,fila p3,fila p4);

//Diminui o combustivel de cada avião das filas por unidade de tempo
void DecrementaCombustivel(fila p1,fila p2,fila p3,fila p4);

//Retira das filas avioes com combustivel 0
int DesenfileiraAviaoSemCombustivel(int id,int prateleira,fila p1,fila p2,fila p3,fila p4);

//Calcula a media de tempo de espera para pousos acontecerem.
float TempoEsperaPouso(fila p1,fila p2,fila p3,fila p4);

//Incrementa o tempo de espera dos avies das filas de decolagem
void IncrementaTempoEspera(fila d1,fila d2,fila d3);

//Calcula a media de tempo de esperar para decolagens acontecerem.
float TempoEsperaDecolagem(fila d1,fila d2,fila d3);

//Imprime conteudo de fila
void ImprimeConteudo(fila f);

// Media dos avioes que decolaram
float mediaDecolar();

// Media dos avioes que pousaram
float mediaPousar();
