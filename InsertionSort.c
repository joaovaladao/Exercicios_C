#include <stdio.h>
typedef int Item;

void insertionsort(Item *v,int l,int r)
{
  for(int i=r;i>l;i--)
    if(v[i] < v[i-i]){
                Item aux;
                aux = v[i];
                v[i] = v[i-i];
                v[i-i] = aux;
            }

  for(int i=l+2;i<=r;i++)
  {
    int j=i; Item tmp=v[j];
        while(tmp < v[j-1]){
        v[j]=v[j-1];
        j--;
        }
    v[j]=tmp;
  }
}

int main(){
    //int V[5] = {1,5,2,3,4};
    int V[50001];
    int tam = 0, entrada;
    while(scanf("%d", &entrada) != EOF){
        V[tam] = entrada;
        tam++;
    }
    //printf("Prim: %d\nUlti: %d\n", V[0], entrada);
    insertionsort(V,0,tam-1);
    printf("%d",V[0]);
    for(int i = 1; i < tam; i++){
        printf(" %d",V[i]);
    }
    printf("\n");
    return 0;
}