#include <stdio.h>
typedef int Item;

void selectionsort(Item *v,int l,int r)
{
  for(int i=l;i<r;i++)
  {
    int min=i;
    for(int j=i+1;j<=r;j++)
      if(v[j] > v[min])
        min=j;
    Item aux;
    aux = v[i];
    v[i] = v[min];
    v[min] = aux;
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
    selectionsort(V,0,tam-1);

    printf("%d",V[tam-1]);
    for(int i = tam - 2; i >= 0; i--){
        printf(" %d",V[i]);
    }
    printf("\n");
    return 0;
}