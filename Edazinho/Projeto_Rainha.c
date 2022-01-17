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
    edazin direita = criaCelula(linha, coluna, pontos_totais);
    edazin diag_direita_up = criaCelula(linha, coluna, pontos_totais);
    edazin cima = criaCelula(linha, coluna, pontos_totais);
    edazin diag_esquerda_up = criaCelula(linha, coluna, pontos_totais);
    edazin esquerda = criaCelula(linha, coluna, pontos_totais);
    edazin diag_esquerda_down = criaCelula(linha, coluna, pontos_totais);
    edazin baixo = criaCelula(linha, coluna, pontos_totais);
    edazin diag_direita_down = criaCelula(linha, coluna, pontos_totais);
    //vetor_edazinhos[0] = primeiro;

    char controler, vetor_controler[2];

    long int pontos_atuais = 0, qtd_eda = 1;

    for(contador_de_turnos = 1; contador_de_turnos <= turnos; contador_de_turnos++){

        long int scan_linha, scan_coluna;
        char scan_resposta[10];

        if(contador_de_turnos == 1){
            sondar_direita(direita);
            //printf("sondar %ld %ld\n", linha, coluna+1);
            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

            direita.cord_x = scan_linha;
            direita.cord_y = scan_coluna;
            direita.pontos = pontos_atuais;

        }

        else if(contador_de_turnos == 2){
            dominar(direita);
            sondar_diagonal_up_direita(diag_direita_up);
            //printf("sondar %ld %ld\n", linha, coluna+1);
            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld", scan_resposta, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

            diag_direita_up.cord_x = scan_linha;
            diag_direita_up.cord_y = scan_coluna;
            diag_direita_up.pontos = pontos_atuais;

        }

        else if(contador_de_turnos == 3){
            dominar(diag_direita_up);
            sondar_cima(cima);
            sondar_diagonal_up_esquerda(diag_esquerda_up);
            //printf("sondar %ld %ld\n", linha, coluna+1);
            printf("fimturno\n");
            fflush(stdout);

            long int linha_up, coluna_up, pontos_up;

            scanf("%s %ld", scan_resposta, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &linha_up, &coluna_up, &pontos_up);

            cima.cord_x = scan_linha;
            cima.cord_y = scan_coluna;
            cima.pontos = pontos_atuais;

            diag_esquerda_up.cord_x = linha_up;
            diag_esquerda_up.cord_y = coluna_up;
            diag_esquerda_up.pontos = pontos_up;

            //printf("l: %ld c: %ld p: %ld\n", diag_esquerda_up.cord_x, diag_esquerda_up.cord_y, diag_esquerda_up.pontos);

        }

        else if(contador_de_turnos == 4){
            if(cima.pontos >= diag_esquerda_up.pontos){
                dominar(cima);
                controler = 'C';
            }
            else{
                dominar(diag_esquerda_up);
                controler = 'y';
            }

            vetor_controler[0] = controler;

            sondar_esquerda(esquerda);
            sondar_diagonal_down_esquerda(diag_esquerda_down);
            sondar_baixo(baixo);
            printf("fimturno\n");
            fflush(stdout);

            long int linha_up, coluna_up, pontos_up;
            long int linha_down, coluna_down, pontos_down;

            scanf("%s %ld", scan_resposta, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &linha_up, &coluna_up, &pontos_up);
            scanf("%s %ld %ld %ld", scan_resposta, &linha_down, &coluna_down, &pontos_down);

            esquerda.cord_x = scan_linha;
            esquerda.cord_y = scan_coluna;
            esquerda.pontos = pontos_atuais;

            diag_esquerda_down.cord_x = linha_up;
            diag_esquerda_down.cord_y = coluna_up;
            diag_esquerda_down.pontos = pontos_up;

            baixo.cord_x = linha_down;
            baixo.cord_y = coluna_down;
            baixo.pontos = pontos_down;

        }


        else if(contador_de_turnos == 5){
            if(esquerda.pontos >= diag_esquerda_down.pontos && esquerda.pontos >= baixo.pontos){
                dominar(esquerda);
                controler = 'E';
            }
            else if(diag_esquerda_down.pontos > esquerda.pontos && diag_esquerda_down.pontos > baixo.pontos){
                dominar(diag_esquerda_down);
                controler = 'x';
            }
            else {
                dominar(baixo);
                controler = 'B';
            }

            vetor_controler[1] = controler;

            if(vetor_controler[0] == 'C'){
                sondar_cima(cima);
            }
            else{
                sondar_diagonal_up_esquerda(diag_esquerda_up);
            }

            sondar_diagonal_down_direita(diag_direita_down);
            sondar_direita(direita);
            sondar_diagonal_up_direita(diag_direita_up);
            printf("fimturno\n");
            fflush(stdout);

            long int linha_up, coluna_up, pontos_up;
            long int linha_down, coluna_down, pontos_down;
            long int linha_esp, coluna_esp, pontos_esp;

            scanf("%s %ld", scan_resposta, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &linha_esp, &coluna_esp, &pontos_esp);
            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);
            scanf("%s %ld %ld %ld", scan_resposta, &linha_up, &coluna_up, &pontos_up);
            scanf("%s %ld %ld %ld", scan_resposta, &linha_down, &coluna_down, &pontos_down);

            diag_direita_down.cord_x = scan_linha;
            diag_direita_down.cord_y = scan_coluna;
            diag_direita_down.pontos = pontos_atuais;

            direita.cord_x = linha_up;
            direita.cord_y = coluna_up;
            direita.pontos = pontos_up;

            diag_direita_up.cord_x = linha_down;
            diag_direita_up.cord_y = coluna_down;
            diag_direita_up.pontos = pontos_down;

            if(vetor_controler[0] == 'C'){
                cima.cord_x = linha_esp;
                cima.cord_y = coluna_esp;
                cima.pontos = pontos_esp;
            }
            else{
                diag_esquerda_up.cord_x = linha_esp;
                diag_esquerda_up.cord_y = coluna_esp;
                diag_esquerda_up.pontos = pontos_esp;
            }

        }


        else{
            char aux;
            aux = vetor_controler[1];
            vetor_controler[0] = aux;

            if(diag_direita_down.pontos >= direita.pontos && diag_direita_down.pontos >= diag_direita_up.pontos && diag_direita_down.pontos >= cima.pontos && diag_direita_down.pontos >= diag_esquerda_up.pontos && diag_direita_down.pontos >= esquerda.pontos && diag_direita_down.pontos >= diag_esquerda_down.pontos && diag_direita_down.pontos >= baixo.pontos){
                if(controler != 'w'){
                    dominar(diag_direita_down);
                    controler = 'w';
                }
                else{
                    dominar(direita);
                    controler = 'D';
                }
            }

            else if(direita.pontos >= diag_direita_up.pontos && direita.pontos >= cima.pontos && direita.pontos >= diag_esquerda_up.pontos && direita.pontos >= esquerda.pontos && direita.pontos >= diag_esquerda_down.pontos && direita.pontos >= baixo.pontos && direita.pontos >= diag_direita_down.pontos){
                if(controler != 'D'){
                    dominar(direita);
                    controler = 'D';
                }
                else{
                    dominar(diag_direita_up);
                    controler = 'z';
                }
            }

            else if(diag_direita_up.pontos >= cima.pontos && diag_direita_up.pontos >= diag_esquerda_up.pontos && diag_direita_up.pontos >= esquerda.pontos && diag_direita_up.pontos >= diag_esquerda_down.pontos && diag_direita_up.pontos >= baixo.pontos && diag_direita_up.pontos >= diag_direita_down.pontos && diag_direita_up.pontos >= direita.pontos){
                if(controler != 'z'){
                    dominar(diag_direita_up);
                    controler = 'z';
                }
                else{
                    dominar(cima);
                    controler = 'C';
                }
            }

            else if(cima.pontos >= diag_esquerda_up.pontos && cima.pontos >= esquerda.pontos && cima.pontos >= diag_esquerda_down.pontos && cima.pontos >= baixo.pontos && cima.pontos >= diag_direita_down.pontos && cima.pontos >= direita.pontos && cima.pontos >= diag_direita_up.pontos){
                if(controler != 'C'){
                    dominar(cima);
                    controler = 'C';
                }
                else{
                    dominar(diag_esquerda_up);
                    controler = 'y';
                }
            }

            else if(diag_esquerda_up.pontos >= esquerda.pontos && diag_esquerda_up.pontos >= diag_esquerda_down.pontos && diag_esquerda_up.pontos >= baixo.pontos && diag_esquerda_up.pontos >= diag_direita_down.pontos && diag_esquerda_up.pontos >= direita.pontos && diag_esquerda_up.pontos >= diag_direita_up.pontos && diag_esquerda_up.pontos >= cima.pontos){
                if(controler != 'y'){
                    dominar(diag_esquerda_up);
                    controler = 'y';
                }
                else{
                    dominar(esquerda);
                    controler = 'E';
                }
            }

            else if(esquerda.pontos >= diag_esquerda_down.pontos && esquerda.pontos >= baixo.pontos && esquerda.pontos >= diag_direita_down.pontos && esquerda.pontos >= direita.pontos && esquerda.pontos >= diag_direita_up.pontos && esquerda.pontos >= cima.pontos && esquerda.pontos >= diag_esquerda_up.pontos){
                if(controler != 'E'){
                    dominar(esquerda);
                    controler = 'E';
                }
                else{
                    dominar(diag_esquerda_down);
                    controler = 'x';
                }
            }

            else if(diag_esquerda_down.pontos >= baixo.pontos && diag_esquerda_down.pontos >= diag_direita_down.pontos && diag_esquerda_down.pontos >= direita.pontos && diag_esquerda_down.pontos >= diag_direita_up.pontos && diag_esquerda_down.pontos >= cima.pontos && diag_esquerda_down.pontos >= diag_esquerda_up.pontos && diag_esquerda_down.pontos >= esquerda.pontos){
                if(controler != 'x'){
                    dominar(diag_esquerda_down);
                    controler = 'x';
                }
                else{
                    dominar(baixo);
                    controler = 'B';
                }
            }

            else {
                if(controler != 'B'){
                    dominar(baixo);
                    controler = 'B';
                }
                else{
                    dominar(diag_direita_down);
                    controler = 'w';
                }
            }

            vetor_controler[1] = controler;

//-----------------------------------------------------

            if(vetor_controler[0] == 'D'){
                sondar_direita(direita);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                direita.cord_x = scan_linha;
                direita.cord_y = scan_coluna;
                direita.pontos = pontos_atuais;
            }

            else if(vetor_controler[0] == 'z'){
                sondar_diagonal_up_direita(diag_direita_up);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                diag_direita_up.cord_x = scan_linha;
                diag_direita_up.cord_y = scan_coluna;
                diag_direita_up.pontos = pontos_atuais;
            }

            else if(vetor_controler[0] == 'C'){
                sondar_cima(cima);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                cima.cord_x = scan_linha;
                cima.cord_y = scan_coluna;
                cima.pontos = pontos_atuais;
            }

            else if(vetor_controler[0] == 'y'){
                sondar_diagonal_up_esquerda(diag_esquerda_up);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                diag_esquerda_up.cord_x = scan_linha;
                diag_esquerda_up.cord_y = scan_coluna;
                diag_esquerda_up.pontos = pontos_atuais;
            }

            else if(vetor_controler[0] == 'E'){
                sondar_esquerda(esquerda);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                esquerda.cord_x = scan_linha;
                esquerda.cord_y = scan_coluna;
                esquerda.pontos = pontos_atuais;
            }

            else if(vetor_controler[0] == 'x'){
                sondar_diagonal_down_esquerda(diag_esquerda_down);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                diag_esquerda_down.cord_x = scan_linha;
                diag_esquerda_down.cord_y = scan_coluna;
                diag_esquerda_down.pontos = pontos_atuais;
            }

            else if(vetor_controler[0] == 'B'){
                sondar_baixo(baixo);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                baixo.cord_x = scan_linha;
                baixo.cord_y = scan_coluna;
                baixo.pontos = pontos_atuais;
            }
                        
            else if(vetor_controler[0] == 'w'){
                sondar_diagonal_down_direita(diag_direita_down);
                printf("fimturno\n");
                fflush(stdout);

                scanf("%s %ld", scan_resposta, &pontos_atuais);
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_atuais);

                diag_direita_down.cord_x = scan_linha;
                diag_direita_down.cord_y = scan_coluna;
                diag_direita_down.pontos = pontos_atuais;
            }
        }          
    }
    //printf("Pontos: %d\n", pontos_totais);



    return 0;
}