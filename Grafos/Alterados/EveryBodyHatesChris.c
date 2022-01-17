#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int v;
    int w;
} Edge;

typedef struct graph *Graph;

struct graph
{
    int V;
    int E;
    int **adj;
};

int **MATRIXInit(int r, int c, int val)
{
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        t[i] = malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}

Graph GRAPHInit(int v)
{
    Graph G = malloc(sizeof(*G));
    G->V = v;
    G->E = 0;
    G->adj = MATRIXInit(v, v, 0);
    return G;
}

void GRAPHinsertE(Graph G, Edge e)
  { 
    int v = e.v, w = e.w;
    if (G->adj[v][w] == 0) G->E++;
    G->adj[v][w] = 1; 
    G->adj[w][v] = 1;
  }

void GRAPHremoveE(Graph G, Edge e)
  { 
    int v = e.v, w = e.w;
    if (G->adj[v][w] == 1) G->E--;
    G->adj[v][w] = 0; 
    G->adj[w][v] = 0;
  }

int main()
{
    int N, M, J;
    int vetor_frequencia[3000] = {};
    scanf("%d %d %d", &N, &M, &J);

    Graph G = GRAPHInit(N);
    int qtd_vizinho, local_vizinho;

// i representa a ID do local

    for (int i = 0; i < N; i++) {
        scanf("%d", &qtd_vizinho);

        for (int k = 0; k < qtd_vizinho; k++){
            scanf("%d", &local_vizinho);
            Edge new_edge = {i,local_vizinho};
            GRAPHinsertE(G,new_edge);
        }
    }

    int ja_esteve;
    for (int i = 0; i < M; i++){
        scanf("%d", &ja_esteve);
        vetor_frequencia[ja_esteve]++;

        for(int k = 0; k < G->V; k++){
            if (G->adj[ja_esteve][k] > 0){
                vetor_frequencia[k]++;
            }
        }

    }

    int onde_esta;
    for (int j = 0; j < J; j++){
        scanf("%d", &onde_esta);
        if(vetor_frequencia[onde_esta] == 0)
            printf("Nao vou estar la\n");
        else
            printf("Eu vou estar la\n");
    }

    return 0;
}