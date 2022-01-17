#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int v; //Vértice 1
    int w; //Vértice 2
} Edge;

//Inicializador de aresta
Edge EDGE(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

typedef struct node *link;

struct node
{
    int v; //Vértice
    link next; //Próximo nó
};

typedef struct graph* Graph;

struct graph
{
    int V;
    int E;
    link *adj;
};

//Retorna um novo nó
link NEW(int v, link next)
{ 
    link x = malloc(sizeof *x);
    x->v = v;
    x->next = next;     
    return x;                         
}

//Função que inicializa um grafo passando como parâmetro a qtd de vértices
Graph GRAPHinit(int V)
{ 
    int v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = malloc(V * sizeof(link));
    for (v = 0; v < V; v++) G->adj[v] = NULL;
    return G;
}

//Adiciona uma aresta num grafo
void GRAPHinsertE(Graph G, Edge e, int maoDupla)
{ 
    int v = e.v, w = e.w;
    G->adj[v] = NEW(w, G->adj[v]);
    if (maoDupla == 2)    
        G->adj[w] = NEW(v, G->adj[w]); 

    G->E++;
}

// Printa um grafo
void printGraph(Graph G)
{
    int v;
    for (v = 0; v < G->V; v++)
    {
        link temp = G->adj[v];
        printf("\n Vertex %d\n: ", v);
        while (temp)
        {
            printf("%d -> ", temp->v);
            temp = temp->next;
        }
        printf("\n");
    }
}

//Busca em Profundidade (DFS)

static int cnt;
static int *pre;

void dfsR(Graph G, Edge e)
{
    int t;
    int w = e.w;
    link l;
    pre[w] = cnt++;

    for (l = G->adj[w]; l != NULL; l = l->next)
    {
        t = l->v;
        if (pre[t] == -1)
            dfsR(G, EDGE(w, t));
    }
}

int GRAPHSearch(Graph G, int cidadeT, int cidadeX)
{
    int v;
    cnt = 0;
    for (v = 0; v < G->V; v++)
    {
        pre[v] = -1;
    }
    
    dfsR(G, EDGE(cidadeT, cidadeX));

    if (pre[cidadeT] != -1 && pre[cidadeX] != -1)
        return 1;
    else
        return 0;
}

int main(int argc, char const *argv[])
{
    int qtdCidades; //V; 2 <= V <= 2000
    int cidadeV; //v; 0 <= v < V
    int cidadeW; //w; 0 <= w < V
    int direcao; //d; 0 <= d <= 2; 1 = v para w, 2 = mão dupla

    scanf("%d", &qtdCidades);

    Graph G = GRAPHinit(qtdCidades);
    pre = malloc(qtdCidades * sizeof(int));

    while (1)
    {
        scanf("%d %d %d", &cidadeV, &cidadeW, &direcao);
        if (cidadeV == 0 && cidadeW == 0 && direcao == 0)
            break;
        
        GRAPHinsertE(G, EDGE(cidadeV, cidadeW), direcao);
    }

    int cidadeT; //t; 0 <= t < V
    int cidadeX; //x; 0 <= x < V

    while (scanf("%d %d", &cidadeT, &cidadeX) != EOF)
    {
        int r2 = GRAPHSearch(G, cidadeT, cidadeX);
        int r1 = GRAPHSearch(G, cidadeX, cidadeT);

        if (r1 == 1 && r2 == 1)
            printf("Ida e volta\n");
        else if (r1 == 1 && r2 == 0)
            printf("Apenas Ida\n");
        else if (r1 == 0 && r2 == 1)
            printf("Apenas Volta\n");
        else
            printf("Impossibru\n");
    }

    return 0;
}