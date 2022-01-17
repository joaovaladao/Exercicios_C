#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void pos_inic (){

    srand(time(NULL));
    int coluna_inic = rand() % 20;
    int linha_inic = rand() % 20;
    printf("Você está na linha: %d coluna: %d\n", linha_inic, coluna_inic);

}

typedef struct edazin
{
    long int cord_x, cord_y;
    long int pontos;
} edazin;

edazin vetor_frequencia[100000] = {};
long int vetor_coordenadas[50000] = {};

edazin criaCelula(int x, int y, int z){
    edazin *edazinCriada = malloc(sizeof(edazin));
    edazinCriada -> cord_x = x;
    edazinCriada -> cord_y = y; 
    edazinCriada -> pontos = z; 
    //printf("---------------------------------------------------\n");
    //printf("Edazinho criado - cord_x: %d - cord_y: %d pontuação: %d\n",edazinCriada->cord_x, edazinCriada->cord_y, edazinCriada-> pontos);
    //printf("---------------------------------------------------\n");

        return *edazinCriada;
}

long long int concatena(long long int x, long long int y){
    long long int pow = 10;

    while(y >= pow)
        pow *= 10;

    return x * pow + y;
}

long long int sondar(edazin x, int *count){
    long int linha =  x.cord_x;
    long int coluna =  x.cord_y;
    int random = rand() % 5;

    int verificador;
    long long int junta;
    long long int vet_possicoes[6] = {concatena(linha+1,coluna),concatena(linha-1,coluna),concatena(linha,coluna+1),concatena(linha,coluna-1),
    concatena(linha+1,coluna-1),concatena(linha-1,coluna+1)};
    //printf("random = %d\n", random);


        for(int i = random; i<random+6; i++){
            verificador = vet_possicoes[random];
            //printf("verificador = %d\n", verificador);

            if(vetor_coordenadas[verificador] > 0){
                random = (random + 1)%6;
                continue;
            }
            else{
                int aux1, aux2;
                if(random == 0 ) { aux1 = 1; aux2 = 0;}
                else if(random == 1 ) { aux1 = -1; aux2 = 0;}
                else if(random == 2 ) { aux1 = 0; aux2 = 1;}
                else if(random == 3 ) { aux1 = 0; aux2 = -1;}
                else if(random == 4 ) { aux1 = +1; aux2 = -1;}
                else if(random == 5 ) { aux1 = -1; aux2 = +1;}

                printf("sondar %ld %ld\n", linha + aux1, coluna + aux2);
                *count = *count + 1;
                junta = vet_possicoes[random];
                //printf("%lld\n",junta);
                break;
            }

        }

    return junta;
}

edazin dominar(){

edazin edazin_dominado;

    for(int i=50000; i>0; i--){
        if(vetor_frequencia[i].pontos > 0){
            printf("dominar %ld %ld\n", vetor_frequencia[i].cord_x, vetor_frequencia[i].cord_y);
            edazin_dominado = criaCelula(vetor_frequencia[i].cord_x, vetor_frequencia[i].cord_y, vetor_frequencia[i].pontos);
            vetor_frequencia[i].pontos = 0;
            break;
        }
    }
        return edazin_dominado;
}

int main() {

    //pos_inic();
    edazin vetor_edazinhos[100000] = {};
    long int linha, coluna, turnos;
    long int contador_de_turnos, pontos_totais;
    scanf("%ld %ld %ld %ld", &linha, &coluna, &pontos_totais, &turnos);

    vetor_coordenadas[concatena(linha+1,coluna)]++;
    edazin primeiro = criaCelula(linha, coluna, pontos_totais);
    vetor_edazinhos[0] = primeiro;

    long int pontos_atuais = 0, qtd_eda = 1;
    int sem_scan = 0;

    for(contador_de_turnos = 1; contador_de_turnos <= turnos; contador_de_turnos++){

        long int scan_linha, scan_coluna;
        char scan_resposta[10];

        if(contador_de_turnos == 1){
            printf("sondar %ld %ld\n", linha+1, coluna+1);
            printf("fimturno\n");
            fflush(stdout);
            long int junta = concatena(linha+1, coluna+1);
            vetor_coordenadas[junta]++;

            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

            vetor_frequencia[pontos_atuais].cord_x = scan_linha;
            vetor_frequencia[pontos_atuais].cord_y = scan_coluna;
            vetor_frequencia[pontos_atuais].pontos = pontos_atuais;
        }

        else{
            vetor_edazinhos[qtd_eda] = dominar();
            int contador_de_prints = 0;

            for(int i = 0; i<qtd_eda; i++){
                if(vetor_edazinhos[i].pontos > 0){
                    printf("Rodando: %dx\nVetor: %ld\n", i, vetor_edazinhos[i].pontos);
                    long long int res = sondar(vetor_edazinhos[i], &contador_de_prints);
                    //printf("res: %lld\n", res);
                    vetor_coordenadas[res]++;
                    //printf("count: %d\n", contador_de_prints);
                }
            }

            //pontos_totais += vetor_edazinhos[qtd_eda].pontos;
            //printf("Tô rodando pela %dx...\n", contador_de_turnos);
            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld", scan_resposta, &pontos_atuais);

            for(int i = 0; i<contador_de_prints; i++){
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                if(vetor_frequencia[pontos_atuais].pontos == 0 && scan_resposta[0] == 's' && pontos_atuais > 0){
                    vetor_frequencia[pontos_atuais].cord_x = scan_linha;
                    vetor_frequencia[pontos_atuais].cord_y = scan_coluna;
                    vetor_frequencia[pontos_atuais].pontos = pontos_atuais;
                }
                else if(vetor_frequencia[pontos_atuais].pontos == 0 && scan_resposta[0] == 's' && pontos_atuais < 0){
                    vetor_frequencia[0].cord_x = scan_linha;
                    vetor_frequencia[0].cord_y = scan_coluna;
                    vetor_frequencia[0].pontos = pontos_atuais;
                }
            }
            qtd_eda++;
        }
    }



    return 0;
}