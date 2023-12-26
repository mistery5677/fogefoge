#ifndef _MAPA_H
#define _MAPA_H

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'



//Nós criamos uma "Estrutura", para no caso se precisarmos de fazer um outro mapa, ser mais legivel o nosso código
struct mapa{ 
    char** matriz;
    int linhas;
    int colunas;
};

typedef struct mapa MAPA; //Vai definir um novo nome de uma estrutura, para ser mais fácil de invocar

struct posicao{
    int x;
    int y;
};

typedef struct posicao POSICAO;

void liberamapa(MAPA* m);
void lemapa(MAPA* m);
void alocamapa(MAPA* m);
int encontramapa(MAPA* m, POSICAO* p, char c);
int ehvalida(MAPA*m, int x, int y);
int ehvazia(MAPA*m, int x, int y);
void andanomapa(MAPA* m, int xorigem, int yorigem, 
    int xdestino, int ydestino);
void copiamapa(MAPA* destino, MAPA* origem);
int podeandar(MAPA* m, char personagem,  int x, int y);
int ehparede(MAPA* m, int x, int y);
int ehpersonagem(MAPA* m, char personagem, int x, int y);

#endif