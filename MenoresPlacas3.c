#include <stdio.h>
#include <stdlib.h>

#define tipo int

typedef struct PQ
{
    tipo *pq;
    int N;
} PQ;

#define less(A,B) ((A) > (B))
#define exch(A,B) { tipo t; t=A;A=B;B=t; }

void fixUp(tipo *pq, int k)
{
    while(k>1 && less(pq[k/2],pq[k]))
    {
        exch(pq[k],pq[k/2]);
        k=k/2;
    }
}

void fixDown(tipo *pq, int k, int N)
{
    int j;
    while(2*k <= N)
    {
        j=2*k;
        if(j<N && less(pq[j],pq[j+1])) j++;
        if(!less(pq[k],pq[j])) break;
        exch(pq[k],pq[j]);
        k=j;
    }
}

void PQinit(PQ *PQ, int maxN)
{
    PQ->pq=malloc(sizeof(tipo)*maxN);
    PQ->N=0;
}

int PQempty(PQ *PQ)
{
    return PQ->N==0;
}

void PQinsert(PQ *PQ,tipo v)
{
    PQ->pq[++PQ->N]=v;
    fixUp(PQ->pq,PQ->N);
}

tipo PQdelmax(PQ *PQ)
{
    exch(PQ->pq[1],PQ->pq[PQ->N]);
    fixDown(PQ->pq,1,PQ->N-1);
    return PQ->pq[PQ->N--];
}

tipo PQespiamax(PQ *PQ)
{
    return PQ->pq[1];
}

void PQworkaroundMax(PQ *PQ, tipo x){
    PQ->pq[1] = x;
    fixDown(PQ->pq,1,PQ->N);
}

void merge(int *V, int l, int m, int r)
{
    int *R = malloc(sizeof(int) * (r - l + 1));
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r)
    {
        if (less(V[i], V[j]))
            R[k++] = V[i++];
        else
            R[k++] = V[j++];
    }

    while (i <= m)
        R[k++] = V[i++];
    while (j <= r)
        R[k++] = V[j++];

    k = 0;
    for (i = l; i <= r; i++)
        V[i] = R[k++];
    free(R);
}

void mergesort(int *V, int l, int r)
{
    if (l >= r)
        return;
    int meio = (l + r) / 2;
    mergesort(V, l, meio);
    mergesort(V, meio + 1, r);
    merge(V, l, meio, r);
}

void imprimeCrescente(PQ *pq,int tam){
    mergesort(pq->pq, 1, tam-1);

    for (int i = 1; i < tam; i++)
    {
        printf("%d ", pq->pq[i]);
    }
    printf("\n");

}

void imprimeHeap(PQ *pq){
    if(PQempty(pq))
        return;
    
    int x = PQdelmax(pq);

    imprimeHeap(pq);

    printf("%d ",x);

}

int main()
{
    PQ *pq = malloc(sizeof(PQ));
    PQinit(pq, 1000001);

    int n=0;
    int comando,num;
    while (scanf("%d %d", &comando, &num) != EOF)
    {
        if(comando==1){
            PQinsert(pq,num);
            n++;
        }
        else{
            int *v = calloc(num,sizeof(int));
            for (int i=0;i<num;i++){
                int valor_atual = PQdelmax(pq);
                v[i]=valor_atual;
                if(i==0){
                    printf("%d",valor_atual);
                }else{
                    printf(" %d",valor_atual);
                }
            }
            for (int i=0;i<num;i++){
                PQinsert(pq,v[i]);
            }
            free(v);
            printf("\n");
        }
    }

    // imprimeCrescente(pq, k);
    // imprimeHeap(pq);
}