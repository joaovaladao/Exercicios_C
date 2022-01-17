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
Graph GRAPHrand(int, int);

struct graph
{
    int V;
    int E;
    int **adj;
};

Graph GRAPHInit(int v)
{
    Graph G = malloc(sizeof(*G));
    G->V = v;
    G->E = 0;
    G->adj = MATRIXInit(v, v, 0);
    return G;
}

void GRAPHInsertE(Graph G, Edge e)
{
    int v = e.v;
    int w = e.w;

    if (G->adj[v][w] == 0)
        G->E++;

    G->adj[v][w] = 1;
    G->adj[w][v] = 1;
}

void GRAPHRemoveE(Graph G, Edge e)
{
    int v = e.v;
    int w = e.w;

    if (G->adj[v][w] == 1)
        G->E--;

    G->adj[v][w] = 0;
    G->adj[w][v] = 0;
}

int GRAPHEdges(Edge a[], Graph G)
{
    int v, w, E = 0;

    for (v = 0; v < G->V; v++)
        for (w = v + 1; w < G->V; v++)
            if (G->adj[v][w] == 1)
                a[E++] = EDGE(v, w);

    return E;
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

int randV(Graph G)
{
    return G->V * (rand() / (RAND_MAX + 1.0));
}

Graph GRAPHrand(int V, int E)
{
    Graph G = GRAPHInit(V);
    while (G->E < E)
        GRAPHInsertE(G, EDGE(randV(G), randV(G)));
    return G;
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

#define dfsR search
static int cnt, pre[5000], conexoesJoao = -1, maior, pos, posJoao, primeiro = 0, conexoes, maiorPos, maiorConexoes;

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

    for (v = 0; v < G->V; v++)
        pre[v] = -1;

    search(G, EDGE(posJoao, posJoao));
    printf("cnt: %d\n", cnt);
    conexoesJoao = cnt;

    conexoes = conexoesJoao;
    maior = conexoesJoao;
    maiorConexoes = conexoesJoao;

    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
        {
            search(G, EDGE(v, v));
            printf("Pos_maior: %d - Maior: %d\n", cnt, maior);

            if (cnt > maior)
            {
                conexoes = cnt - maior;
                maior = cnt;
                pos = v;

                if (conexoes > maiorConexoes)
                {
                    maiorConexoes = conexoes;
                    maiorPos = pos;
                }

                printf("Maior: %d No: %d Conexoes: %d\n", maior, v, conexoes);
            }

            // if(conexoesJoao!=-1){
            //     conexoesJoao=cnt;
            //     printf("-%d\n",v);
            // }
        }
}

int main()
{
    int V, J, v, w;
    scanf("%d %d", &V, &posJoao);

    Graph G = GRAPHInit(V);

    while (scanf("%d %d", &v, &w) != EOF)
        GRAPHInsertE(G, EDGE(v, w));

    GRAPHsearch(G);

    if (maiorConexoes == conexoesJoao && conexoesJoao == 1)
    {
        printf("Fique em casa\n");
    }
    else if (maiorConexoes == conexoesJoao)
    {
        printf("Bora pra estrada\n");
    }
    else if (maiorConexoes > conexoesJoao)
    {
        printf("Vamos para %d\n", maiorPos);
    }

    return 0;
}