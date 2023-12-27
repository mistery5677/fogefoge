#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "pacman2.h"

MAP m;
MAP copy;
HERO_POSITION hero_position;
GHOST_POSITION ghost_position;

void move_hero(char direction)
{

    int next_x = hero_position.x;
    int next_y = hero_position.y;

    switch (direction)
    {
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

    if (!wall(&m, next_x, next_y))
    {
        m.matrix[hero_position.x][hero_position.y] = EMPTY;
        hero_position.x = next_x;
        hero_position.y = next_y;
        m.matrix[next_x][next_y] = HERO;
    }
}

void ghost(MAP* m, MAP* copy)
{
    copy_map(copy, m);

    int random = 0;

    for(int i = 0; i < copy->lines; i++){
        for(int j = 0; j < copy->columns; j++){
            if(copy->matrix[i][j] == GHOST){
                for(int l = 0; l < 4; l++){
                    random = rand() % 4;
                    printf("%d\n", random);
                }
            }
        }
    }
}

/*void move_ghost(MAP* m, GHOST_POSITION* ghost_position){ 
    
    int next_x = ghost_position->x;
    int next_y = ghost_position->y;

    switch (0){
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

    if(!wall(&m, next_x, next_y)){
        m->matrix[ghost_position->x][ghost_position->y] = EMPTY;
        ghost_position->x = next_x;
        ghost_position->y = next_y;  
        m->matrix[next_x][next_y] = GHOST;
    }
}*/

int finish()
{
    return 0;
}

int main()
{
    read_map(&m, &hero_position); // Read the entire map, and locates the hero (already has the memmory allocated)
    do
    {
        draw_map(&m); // Draw the map

        printf("What is your move?\n");

        char move;
        scanf(" %c", &move); // Gives the option to player plays
        move_hero(move);    // The fuction gets the move, from the player, and move the hero

        ghost(&m, &copy);

    } while (!finish());

    free_map(&m);
}