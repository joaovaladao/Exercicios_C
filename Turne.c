#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define less(A,B) ((A.atual) < (B.atual))
#define lesseq(A,B) ((A.pos) <= (B.pos))
#define exch(A,B) { int t; t=A.atual;A.atual=B.atual;B.atual=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }

typedef struct{
    char caracter[27];
}item;

int main(){
    char cidade[27];
    item lista[1000001];
    int j = 0;
        
    while (scanf("%s", cidade) != EOF){
        //printf("Comparando %c ----- %c\n",cidade[tam-1], lista[j-1].caracter[tam-1]);
        strcpy(lista[j].caracter,cidade);
        j++;
    }

    int a=0;

    for(int i=0; i<j+a; i++){
        int tam = strlen(lista[i-1].caracter);
        //printf("%s\n", lista[i].caracter);
        //printf("Comparando %c ----- %c\n", lista[i].caracter[0] + 32, lista[i-1].caracter[tam-1]);
        if(lista[i-1].caracter[tam-1] == lista[i].caracter[0] + 32){
            strcpy(lista[j+a].caracter,lista[i].caracter);
            printf("%s\n", lista[i+1].caracter);
            i++;
            a++;
            //printf("Trocou\n");
        }
        else
            printf("%s\n", lista[i].caracter);
    //printf("%s\n", cidade);
    }

    return 0;
}
