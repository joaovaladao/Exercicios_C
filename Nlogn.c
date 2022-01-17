#include <stdio.h>
#include <stdlib.h>

#define less(A,B) ((A) < (B))
#define lesseq(A,B) ((A) <= (B))
#define exch(A,B) { int t; t=A.atual;A.atual=B.atual;B.atual=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }
#define Item item

#define cmpexch_min(A,B) { if (less(A,B)) exch(A,B); }
#define cmpexch_max(A,B) { if (less(A,B)) exch(A,B); }

typedef struct{
    //int pos;
    char caracter;
}Item;

int maior_menor(int *menor, int *maior, int primeiro, int posicao)
{
    if (primeiro)
    {
        *menor = posicao;
        *maior = posicao;
        primeiro = 0;
    }
    else
    {
        *menor = cmpexch_min(*menor, posicao);
        *maior = cmpexch_max(*maior, posicao);
    }
    return primeiro;
}

void merge(Item *V, int l, int m, int r)
{
  Item *R=malloc(sizeof(Item)*(r-l+1));
  int i=l,j=m+1,k=0;

  while(i<=m && j<=r)
  {
    if(lesseq(V[i],V[j]))
      R[k++]=V[i++];
    else
      R[k++]=V[j++];
  }

  while(i<=m)
      R[k++]=V[i++];
  while(j<=r)
      R[k++]=V[j++];


  k=0;
  for(i=l;i<=r;i++)
    V[i]=R[k++];
  free(R);
}

void mergesort(Item *V,int l, int r)
{
  if (l>= r) return;
  int meio=(l+r)/2;
  mergesort(V,l,meio);
  mergesort(V,meio+1,r);
  merge(V,l,meio,r);
}

int main()
{

    Item v[2118124];
    int v_min = 2118124 / 2;
    int v_max = v_min;
    int menor, maior, primeiro=1;

    int num;
    char caracter;

    while (scanf("%d %c", &num, &caracter) != EOF) {
        if (primeiro == 1) {
            v[v_min].caracter = caracter;
            v_max = v_min;
        }
        else {
            if (less(num,maior)) {
                int intervalo = num - maior;
                v_max += intervalo;
                v[v_max].caracter = caracter;
            }
            else if (less(num,menor)) {
                int intervalo = menor - num;
                v_min -= intervalo;
                v[v_min].caracter = caracter;
            }
            else {
                int intervalo = num - menor;
                int pos_entre = v_min+ intervalo;
                v[pos_entre].caracter = caracter;
            }   
        }
        primeiro = maior_menor(&menor, &maior, primeiro, num);        
    }

    //mergesort(v,0,n-1);

    /*for(int i=0; i<n; i++){
        if(v[i].pos != v[i-1].pos)
        printf("%d %c\n", v[i].pos, v[i].caracter);
    }
    */

    for (int i = v_min; i < v_max+1; i++)
        printf("%c", v[i].caracter);

    printf("\n");
    
    return 0;
}