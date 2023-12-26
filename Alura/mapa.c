#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void copiamapa(MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocamapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]); //Vai varrer a linha toda, e copiar o valor "origem", para o "destino"
    }
}

void andanomapa(MAPA* m, int xorigem, int yorigem, 
    int xdestino, int ydestino){

    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xdestino][ydestino] = personagem;
    m->matriz[xorigem][yorigem] = VAZIO;
}

int ehvazia(MAPA*m, int x, int y){
    return m->matriz[x][y] == VAZIO;
}

int ehvalida(MAPA*m, int x, int y){
    if(x >= m->linhas)
        return 0;
    if(y >= m->colunas)
        return 0;
    
    return 1;
}

int encontramapa(MAPA* m, POSICAO* p, char c){
    // Acha a posição do personagem
    for(int i = 0; i < m->linhas; i++) {
        for(int j = 0; j< m->colunas; j++) {
            if(m->matriz[i][j] == HEROI){
                p->x = i;
                p->y = j;
                return 1;
            }
        }  
    }
    return 0;
}

int ehparede(MAPA* m, int x, int y) {
    return m->matriz[x][y] == PAREDE_VERTICAL ||
        m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int ehpersonagem(MAPA* m, char personagem, int x, int y) {
    return m->matriz[x][y] == personagem;
}

int podeandar(MAPA* m, char personagem,  int x, int y){
    return
        ehvalida(m, x, y) && 
        !ehparede(m, x, y) &&
        !ehpersonagem(m, personagem, x, y);
}

void liberamapa(MAPA* m){
    for (int i = 0; i < (*m).linhas; i++){
        free(m->matriz[i]); //m->matriz é igual a (*m).matriz, é apenas uma forma mais fácil de escrever e etender o código
    }
    free(m->matriz);
}

void alocamapa(MAPA* m){

    m->matriz = malloc(sizeof(char*) * m->linhas);
    for (int i = 0; i < m->linhas; i++){
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1)); //Colocamos o "+1", para poder compensar o '/0' que define o final de uma string
    }
}

void lemapa(MAPA* m){

    FILE* f;
    f = fopen("mapa.txt", "r");

    if (f == 0){
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f, "%d %d", &m->linhas, &m->colunas);
    //printf("linhas %d colunas %d\n", linhas, colunas);

/* Explicação malloc(){
    int* v = malloc(sizeof(int) * 50); //Estamos a pedir ao computador a quantidade de memória necessária, pois o computador não tem informação de quanta memória necessita para rodar o programa
                    //A função do 'sizeof()', é útil para definir quanto é que o sistema vai necessitar, porque um valor de char/int é igual em todos os sistemas
    v[0] = 10;
    v[1] = 12;
    //Com a função acima, pedimos ao computador um array (espaços de memória seguida), para guardar informação.    
    printf("inteiro alocado %d %d\n", v[0], v[1]);

    free(v); //Como no 'fclose()', que usamos para fechar um ficheiro, 'free()' é para fechar o espaço de memória
}
*/

/* Explicação do malloc() em vertente de matriz {

    int** v = malloc(sizeof(int*) * 5); //Aqui estamos a dizer ao sistema que estamos a declarar uma matriz, que é igual a um ponteiro de ponteiros, dai ter 'int** v'
    for(int i = 0; i < 5; i++){ //Estamos a colocar memória nas linhas
        v[i] = malloc(sizeof(int) * 10); //Estamos a colocar mesmória em cada ponto da nossa linha
    }

    v[0][0] = 10;
    v[1][2] = 12;
    printf("inteiro alocado %d %d\n", v[0][0], v[1][2]);

    for(int i = 0; i < 5; i++){
        free(v[i]); //Precisamos de liberar o endereço de memória para todos os pontos na linha
    }
    free(v); // Depois de liberar o espaço da linha, precisamos de liberar o espaço da linha no total
}    
*/
    
    alocamapa(m);

    for(int i = 0; i < 5; i++){
        fscanf(f, "%s", m->matriz[i]); //Está a passar apenas o valor da linha
    }

    fclose(f);
}

/*void imprimemapa(MAPA* m){
    for(int i = 0; i < 5; i++){
        printf("%s\n", m->matriz[i]); //Está a dar print na linha correspondente do 'i'
    }
}*/
