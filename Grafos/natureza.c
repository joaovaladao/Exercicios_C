#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[31];
} animal;

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
void GRAPHshow(Graph, animal[]);
void GRAPHshowTC(Graph);

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
    G->adj[w][v] = 1;
}

void GRAPHDestroy(Graph G)
{
    int v;

    for (v = 0; v < G->V; v++)
    {
        free(G->adj[v]);
    }

    free(G->adj);

    free(G);
}

void GRAPHshow(Graph G, animal a[])
{
    int i, j;
    printf("%d vertices, %d edges\n", G->V, G->E);
    for (i = 0; i < G->V; i++)
    {
        printf("%s come", a[i].nome);
        for (j = 0; j < G->V; j++)
            if (G->adj[i][j] == 1)
                printf(" %s come", a[j].nome);
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

#define vertex Edge

// static vertex *queue;
// static int begin, end;

// void QUEUEinit(int N)
// {
//     queue = malloc(N * sizeof(vertex));
//     begin = end = 0;
// }

// int QUEUEempty(void)
// {
//     return begin == end;
// }

// void QUEUEput(vertex v)
// {
//     queue[end++] = v;
// }

// vertex QUEUEget(void)
// {
//     return queue[begin++];
// }

// void QUEUEfree(void)
// {
//     free(queue);
// }

// void bfs(Graph G, Edge e)
// {
//     int v, w;
//     QUEUEput(e);
//     pre[e.w] = cnt++;
//     while (!QUEUEempty())
//     {
//         e = QUEUEget();
//         w = e.w;
//         st[w] = e.v;
//         for (v = 0; v < G->V; v++)
//             if ((G->adj[w][v] == 1) && (pre[v] == -1))
//             {
//                 QUEUEput(EDGE(w, v));
//                 pre[v] = cnt++;
//             }
//     }
// }

#define maxV 5002

#define dfsR search
static int cnt, pre[maxV], st[maxV], maiorCadeia = 0;

void dfsR(Graph G, int v)
{
    int t, w = v;
    pre[w] = 1;
    cnt++;
    for (t = 0; t < G->V; t++)
        if (G->adj[w][t] && !pre[t])
            dfsR(G, t);
}


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

void GRAPHshowTC(Graph G)
{
    int i, j;
    printf("%d vertices, %d edges\n", G->V, G->E);
    for (i = 0; i < G->V; i++)
    {
        printf("%2d:", i);
        for (j = 0; j < G->V; j++)
            if (G->tc[i][j] == 1)
                printf(" %2d", j);
        printf("\n");
    }
}

int GRAPHLongestPath(Graph G)
{
    int i, j, maior = 0, maiorCadeia = 0;
    for (i = 0; i < G->V; i++)
    {
        maior = 0;
        for (j = 0; j < G->V; j++)
            if (G->tc[i][j] == 1)
                maior++;
        if (maior > maiorCadeia)
        {
            maiorCadeia = maior;
        }
    }

    return maiorCadeia;
}

int comp(const void *a, const void *b)
{
    animal *ia = (animal *)a;
    animal *ib = (animal *)b;
    return strcmp(ia->nome, ib->nome);
}

int busca_ordenada(animal *v, int size, char *target)
{
    int bottom = 0;
    int mid;
    int top = size - 1;

    while (bottom <= top)
    {
        mid = (bottom + top) / 2;
        if (strcmp(v[mid].nome, target) == 0)
        {
            return mid;
        }
        else if (strcmp(v[mid].nome, target) > 0)
        {
            top = mid - 1;
        }
        else if (strcmp(v[mid].nome, target) < 0)
        {
            bottom = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int c, r, posA1, posA2;
    char nome[31];
    char a1[31];
    char a2[31];

    while (scanf("%d %d", &c, &r))
    {
        maiorCadeia = 0;
        if (c == 0 && r == 0)
        {
            break;
        }

        Graph G = GRAPHInit(c);

        animal *a = malloc(c * sizeof(animal));

        for (int i = 0; i < c; i++)
        {
            scanf("%s", a[i].nome);
        }

        qsort(a, c, sizeof(animal), comp);

        for (int i = 0; i < r; i++)
        {
            scanf("%s %s", a1, a2);

            posA1 = busca_ordenada(a, c, a1);
            posA2 = busca_ordenada(a, c, a2);

            GRAPHInsert(G, EDGE(posA2, posA1));
        }

        // GRAPHshow(G,a);

        int v;
        for (v = 0; v < G->V; v++)
            pre[v] = 0;

        for (v = 0; v < G->V; v++)
        {
            cnt = 0;
            if (pre[v] == 0)
                search(G, v);
            maiorCadeia = cnt > maiorCadeia ? cnt : maiorCadeia;
        }

        printf("%d\n", maiorCadeia);

        GRAPHDestroy(G);
    }

    return 0;
}