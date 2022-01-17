#include <stdio.h>
#include <stdlib.h>

#define less(A,B) ((A.atual) < (B.atual))
#define lesseq(A,B) ((A.pos) <= (B.pos))
#define exch(A,B) { int t; t=A.atual;A.atual=B.atual;B.atual=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }
#define Item item

typedef struct{
    int pos;
    char caracter;
}item;

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

int main(){
    int n = 0;
    int num;
    char carac;
    Item v[1000001];
    int flag = 0;

    while (scanf("%d %c", &num, &carac) != EOF){
        if(n<1000001){
            v[n].pos = num;
            v[n].caracter = carac;
            n++;
        }
        else{
            flag++;
        }
    }
    mergesort(v,0,n-1);
    for(int i=0; i<n; i++){
        if(v[i].pos != v[i-1].pos)
        printf("%c", v[i].caracter);
    }
        printf("\n");
    return 0;
}
