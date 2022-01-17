#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void pos_inic (){

    srand(time(NULL));
    long int coluna_inic = rand() % 20;
    long int linha_inic = rand() % 20;
    printf("Você está na linha: %ld coluna: %ld\n", linha_inic, coluna_inic);

}

typedef struct edazin
{
    long int cord_x, cord_y;
    long int pontos;
} edazin;

edazin vetor_frequencia[100000] = {};
long int vetor_coordenadas[50000] = {};

edazin criaCelula(long int x, long int y, long int z){
    edazin *edazinCriada = malloc(sizeof(edazin));
    edazinCriada -> cord_x = x;
    edazinCriada -> cord_y = y; 
    edazinCriada -> pontos = z; 
    //printf("---------------------------------------------------\n");
    //printf("Edazinho criado - cord_x: %d - cord_y: %d pontuação: %d\n",edazinCriada->cord_x, edazinCriada->cord_y, edazinCriada-> pontos);
    //printf("---------------------------------------------------\n");

        return *edazinCriada;
}

void sondar_direita(edazin x){
   
        printf("sondar %ld %ld\n", x.cord_x, x.cord_y+1);

}

void sondar_esquerda(edazin x){
   
        printf("sondar %ld %ld\n", x.cord_x, x.cord_y-1);

}

void sondar_baixo(edazin x){

        printf("sondar %ld %ld\n", x.cord_x+1, x.cord_y);

}

void sondar_cima(edazin x){
   
        printf("sondar %ld %ld\n", x.cord_x-1, x.cord_y);

}

void sondar_diagonal_up_esquerda(edazin x){
   
        printf("sondar %ld %ld\n", x.cord_x-1, x.cord_y-1);

}

void sondar_diagonal_up_direita(edazin x){
   
        printf("sondar %ld %ld\n", x.cord_x+1, x.cord_y-1);

}

void sondar_diagonal_down_esquerda(edazin x){
   
        printf("sondar %ld %ld\n", x.cord_x-1, x.cord_y+1);

}

void sondar_diagonal_down_direita(edazin x){
   
        printf("sondar %ld %ld\n", x.cord_x+1, x.cord_y+1);

}

void dominar(edazin x){
   
        printf("dominar %ld %ld\n", x.cord_x, x.cord_y);

}

int main() {

    //pos_inic();
    //edazin vetor_edazinhos[100];
    long int linha, coluna, turnos;
    long int contador_de_turnos, pontos_totais;
    scanf("%ld %ld %ld %ld", &linha, &coluna, &pontos_totais, &turnos);

    //vetor_coordenadas[linha*10 + coluna]++;
    edazin primeiro = criaCelula(linha, coluna, pontos_totais);
    edazin segundo = criaCelula(linha, coluna, pontos_totais);
    edazin terceiro = criaCelula(linha, coluna, pontos_totais);
    //vetor_edazinhos[0] = primeiro;

    long int pontos_atuais = 0, qtd_eda = 1;

    for(contador_de_turnos = 1; contador_de_turnos <= turnos; contador_de_turnos++){

        long int scan_linha, scan_coluna;
        char scan_resposta[10];

        if(contador_de_turnos == 1){
            sondar_baixo(primeiro);
            //printf("sondar %ld %ld\n", linha, coluna+1);
            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            segundo.cord_x = scan_linha;
            segundo.cord_y = scan_coluna;

        }

        else if(contador_de_turnos == 2){
            dominar(segundo);
            sondar_direita(segundo);
            //printf("sondar %ld %ld\n", linha, coluna+1);
            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld", scan_resposta, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            segundo.cord_x = scan_linha;
            segundo.cord_y = scan_coluna;

        }

        else {
            if(contador_de_turnos%2 == 1){
                dominar(segundo);
                sondar_esquerda(primeiro);
                sondar_cima(primeiro);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                long int linha_up, coluna_up, pontos_up;

                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &linha_up, &coluna_up, &pontos_up);

                if(pontos_atuais>=pontos_up){
                    primeiro.cord_x = scan_linha;
                    primeiro.cord_y = scan_coluna;
                }
                else {
                    primeiro.cord_x = linha_up;
                    primeiro.cord_y = coluna_up;
                }
            }
            else{
                dominar(primeiro);
                sondar_direita(segundo);
                sondar_baixo(segundo);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                long int linha_up, coluna_up, pontos_up;

                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &linha_up, &coluna_up, &pontos_up);

                if(pontos_atuais>=pontos_up){
                    segundo.cord_x = scan_linha;
                    segundo.cord_y = scan_coluna;
                }
                else {
                    segundo.cord_x = linha_up;
                    segundo.cord_y = coluna_up;
                }
            }
        }
            
    }
    //printf("Pontos: %d\n", pontos_totais);



    return 0;
}