#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "pacman2.h"

MAP m;
HERO_POSITION hero_position;
GHOST_POSITION ghost_position;

void move_hero(char direction){
    
    int next_x = hero_position.x;
    int next_y = hero_position.y;

    switch (direction){
    case 'q':
        exit(1);
    case UP:
        next_x--;
        break;

    case DOWN:
        next_x++;
        break;

    case LEFT:
        next_y--;    
        break;

    case RIGHT:
        next_y++;
        break;
    }

    if(!wall(&m, next_x, next_y)){
        m.matrix[hero_position.x][hero_position.y] = EMPTY;
        hero_position.x = next_x;
        hero_position.y = next_y;  
        m.matrix[next_x][next_y] = HERO;
    }
}

int finish(){
    return 0;
}


int main(){

    int random = 0;
    read_map(&m, &hero_position); //Read the entire map, and locates the hero (already has the memmory allocated)

    do {
    
        draw_map(&m); //Draw the map

        printf("What is your move?\n");

        char move;
        scanf("%c", &move); //Gives the option to player plays
        move_hero(move); //The fuction gets the move, from the player, and move the hero

        ghost(&m, &ghost_position);
    
    }while(!finish());

    free_map(&m);
}