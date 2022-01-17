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

int GRAPHsearch(Graph G, int j, int *possivel_maior, int *maior, int *pos, int *menor)
{
    int v, qtd_conec, maior_conec;

    for (v = 0; v < G->V; v++)
        pre[v] = -1;

    Edge novo_edge = {j,j};
    search(G,novo_edge);
    //printf("cnt: %d\n", cnt);
    *menor = *possivel_maior = *pos = *maior = cnt;
    int aux = cnt;
    maior_conec = aux;

    for (v = 0; v < G->V; v++){
        if (pre[v] == -1){
            Edge new_edge = {v,v};
            search(G, new_edge);
            *possivel_maior = cnt;

            //printf("Pos_maior: %d - Maior: %d\n", *possivel_maior, *maior);
            if(*possivel_maior > *maior){
                qtd_conec = *possivel_maior - *maior;
                *maior = *possivel_maior;

                //printf("Maior: %d - Posição: %d\n", *maior, v);

                if(qtd_conec > aux){
                    maior_conec = qtd_conec;
                    *pos = v;
                }
            }
            *possivel_maior = 0;
        }
        else
            *possivel_maior = *possivel_maior + 1;
    }

    if (aux > maior_conec){
        return 1;
    }
    else if(aux == 1 && maior_conec ==1){
        return 2;
    }
    else{
        return 3;
    }
}

int main()
{
    int N, J, v, w;
    scanf("%d %d", &N, &J);
    Graph grafo = GRAPHInit(N);
    int maior = 0, possivel_maior = 0, pos = 0;

    while (scanf("%d %d", &v, &w) != EOF){
        Edge new_edge = {v,w};
        GRAPHinsertE(grafo, new_edge);
        //printf("inseri %d %d no grafo\n", v, w);
    }

    int menor = 0;

    int res = GRAPHsearch(grafo, J, &possivel_maior, &maior, &pos, &menor);

    if(res == 1)
        printf("Vamos para %d\n", pos);
    else if(res == 2)
        printf("Fica em casa\n");
    else
        printf("Bora pra estrada\n");
    

    return 0;
}