#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void alloc_map(MAP* m){

    m->matrix = malloc(sizeof(char*) * m->lines);
    for(int i = 0; i < m->lines; i++) {
        m->matrix[i] = malloc(sizeof(char) * (m->columns + 1));
    }
}

void free_map(MAP* m){
    for (int i = 0; i < m->lines; i++) {
        free(m->matrix[i]);
    }
    free(m->matrix);
}

void read_map(MAP* m, HERO_POSITION* hero_position){

    FILE* f;
    f = fopen("mapa.txt", "r");

    if (f == 0){
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f, "%d %d", &m->lines, &m->columns);

    alloc_map(m);

    for(int i = 0; i < m->lines; i++){
        fscanf(f, "%s", m->matrix[i]);
    }

    find_hero(m, hero_position);

    fclose(f);
}

void draw_map(MAP* m){
    for(int i = 0; i < m->lines; i++){
        printf("%s\n", m->matrix[i]);
    }
}

// Functions to read and draw the map

void find_hero(MAP* m, HERO_POSITION* hero_position){
    
    for(int i = 0; i < m->lines; i++){
        for(int j = 0; j < m->columns; j++){
            
            if(m->matrix[i][j] == HERO){
                hero_position->x = i;
                hero_position->y = j;
                break;
            }
        }
    }
}

// Find the hero;

int wall(MAP*m, int next_movex, int next_movey){
    if(m->matrix[next_movex][next_movey] == VERTICAL_WALL ||
        m->matrix[next_movex][next_movey] == HORIZONTAL_WALL){
        
        return 1;
    }
    return 0;
}

//Verify if there is any wall

void ghost(MAP* m, GHOST_POSITION* ghost_position){

    int random = 0;

    for(int i = 0; i < m->lines; i++){
        for(int j = 0; j < m->columns; j++){
            if(m->matrix[i][j] == GHOST) {
                printf("encontrou\n");

            }
        }
    }
}

void move_ghost(MAP* m, GHOST_POSITION* ghost_position, int direction){
    
    int next_x = ghost_position->x;
    int next_y = ghost_position->y;

    switch (direction){
    case 0: //up
        next_x--; 
        break;

    case 1: //down
        next_x++;
        break;

    case 2: //left
        next_y--;        
        break;

    case 3: //right
        next_y++;
        break;
    }

    if(!wall(m, next_x, next_y)){
        m->matrix[ghost_position->x][ghost_position->y] = EMPTY;
        ghost_position->x = next_x;
        ghost_position->y = next_y;  
        m->matrix[next_x][next_y] = GHOST;
    }
}