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

typedef struct cords
{
    long int cord_x, cord_y;
} cords;

typedef struct coordenadas
{
    cords localizacao[100000];
} coordenadas;

edazin vetor_frequencia[200] = {};
coordenadas coordendas_sondadas[4] = {};

edazin criaCelula(long int x,long int y,long int z){
    edazin *edazinCriada = malloc(sizeof(edazin));
    edazinCriada -> cord_x = x;
    edazinCriada -> cord_y = y; 
    edazinCriada -> pontos = z; 
    //printf("---------------------------------------------------\n");
    //printf("Edazinho criado - cord_x: %d - cord_y: %d pontuação: %d\n",edazinCriada->cord_x, edazinCriada->cord_y, edazinCriada-> pontos);
    //printf("---------------------------------------------------\n");

        return *edazinCriada;
}
int onde_alocar(cords novas_coordenadas){
    long int qtd_coord;
    int quadrante;

    long int linha = novas_coordenadas.cord_x;
    long int coluna = novas_coordenadas.cord_y;

    if(linha >= 0 && coluna >= 0)
     quadrante = 0;

    else if(linha >= 0 && coluna < 0)
     quadrante = 1;

    else if(linha < 0 && coluna < 0) 
     quadrante = 2;

    else 
     quadrante = 3;

    //coordendas_sondadas[quadrante].cordendas[qtd_coord];

    return quadrante;
}

void sondar(edazin x, int *count, long int *count_coord_0, long int *count_coord_1, long int *count_coord_2, long int *count_coord_3){
    long int linha =  x.cord_x;
    long int coluna =  x.cord_y;

    long int vet_possicoes_coluna[6] = {coluna, coluna+1, coluna-1, coluna-1, coluna+1, coluna,};
    long int vet_possicoes_linha[6] = {linha-1, linha, linha, linha+1, linha-1, linha+1,};

        for(int i = 0; i<6; i++){
            cords novas_coordenadas;
            novas_coordenadas.cord_x = vet_possicoes_linha[i];
            novas_coordenadas.cord_y = vet_possicoes_coluna[i];

            int quadrante = onde_alocar(novas_coordenadas);

            int count_coord, ta_ocupado = 0;

            if(quadrante == 0) count_coord = *count_coord_0;

            else if(quadrante == 1) count_coord = *count_coord_1;

            else if(quadrante == 2) count_coord = *count_coord_2;

            else count_coord = *count_coord_3;

            for(int j = 0; j<count_coord; j++){
                if(coordendas_sondadas[quadrante].localizacao[j].cord_x == novas_coordenadas.cord_x && coordendas_sondadas[quadrante].localizacao[j].cord_y == novas_coordenadas.cord_y){
                ta_ocupado = 1;
                break;
                }
            }

            if(ta_ocupado == 1)
                continue;

            else{

                printf("sondar %ld %ld\n", vet_possicoes_linha[i], vet_possicoes_coluna[i]);
                *count = *count + 1;
                cords pos_sondagem = {vet_possicoes_linha[i], vet_possicoes_coluna[i]};

                if(quadrante == 0){
                    coordendas_sondadas[quadrante].localizacao[*count_coord_0].cord_x = vet_possicoes_linha[i];
                    coordendas_sondadas[quadrante].localizacao[*count_coord_0].cord_y = vet_possicoes_coluna[i];
                    *count_coord_0 = *count_coord_0 + 1;
                }
                else if(quadrante == 1){
                    coordendas_sondadas[quadrante].localizacao[*count_coord_1].cord_x = vet_possicoes_linha[i];
                    coordendas_sondadas[quadrante].localizacao[*count_coord_1].cord_y = vet_possicoes_coluna[i];
                    *count_coord_1 = *count_coord_1 + 1;
                }
                else if(quadrante == 2){
                    coordendas_sondadas[quadrante].localizacao[*count_coord_2].cord_x = vet_possicoes_linha[i];
                    coordendas_sondadas[quadrante].localizacao[*count_coord_2].cord_y = vet_possicoes_coluna[i];
                    *count_coord_2 = *count_coord_2 + 1;
                }
                else{
                    coordendas_sondadas[quadrante].localizacao[*count_coord_3].cord_x = vet_possicoes_linha[i];
                    coordendas_sondadas[quadrante].localizacao[*count_coord_3].cord_y = vet_possicoes_coluna[i];
                    *count_coord_3 = *count_coord_3 + 1;
                }

                break;
            }

        }
}

edazin dominar_primeiros_turnos(){

edazin edazin_dominado;

    for(int i=200; i>0; i--){
        if(vetor_frequencia[i].pontos > 0){
            printf("dominar %ld %ld\n", vetor_frequencia[i].cord_x, vetor_frequencia[i].cord_y);
            edazin_dominado = criaCelula(vetor_frequencia[i].cord_x, vetor_frequencia[i].cord_y, vetor_frequencia[i].pontos);
            vetor_frequencia[i].pontos = 0;
            break;
        }
    }
        return edazin_dominado;
}

edazin dominar(edazin mais_baixo, edazin mais_alto, edazin mais_esquerda, edazin mais_direita, int tam_0, int tam_1, int tam_2, int tam_3){

edazin edazin_dominado;
edazin dummy = {0,0,0};
int flag = 0, flag2 = 0, flag3 = 0;
int vetor[4] = {tam_0,tam_1,tam_2,tam_3};

    for(int i=200; i>0; i--){
        if(vetor_frequencia[i].pontos > 0){
            printf("dominar %ld %ld\n", vetor_frequencia[i].cord_x, vetor_frequencia[i].cord_y);
            edazin_dominado = criaCelula(vetor_frequencia[i].cord_x, vetor_frequencia[i].cord_y, vetor_frequencia[i].pontos);
            vetor_frequencia[i].pontos = 0; vetor_frequencia[i].cord_x = 0; vetor_frequencia[i].cord_y = 0;
            flag = 1;
            return edazin_dominado;
        }
    }
    if(flag == 0){
        long int linha = mais_baixo.cord_x;
        long int coluna = mais_baixo.cord_y;
        long int pontos = mais_baixo.pontos;

        int tamanho;

        cords cords_donde_esta = {linha,coluna};
        int donde_esta = onde_alocar(cords_donde_esta);
        tamanho = vetor[donde_esta];

        for(int i=0; i<tamanho; i++){

            if(coordendas_sondadas[donde_esta].localizacao[i].cord_x == linha+1 && coordendas_sondadas[donde_esta].localizacao[i].cord_y == coluna){
                printf("dominar %ld %ld\n", linha+1, coluna);
                edazin_dominado = criaCelula(linha + 1, coluna, pontos);
                return edazin_dominado;
        }
        }
        flag2 = 1;
    }
//Peão
if(flag2 == 1){
        long int linha = mais_alto.cord_x;
        long int coluna = mais_alto.cord_y;
        long int pontos = mais_alto.pontos;

        int tamanho;

        cords cords_donde_esta = {linha,coluna};
        int donde_esta = onde_alocar(cords_donde_esta);
        tamanho = vetor[donde_esta];

        for(int i=0; i<tamanho; i++){

            if(coordendas_sondadas[donde_esta].localizacao[i].cord_x == linha-1 && coordendas_sondadas[donde_esta].localizacao[i].cord_y == coluna){
                printf("dominar %ld %ld\n", linha - 1, coluna);
                edazin_dominado = criaCelula(linha - 1, coluna, pontos);
                return edazin_dominado;
            }
        }
        flag3 = 1;
}
//Esquerda
if(flag3 == 1){
        long int linha = mais_esquerda.cord_x;
        long int coluna = mais_esquerda.cord_y;
        long int pontos = mais_esquerda.pontos;

        int tamanho;

        cords cords_donde_esta = {linha,coluna};
        int donde_esta = onde_alocar(cords_donde_esta);
        tamanho = vetor[donde_esta];

        for(int i=0; i<tamanho; i++){

            if(coordendas_sondadas[donde_esta].localizacao[i].cord_x == linha && coordendas_sondadas[donde_esta].localizacao[i].cord_y == coluna-1){
                printf("dominar %ld %ld\n", linha, coluna-1);
                edazin_dominado = criaCelula(linha, coluna-1, pontos);
                return edazin_dominado;
            }
        }
    }
//Direita
        long int linha = mais_direita.cord_x;
        long int coluna = mais_direita.cord_y;
        long int pontos = mais_direita.pontos;

        int tamanho;

        cords cords_donde_esta = {linha,coluna};
        int donde_esta = onde_alocar(cords_donde_esta);
        tamanho = vetor[donde_esta];

        for(int i=0; i<tamanho; i++){

            if(coordendas_sondadas[donde_esta].localizacao[i].cord_x == linha && coordendas_sondadas[donde_esta].localizacao[i].cord_y == coluna+1){
                printf("dominar %ld %ld\n", linha, coluna+1);
                edazin_dominado = criaCelula(linha, coluna+1, pontos);
                return edazin_dominado;
            }
        }


        return dummy;
}

int main() {

    //pos_inic();
    edazin edazinhos_dominados[7000] = {};
    long int linha, coluna, turnos;
    long int contador_de_turnos, pontos_iniciais;
    scanf("%ld %ld %ld %ld", &linha, &coluna, &pontos_iniciais, &turnos);

    if(pontos_iniciais < 0) pontos_iniciais = pontos_iniciais*-1;
    if(pontos_iniciais >= 200 || pontos_iniciais == 0) pontos_iniciais = 199;

    edazin primeiro = criaCelula(linha, coluna, pontos_iniciais);
    edazin mais_baixo = primeiro;
    edazin mais_alto = primeiro;
    edazin mais_esquerda = primeiro;
    edazin mais_direita = primeiro;
    edazinhos_dominados[0] = primeiro;

    cords first = {linha,coluna};
    int onde = onde_alocar(first);

    coordendas_sondadas[onde].localizacao[0].cord_x = linha;
    coordendas_sondadas[onde].localizacao[0].cord_y = coluna;

    long int qtd_eda = 1, edeazinhos_lotados = 0;
    long int count_coord_0 = 0; if(onde == 0) count_coord_0 = 1;
    long int count_coord_1 = 0; if(onde == 1) count_coord_1 = 1;
    long int count_coord_2 = 0; if(onde == 2) count_coord_2 = 1;
    long int count_coord_3 = 0; if(onde == 3) count_coord_3 = 1;

    for(contador_de_turnos = 1; contador_de_turnos <= turnos; contador_de_turnos++){

        long int scan_linha, scan_coluna;
        char scan_resposta[10];

        if(contador_de_turnos == 1){
            printf("sondar %ld %ld\n", linha+1, coluna+1);
            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_iniciais);

            if(pontos_iniciais < 0) pontos_iniciais = pontos_iniciais*(-1);

                if(vetor_frequencia[pontos_iniciais].pontos > 0){
                    for(int l = pontos_iniciais+1; l<200; l++){
                        if(vetor_frequencia[l].pontos == 0){
                            vetor_frequencia[l].cord_x = scan_linha;
                            vetor_frequencia[l].cord_y = scan_coluna;
                            vetor_frequencia[l].pontos = pontos_iniciais;
                            break;
                        }
                    }

                }
                else{
                    vetor_frequencia[pontos_iniciais].cord_x = scan_linha;
                    vetor_frequencia[pontos_iniciais].cord_y = scan_coluna;
                    vetor_frequencia[pontos_iniciais].pontos = pontos_iniciais;
                }

            coordendas_sondadas[onde].localizacao[1].cord_x = scan_linha;
            coordendas_sondadas[onde].localizacao[1].cord_y = scan_coluna;

            if(onde == 0) count_coord_0++;
            else if(onde == 1) count_coord_1++;
            else if(onde == 2) count_coord_2++;
            else if(onde == 3) count_coord_3++;
        }

        else if(contador_de_turnos <= 4){

            edazinhos_dominados[qtd_eda] = dominar_primeiros_turnos();

            if(edazinhos_dominados[qtd_eda].cord_x > mais_baixo.cord_x && edazinhos_dominados[qtd_eda].cord_y == mais_baixo.cord_y){
                mais_baixo.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_baixo.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_baixo.pontos = edazinhos_dominados[qtd_eda].pontos;
            }
            if(edazinhos_dominados[qtd_eda].cord_x < mais_alto.cord_x && edazinhos_dominados[qtd_eda].cord_y == mais_alto.cord_y){
                mais_alto.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_alto.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_alto.pontos = edazinhos_dominados[qtd_eda].pontos;
            }
            if(edazinhos_dominados[qtd_eda].cord_y < mais_esquerda.cord_y && edazinhos_dominados[qtd_eda].cord_x == mais_esquerda.cord_x){
                mais_esquerda.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_esquerda.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_esquerda.pontos = edazinhos_dominados[qtd_eda].pontos;
            }
            if(edazinhos_dominados[qtd_eda].cord_y > mais_direita.cord_y && edazinhos_dominados[qtd_eda].cord_x == mais_direita.cord_x){
                mais_direita.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_direita.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_direita.pontos = edazinhos_dominados[qtd_eda].pontos;
            }
            int contador_de_prints = 0;

            for(int i = 0; i<qtd_eda; i++){
                if(edazinhos_dominados[i].pontos > 0){
                    sondar(edazinhos_dominados[i], &contador_de_prints, &count_coord_0, &count_coord_1, &count_coord_2, &count_coord_3);
                }
            }

            printf("fimturno\n");
            fflush(stdout);

            scanf("%s %ld", scan_resposta, &pontos_iniciais);

            for(int i = 0; i<contador_de_prints; i++){
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_iniciais);

                if(pontos_iniciais < 0) pontos_iniciais = 2;

                vetor_frequencia[pontos_iniciais].cord_x = scan_linha;
                vetor_frequencia[pontos_iniciais].cord_y = scan_coluna;
                vetor_frequencia[pontos_iniciais].pontos = pontos_iniciais;
                
            }
            qtd_eda++;
        }

        else{
                if(contador_de_turnos > 6)
                    edeazinhos_lotados++;

            int printa_domina = 0;
            edazin dummy = dominar(mais_baixo, mais_alto, mais_esquerda, mais_direita, count_coord_0, count_coord_1, count_coord_2, count_coord_3);

            if(dummy.cord_x == 0 && dummy.cord_y == 0 && dummy.pontos == 0)
                printa_domina = 1;         
            else
                edazinhos_dominados[qtd_eda] = dummy;

            int contador_de_prints = 0;
            
            if(edazinhos_dominados[qtd_eda].cord_x > mais_baixo.cord_x && edazinhos_dominados[qtd_eda].cord_y == mais_baixo.cord_y){
                mais_baixo.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_baixo.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_baixo.pontos = edazinhos_dominados[qtd_eda].pontos;
            }
            if(edazinhos_dominados[qtd_eda].cord_x < mais_alto.cord_x && edazinhos_dominados[qtd_eda].cord_y == mais_alto.cord_y){
                mais_alto.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_alto.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_alto.pontos = edazinhos_dominados[qtd_eda].pontos;
            }
            if(edazinhos_dominados[qtd_eda].cord_y < mais_esquerda.cord_y && edazinhos_dominados[qtd_eda].cord_x == mais_esquerda.cord_x){
                mais_esquerda.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_esquerda.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_esquerda.pontos = edazinhos_dominados[qtd_eda].pontos;
            }
            if(edazinhos_dominados[qtd_eda].cord_y > mais_direita.cord_y && edazinhos_dominados[qtd_eda].cord_x == mais_direita.cord_x){
                mais_direita.cord_y = edazinhos_dominados[qtd_eda].cord_y;
                mais_direita.cord_x = edazinhos_dominados[qtd_eda].cord_x;
                mais_direita.pontos = edazinhos_dominados[qtd_eda].pontos;
            }

            for(int i = edeazinhos_lotados; i<qtd_eda; i++){
                if(edazinhos_dominados[i].pontos > 0){
                    sondar(edazinhos_dominados[i], &contador_de_prints, &count_coord_0, &count_coord_1, &count_coord_2, &count_coord_3);
                }
            }

            printf("fimturno\n");
            fflush(stdout);

            if(printa_domina == 0)
                scanf("%s %ld", scan_resposta, &pontos_iniciais);

            for(int i = 0; i<contador_de_prints; i++){
                scanf("%s %ld %ld %ld", scan_resposta, &scan_linha, &scan_coluna, &pontos_iniciais);

                if(pontos_iniciais > 0){
                    vetor_frequencia[pontos_iniciais].cord_x = scan_linha;
                    vetor_frequencia[pontos_iniciais].cord_y = scan_coluna;
                    vetor_frequencia[pontos_iniciais].pontos = pontos_iniciais;
                }
            }
            qtd_eda++;
        }
    }

//Pontuação: 3762372

    return 0;
}