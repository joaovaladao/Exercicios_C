#include <stdio.h>
#include <stdlib.h>

#define maxV 5000
#define dfsR search

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

static int cnt, pre[maxV];

void dfsR(Graph G, Edge e)
{
    int t, w = e.w;
    pre[w] = cnt++; 
    for (t = 0; t < G->V; t++){
      if (G->adj[w][t] != 0) {
        if (pre[t] == -1){
            Edge new_edge = {w,t};
          dfsR(G, new_edge); 
        }
      }
    }
  }

void GRAPHsearch(Graph G, int *count)
{
    int v;
    cnt = 0;
    for (v = 0; v < G->V; v++)
        pre[v] = -1;
    for (v = 0; v < G->V; v++){
        if (pre[v] == -1){
            Edge new_edge = {v,v};
            search(G, new_edge);
            *count = *count + 1;
        }
    }
}

int main()
{
    int N, v, w;
    scanf("%d", &N);
    Graph grafo = GRAPHInit(N);
    int count = 0;

    while (scanf("%d %d", &v, &w) != EOF){
        Edge new_edge = {v,w};
        GRAPHinsertE(grafo, new_edge);
        //printf("inseri %d %d no grafo\n", v, w);
    }

    GRAPHsearch(grafo,&count);

    printf("%d\n",count);

    return 0;
}