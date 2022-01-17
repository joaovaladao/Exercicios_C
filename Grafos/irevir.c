#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int v;
    int w;
} Edge;

Edge EDGE(int, int);

Edge EDGE(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

typedef struct graph *Graph;

Graph GRAPHInit(int); // int é quant de vertices
void GRAPHInsertE(Graph, Edge);
void GRAPHRemoveE(Graph, Edge);
int GRAPHEdges(Edge[], Graph G);
Graph GRAPHCopy(Graph);
void GRAPHDestroy(Graph);
int **MATRIXInit(int, int, int);
void GRAPHshow(Graph);

struct graph
{
    int V;
    int E;
    int **adj;
    int **tc;
};

Graph GRAPHInit(int v)
{
    Graph G = malloc(sizeof(*G));
    G->V = v;
    G->E = 0;
    G->adj = MATRIXInit(v, v, 0);
    return G;
}

void GRAPHInsert(Graph G, Edge e)
{
    int v = e.v;
    int w = e.w;

    if (G->adj[v][w] == 0)
        G->E++;

    G->adj[v][w] = 1;
}

void GRAPHDestroy(Graph G)
{
    int v;

    for (v = 0; v < G->V; v++)
    {
        free(G->adj[v]);
    }

    free(G->adj);

    for (v = 0; v < G->V; v++)
    {
        free(G->tc[v]);
    }

    free(G->tc);

    free(G);
}

void GRAPHshow(Graph G)
{
    int i, j;
    printf("%d vertices, %d edges\n", G->V, G->E);
    for (i = 0; i < G->V; i++)
    {
        printf("%2d:", i);
        for (j = 0; j < G->V; j++)
            if (G->adj[i][j] == 1)
                printf(" %2d", j);
        printf("\n");
    }
}

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

#define maxV 2001

static int *visited;
int pathR(Graph G, int v, int w)
{
    int t;
    if (v == w)
        return 1;
    visited[v] = 1;
    for (t = 0; t < G->V; t++)
        if (G->adj[v][t] == 1)
            if (visited[t] == 0)
                if (pathR(G, t, w))
                    return 1;
    return 0;
}
int GRAPHpath(Graph G, int v, int w)
{
    visited = calloc(G->V, sizeof(int));
    return pathR(G, v, w);
}

void GRAPHtc(Graph G)
{
    int i, s, t;
    G->tc = MATRIXInit(G->V, G->V, 0);
    for (s = 0; s < G->V; s++)
        for (t = 0; t < G->V; t++)
            G->tc[s][t] = G->adj[s][t];
    for (s = 0; s < G->V; s++)
        G->tc[s][s] = 1;
    for (i = 0; i < G->V; i++)
        for (s = 0; s < G->V; s++)
            if (G->tc[s][i] == 1)
                for (t = 0; t < G->V; t++)
                    if (G->tc[i][t] == 1)
                        G->tc[s][t] = 1;
}

int GRAPHreach(Graph G, int s, int t)
{
    return G->tc[s][t];
}

int GraphStronglyConnected(Graph G)
{
    for (int i = 0; i < G->V; i++)
    {
        for (int j = 0; j < G->V; j++)
        {
            if (GRAPHreach(G, i, j) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

static int cnt, pre[maxV], contador;
#define dfsR search
void dfsR(Graph G, Edge e)
{
    int t, w = e.w;
    pre[w] = cnt++;
    for (t = 0; t < G->V; t++)
        if (G->adj[w][t] != 0)
            if (pre[t] == -1)
                dfsR(G, EDGE(w, t));
}

void GRAPHsearch(Graph G)
{
    int v;
    cnt = 0;
    contador = 0;
    for (v = 0; v < G->V; v++)
        pre[v] = -1;
    for (v = 0; v < G->V; v++)
    {
        if (pre[v] == -1)
        {
            contador++;
            search(G, EDGE(v, v));
        }
    }
}

int main()
{
    int N, M, v = 1, w = 1, d = 1;

    while (scanf("%d %d", &N, &M))
    {
        if (N == 0 || M == 0)
        {
            break;
        }

        Graph G = GRAPHInit(N);

        for (int i = 0; i < M; i++)
        {
            scanf("%d %d %d", &v, &w, &d);
            v -= 1;
            w -= 1;
            if (d == 1)
            {
                GRAPHInsert(G, EDGE(v, w));
            }
            else
            {
                GRAPHInsert(G, EDGE(v, w));
                GRAPHInsert(G, EDGE(w, v));
            }
        }

        GRAPHtc(G);

        printf("%d\n",GraphStronglyConnected(G));

        GRAPHDestroy(G);
    }

    return 0;
}