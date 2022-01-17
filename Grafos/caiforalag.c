#include <stdio.h>
#include <stdlib.h>

#define vertex int
typedef struct graph *Graph;

typedef struct node *link;
struct node
{
    vertex w;
    int c;
    link next;
};

struct graph
{
    int V;
    int A;
    link *adj;
};
typedef struct graph *Graph;

static link NEWnode(vertex w, link next, int c)
{
    link a = malloc(sizeof(struct node));
    a->w = w;
    a->next = next;
    a->c = c;
    return a;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc(Graph G, vertex v, vertex w, int c)
{
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v], c);
    G->A++;
}

void UGRAPHinsertEdge(Graph G, vertex v, vertex w, int c)
{
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v], c);
    G->adj[w] = NEWnode(v, G->adj[w], c);
    G->A += 2;
}

#define true 1
#define false 0
#define INT_MAX 2147483647

void GRAPHcptD1(Graph G, vertex s,
                vertex *pa, int *dist)
{
    int mature[2001];
    for (vertex v = 0; v < G->V; ++v)
        pa[v] = -1, mature[v] = false, dist[v] = INT_MAX;
    pa[s] = s, dist[s] = 0;

    while (true)
    {
        // escolha de y:
        int min = INT_MAX;
        vertex y;
        for (vertex z = 0; z < G->V; ++z)
        {
            if (mature[z])
                continue;
            if (dist[z] < min)
                min = dist[z], y = z;
        }
        if (min == INT_MAX)
            break;
        // atualização de dist[] e pa[]:
        for (link a = G->adj[y]; a != NULL; a = a->next)
        {
            if (mature[a->w])
                continue;
            if (dist[y] + a->c < dist[a->w])
            {
                dist[a->w] = dist[y] + a->c;
                pa[a->w] = y;
            }
        }
        mature[y] = true;
    }
}

static vertex *queue;
static int begin, end;

void QUEUEinit(int N)
{
    queue = malloc(N * sizeof(vertex));
    begin = end = 0;
}

int QUEUEempty(void)
{
    return begin == end;
}

void QUEUEput(vertex v)
{
    queue[end++] = v;
}

vertex QUEUEget(void)
{
    return queue[begin++];
}

void QUEUEfree(void)
{
    free(queue);
}

int GRAPHcptBF(Graph G, vertex s, vertex *pa, int *dist)
{
    // return false;
    QUEUEinit(G->A);
    int onqueue[1000];
    for (vertex u = 0; u < G->V; ++u)
        pa[u] = -1, dist[u] = INT_MAX, onqueue[u] = false;
    pa[s] = s, dist[s] = 0;
    QUEUEput(s);
    onqueue[s] = true;
    vertex V = G->V; // pseudovértice
    QUEUEput(V);     // sentinela
    int k = 0;

    while (true)
    {
        vertex v = QUEUEget();
        if (v < V)
        {
            for (link a = G->adj[v]; a != NULL; a = a->next)
            {
                if (dist[v] + a->c < dist[a->w])
                {
                    dist[a->w] = dist[v] + a->c;
                    pa[a->w] = v;
                    if (onqueue[a->w] == false)
                    {
                        QUEUEput(a->w);
                        onqueue[a->w] = true;
                    }
                }
            }
        }
        else
        {
            if (QUEUEempty())
            {
                QUEUEfree();
                return true; // A
            }
            if (++k >= G->V)
            {
                QUEUEfree();
                return false; // B
            }
            QUEUEput(V); // sentinela
            for (vertex u = 0; u < G->V; ++u)
                onqueue[u] = false;
        }
    }
}

int dijkstra(Graph G, vertex o, vertex x)
{
    vertex *pa = calloc(G->V, sizeof(int));
    vertex *dist = calloc(G->V, sizeof(int));

    GRAPHcptD1(G, o, pa, dist);
    int peso = dist[x];

    return peso;
}

int bellmanFord(Graph G, vertex o, vertex x)
{
    vertex *pa = calloc(G->V, sizeof(int));
    vertex *dist = calloc(G->V, sizeof(int));

    int bf = GRAPHcptBF(G, o, pa, dist);
    // printf("%d\n", bf);
    // int peso = dist[x];

    return 1;
}

int main()
{
    int V, v, w, c, t, o, x;

    scanf("%d", &V);
    Graph G = GRAPHinit(V);
    Graph Gneg = GRAPHinit(V);

    while (scanf("%d %d %d %d", &v, &w, &c, &t))
    {

        if (v == 0 && w == 0 && c == 0 && t == 0)
        {
            break;
        }

        if (t == 0)
        {
            UGRAPHinsertEdge(G, v, w, c);
            UGRAPHinsertEdge(Gneg, v, w, c);
        }
        else
        {
            GRAPHinsertArc(Gneg, v, w, c);
        }
    }

    while (scanf("%d %d", &o, &x) != EOF)
    {
        int d = dijkstra(G, o, x);
        // int b = bellmanFord(Gneg, o, x);
        printf("%d\n", d);
    }

    return 0;
}