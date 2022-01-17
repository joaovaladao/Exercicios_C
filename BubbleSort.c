#include <stdio.h>
typedef int Item;

void bubblesort(Item *v,int l,int r)
{
  for(int i=l;i<r;i++){
    for(int j=l+1;j<=r;j++){
        if(v[j] < v[j-1]){
            Item aux;
            aux = v[j];
            v[j] = v[j-1];
            v[j-1] = aux;
        }
    }
  }
}

int main(){
    //int V[5] = {1,5,2,3,4};
    int V[1001];
    int tam = 0, entrada;
    while(scanf("%d", &entrada) != EOF){
        V[tam] = entrada;
        tam++;
    }
    //printf("Prim: %d\nUlti: %d\n", V[0], entrada);
    bubblesort(V,0,tam-1);
    printf("%d",V[0]);
    for(int i = 1; i < tam; i++){
        printf(" %d",V[i]);
    }
    printf("\n");
    return 0;
}