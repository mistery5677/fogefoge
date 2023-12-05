#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pacman.h"
#include "mapa.h"

//matriz de 5 linhas por 10 clounas
//struct mapa m; //Antes de utilizar o 'typedef'
MAPA m; //Utilizamos o 'typedef' na pasta "pacman.h"
POSICAO heroi;

int praondeofantasmavai(int xatual, int yatual, int* xdestino, int* ydestino){
    
    int opcoes[4][2] = {
        { xatual, yatual + 1},
        { xatual + 1, yatual},
        { xatual, yatual - 1},
        { xatual - 1, yatual}
    };

    srand(time(0));
    for(int i = 0; i < 10; i++) {
        int posicao = rand () % 4;

        if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];

            return 1;
        }
    }
}

void fantasmas() {
    MAPA copia;

    copiamapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){
            
            int xdestino;
            int ydestino;

            int encontrou = praondeofantasmavai(i, j, &xdestino, &ydestino);

            if(encontrou) {
                andanomapa(&m, i, j, xdestino, ydestino);
            }

            /*if(copia.matriz[i][j] == FANTASMA){
                if(ehvalida(&m, i, j+1) && ehvazia(&m, i, j+1)) {
                    andanomapa(&m, i, j, i, j+1);
                }
            }*/ //Vai fazer o mapa andar apenas para a direita, e detetar se é fim ou se tem alguma parede no mapa
        }
    }
    liberamapa(&copia);
}

int acabou(){
        POSICAO pos;
        int pacmannomapa = encontramapa(&m, &pos, HEROI);
        return !pacmannomapa;
}

int ehdirecao(char direcao){
        return direcao == 'a' ||
        direcao == 'w' ||
        direcao == 's' ||
        direcao == 'd';//Utilizamos esta expressão para proibir o utilizador de utilizar outras teclas
}

void move (char direcao) {
    
    if(direcao == 'q'){
        exit(1);
    }
    
    if(!ehdirecao(direcao)) {
        return;
        } //Utilizamos esta expressão para proibir o utilizador de utilizar outras teclas
    
    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch(direcao) {
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case DIREITA:
            proximoy++;
            break;
        case BAIXO:
            proximox++;
            break;
    }

    if(!podeandar(&m, HEROI, proximox, proximoy))
        return;

    andanomapa(&m, heroi.x, heroi.y,
        proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;

    //m.matriz[heroi.x][heroi.y] = '.'; Nós colocamos esta condição, para não ficar com dois '@' no mapa, um na posição atual e outro na nova posição
}

int main() {
 
    lemapa(&m);
    encontramapa(&m, &heroi, HEROI);

    do {

        imprimemapa(&m);

        char comando;
        scanf(" %c", &comando);
        
        move(comando);
        fantasmas();

    } while(!acabou());

    /*for(int i = 0; i < 5; i++){
        for(int j = 0; j < 10; j++){
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }*/ // O código vai ter o mesmo objetivo, mas vai dar print palavra por palavra

    /*mapa[0][0] = '|';
    mapa[4][9] = '@';

    printf("%c %c", mapa[0][0], mapa[4][9])*/
    liberamapa(&m);
}