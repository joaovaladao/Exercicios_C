#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned long int atual;
    unsigned long int ant;
    unsigned long int prox;
} node;

#define tipo node

#define less(A,B) ((A.atual) < (B.atual))
#define exch(A,B) { int t; t=A.atual;A.atual=B.atual;B.atual=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }

// pos = 1 - atual
// pos = 2 - anterioe
// pos = 3 - proximo

int busca_ordenada(tipo *v, int n, int x, int pos)
{
    int e = -1, d = n, m, conteudo;
    while (e < d - 1)
    {
        m = (e + d) / 2;

        if (pos == 1)
        {
            conteudo = v[m].atual;
        }
        else if (pos == 2)
        {
            conteudo = v[m].ant;
        }
        else
        {
            conteudo = v[m].prox;
        }

        if (v[m].atual == x)
            return m;
        if (v[m].atual < x)
            e = m;
        else
            d = m;
    }
    return -1;
}

int separa(tipo *V,int l,int r)
{
  tipo c=V[r];
  int j=l;
  for(int k=l;k<r;k++)
    if(less(V[k],c))
    {
      exch(V[k],V[j]);
      j++;
    }
  exch(V[j],V[r]);
  return j;
}

void insertionsort(tipo *v,int l,int r)
{
  for(int i=r;i>l;i--)
    cmpexch(v[i-i],v[i]);

  for(int i=l+2;i<=r;i++)
  {
    int j=i; tipo tmp=v[j];
    while(less(tmp,v[j-1]))
    {
      v[j]=v[j-1];
      j--;
    }
    v[j]=tmp;
  }
}

static void quicksortM3(tipo *V,int l, int r)
{
  if (r-l<=32) return;

  exch(V[(l+r)/2],V[r-1]);
  cmpexch(V[l],V[r-1]);
  cmpexch(V[l],V[r]);
  cmpexch(V[r-1],V[r]);


  int j=separa(V,l+1,r-1);
  quicksortM3(V,l,j-1);
  quicksortM3(V,j+1,r);
}

void quicksortM3insertion(tipo *V,int l,int r)
{
  quicksortM3(V,l,r);
  insertionsort(V,l,r);
}

int main(void)
{
    int i = 0, n = 0, sana = 1;
    node no1, no2;
    node *v = malloc(250000 * sizeof(node));

    while (scanf("%lx %lx %lx", &v[n].atual, &v[n].ant, &v[n].prox) != EOF)
    {
        if (n == 0)
        {
            no1 = v[n];
        }
        else if (n == 1)
        {
            no2 = v[n];
        }
        n++;
    }

    quicksortM3insertion(v,0,n-1);

    i=0;
    unsigned long int pos;
    node valor = no1;
    unsigned long int vetorPos[n-2];

    while(n--){
        printf("%lx - %lx - %lx\n", v[n].atual, v[n].ant, v[n].prox);
    }
    //printf("\n");
    //printf("%lx         ", valor.prox);
    //printf("%d         ", n);
    

    while(1){
      pos = busca_ordenada(v,n,valor.prox,1);

      if(pos == -1)
        break;

      vetorPos[i] = pos;
      valor = v[pos];
      i++;
    }

    /*for(int j=0; j<i; j++){
    printf("%lx ", vetorPos[j]);
    }
    printf(" %lx\n", vetorPos[i-1]);*/

    int contPos = 0;

    for(int inic = 0; inic < n; inic++){
      //printf("Comparando %lx com %lx\n", v[inic].atual, vetorPos[contPos]);
      if(v[inic].atual != vetorPos[contPos]){
        printf("%lx %lx %lx\n",v[inic].atual,v[inic].ant,v[inic].prox);
      }
      else{
        printf("Retirado\n");
        contPos++;
      }
    }
    
    /*while(pos!=-1){

        if (valor.prox == no2.ant && no2.prox == no1.ant){
            printf("sana\n");
            return 0;
        }

        pos = busca_ordenada(v,n,valor.prox,1);

        if(pos==-1){
            printf("insana\n");
            return 0;
        }

        valor = v[pos];
    }*/

    return 0;
}