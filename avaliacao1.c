#include <stdio.h>


int buscaBin(int vetor[], int begin, int end, int item) {
  int k;
  k = (begin+end)/2;
  if (begin > end){
	  return -1;
  }
  else {
	  
	  if (vetor[k] == item){
	    return k;
    }
    else{
	    if (item < vetor[k]){
	      return buscaBin(vetor,begin,k-1, item);
      }
      else
	      return buscaBin(vetor,k+1,end, item);
    }
  }
}

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0; 
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
}


int main()
{
  int numMal[200000];
  int numMal_rep[200000];
  int numMal_rep2[200000];
  int soma=0;
  int i,j,cont=0;
  int count=0;
  int aux=1,aux2=1;
  int N,N2;
  scanf("%d",&N);
  for(int n=0;n<N;n++){
    scanf("%d",&numMal[n]);
    
  }
  mergeSort(numMal, 0, N-1);
  numMal_rep[0]=numMal[0];
  for(int i = 0;i<N;i++){
    	if(buscaBin(numMal_rep,0,aux,numMal[i]) == -1){
		numMal_rep[aux] = numMal[i];
		aux++;
  }
  }
   if(aux%2==0){
        for(int j=0;j<aux;j=j+2){
            numMal_rep[aux+count]=numMal_rep[j]+numMal_rep[j+1];
            count++;
        }
   }
  else{
        numMal_rep[aux]=1000000000;
        for(int j=0;j<=aux;j=j+2){
            numMal_rep[aux+count+1]=numMal_rep[j]+numMal_rep[j+1];
            count++;
        }
  }
  mergeSort(numMal_rep, 0, aux-1+count);
  // NUMEROS MALUCOS ORDENADOS
  /*for(i=0;i<N;i++){
      printf("%d ",numMal[i]);   
    }*/
  

  // SOMANDO OS ELEMENTOS 
  for(j=0;j<N;j=j+2){
    numMal[N+soma] = numMal[j] + numMal[j+1]; 
    soma++;
  }
  // ordenando a soma
  mergeSort(numMal, 0, (N + soma)-1);
  /*for(int k=0;k<N + soma;k++){
      printf("\n%d ",numMal[k]);
      cont++;  
  }*/
  numMal_rep2[0]=numMal_rep[0];
 
  for(int g=0;g<aux+count+1;g++){
    if(buscaBin(numMal_rep2, 0, aux2, numMal_rep[g])==-1){
            numMal_rep2[aux2]=numMal_rep[g];
            aux2++;
        }
    }
    if(numMal_rep2[aux2-1]==0){ 
        for(int i = 0;i<aux2-1; i=i+4)
            printf("%d\n", numMal_rep2[i]);
        printf("Elementos: %d\n", aux2-1);
    }
    
    else{
      for(int k=0;k<aux2;k=k+4){
        printf("\n%d ",numMal_rep2[k]);
      }
    printf("\nElementos: %d",aux2);
  
  }
  return 0;
}