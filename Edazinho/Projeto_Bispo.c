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
    edazin central = criaCelula(linha, coluna, pontos_totais);
    edazin primeiro = criaCelula(linha, coluna, pontos_totais);
    edazin segundo = criaCelula(linha, coluna, pontos_totais);
    edazin terceiro = criaCelula(linha, coluna, pontos_totais);
    edazin quarto = criaCelula(linha, coluna, pontos_totais);
    //vetor_edazinhos[0] = primeiro;

    long int pontos_atuais = 0, qtd_eda = 1;
    char controler[2];

    for(contador_de_turnos = 1; contador_de_turnos <= turnos; contador_de_turnos++){

        long int scan_linha, scan_coluna;
        char scan_resposta[10];

        if(contador_de_turnos == 1){
            sondar_baixo(central);

            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            primeiro.cord_x = scan_linha;
            primeiro.cord_y = scan_coluna;

        }

        else if(contador_de_turnos == 2){
            dominar(primeiro);
            controler[0] = 'p';
            sondar_cima(central);

            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld", scan_resposta, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            segundo.cord_x = scan_linha;
            segundo.cord_y = scan_coluna;

        }

        else if(contador_de_turnos == 3){
            dominar(segundo);
            controler[1] = 's';
            sondar_direita(central);
            sondar_baixo(primeiro);

            printf("fimturno\n");
            fflush(stdout);

            long int linha_aux, coluna_aux, pontos_aux;

            scanf("%s %ld", scan_resposta, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &linha_aux, &coluna_aux, &pontos_aux);
            terceiro.cord_x = scan_linha;
            terceiro.cord_y = scan_coluna;
            primeiro.cord_x = scan_linha;
            primeiro.cord_y = scan_coluna;

        }

        else {
            int nao_pode_primeiro = 0, nao_pode_segundo = 0, nao_pode_terceiro = 0;
            if(contador_de_turnos == 4){
                if(primeiro.pontos >= terceiro.pontos){
                    dominar(primeiro);
                    controler[0] = controler[1];
                    controler[1] = 'p';
                    nao_pode_primeiro = 1;
                }
                else{
                    dominar(terceiro);
                    controler[0] = controler[1];
                    controler[1] = 't';
                    nao_pode_terceiro = 1;
                }
            }
            else if(primeiro.pontos >= segundo.pontos && primeiro.pontos >= terceiro.pontos){
                dominar(primeiro);
                    controler[0] = controler[1];
                    controler[1] = 'p';
                nao_pode_primeiro = 1;
            }
            else if(segundo.pontos >= primeiro.pontos && segundo.pontos >= terceiro.pontos){
                dominar(segundo);
                    controler[0] = controler[1];
                    controler[1] = 's';
                nao_pode_segundo = 1;
            }
            else{
                dominar(terceiro);
                    controler[0] = controler[1];
                    controler[1] = 't';
                nao_pode_terceiro = 1;
            }
            if(controler[0] == 's' && nao_pode_segundo == 0){
                sondar_cima(segundo);
                sondar_direita(segundo);

                printf("fimturno\n");
                fflush(stdout);

                long int linha_aux, coluna_aux, pontos_aux;

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &linha_aux, &coluna_aux, &pontos_aux);
                if(pontos_atuais >= pontos_aux){
                    segundo.cord_x = scan_linha;
                    segundo.cord_y = scan_coluna;
                }
                else{
                    segundo.cord_x = linha_aux;
                    segundo.cord_y = coluna_aux;
                }

            }
            else if(controler[0] == 't' && nao_pode_terceiro == 0){
                sondar_direita(terceiro);
                sondar_baixo(terceiro);

                printf("fimturno\n");
                fflush(stdout);

                long int linha_aux, coluna_aux, pontos_aux;

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &linha_aux, &coluna_aux, &pontos_aux);
                if(pontos_atuais >= pontos_aux){
                    terceiro.cord_x = scan_linha;
                    terceiro.cord_y = scan_coluna;
                }
                else{
                    terceiro.cord_x = linha_aux;
                    terceiro.cord_y = coluna_aux;
                }
            }
            else{
                if(nao_pode_primeiro == 0){
                    sondar_baixo(primeiro);
                    sondar_esquerda(primeiro);

                    printf("fimturno\n");
                    fflush(stdout);

                    long int linha_aux, coluna_aux, pontos_aux;

                    scanf("%s %ld", scan_resposta, &pontos_atuais);
                    scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
                    scanf("%s %ld %ld %ld", scan_resposta, &linha_aux, &coluna_aux, &pontos_aux);
                    if(pontos_atuais >= pontos_aux){
                        primeiro.cord_x = scan_linha;
                        primeiro.cord_y = scan_coluna;
                    }
                    else{
                        primeiro.cord_x = linha_aux;
                        primeiro.cord_y = coluna_aux;
                    }

                }
                else{
                    sondar_direita(terceiro);
                    sondar_baixo(terceiro);

                    printf("fimturno\n");
                    fflush(stdout);

                    long int linha_aux, coluna_aux, pontos_aux;

                    scanf("%s %ld", scan_resposta, &pontos_atuais);
                    scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
                    scanf("%s %ld %ld %ld", scan_resposta, &linha_aux, &coluna_aux, &pontos_aux);
                    if(pontos_atuais >= pontos_aux){
                        terceiro.cord_x = scan_linha;
                        terceiro.cord_y = scan_coluna;
                    }
                    else{
                        terceiro.cord_x = linha_aux;
                        terceiro.cord_y = coluna_aux;
                    }
                }
            }
        }
            
    }

    return 0;
}