#include <stdio.h>
#include <stdlib.h>

#define less(A,B) ((A) < (B))
#define lesseq(A,B) ((A) <= (B))
#define exch(A,B) { int t; t=A;A=B;B=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }
#define Item int

int separa(Item *V,int l,int r)
{
  int i=l-1, j=r; Item v=V[r];
  for(;;)
  {
    while(less(V[++i],v));
    while(less(v,V[--j])) if(j==l) break;
    if(i>=j) break;
    exch(V[i],V[j]);
  }
  exch(V[i],V[r])
  return i;
}

void quickSelect(Item *V,int p,int l,int r){
    int j = separa(V,l,r);
    if(j==p) return;
    if(j<p)
        quickSelect(V,p,j+1,r);
    else
        quickSelect(V,p,l,j-1);
}

void insertionsort(Item *v,int l,int r)
{
  for(int i=r;i>l;i--)
    cmpexch(v[i-i],v[i]);

  for(int i=l+2;i<=r;i++)
  {
    int j=i; Item tmp=v[j];
    while(less(tmp,v[j-1]))
    {
      v[j]=v[j-1];
      j--;
    }
    v[j]=tmp;
  }
}

static void quicksortM3(Item *V,int l, int r)
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

void quicksortM3insertion(Item *V,int l,int r)
{
  quicksortM3(V,l,r);
  insertionsort(V,l,r);
}

int main(){
    int op, placa;
    int n = 0;
    Item v[1000001];

    while (scanf("%d %d", &op, &placa) != EOF){
        if(op == 1){
            v[n] = placa;
            n++;
        }
        else if(op == 2){
        //printf("%d\n",placa);
        quickSelect(v,placa-1,0,n-1);
        quicksortM3insertion(v,0,placa);
          for(int i=0; i<n; i++){
              if(i==15) printf("\n");
          printf("%d ",v[i]);
          }
          printf("\n");
        }
    }
    return 0;
}