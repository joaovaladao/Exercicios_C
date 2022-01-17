#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned long int atual;
    unsigned long int ant;
    unsigned long int prox;
} node;

int main(void)
{
    int i = 0, n = 0;
    node no1, no2;
    node *v = malloc(250000 * sizeof(node));
    unsigned long int vetRem[200] = {};
    int posRem = 0;

    while (scanf("%lx %lx %lx", &v[n].atual, &v[n].ant, &v[n].prox) != EOF)
    {
        if (n == 0)
        {
            no1 = v[n];
            vetRem[posRem] = v[n].atual;
            posRem++;
        }
        else if (n == 1)
        {
            no2 = v[n];
            vetRem[posRem] = v[n].atual;
            posRem++;
        }
        else if(v[n].atual == no1.atual || v[n].atual == no2.atual){
            //printf("Remover\n");
            vetRem[posRem] = v[n].atual;
            v[n].atual = 0;
            v[n].prox = 0;
            v[n].ant = 0;
            posRem++;
        }
        else if(v[n].atual > no1.atual && v[n].atual < no2.atual){
            //printf("Remover\n");
            vetRem[posRem] = v[n].atual;
            v[n].atual = 0;
            v[n].prox = 0;
            v[n].ant = 0;
            posRem++;
        }
        //printf("%lx - ", v[n].atual);
        n++;
    }

    //printf("\nAcabou de ler!\n");

    for(int j = 2; j < n; j++){
        if(v[j].atual == 0 && v[j].ant == 0 && v[j].prox == 0)
            continue;
        else
        printf("%lx %lx %lx\n",v[j].atual,v[j].ant,v[j].prox);
    }

    printf("\n");

        for(int k = 0; k < posRem; k++){
        printf("%lx\n",vetRem[k]);
    }
    return 0;
}