#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

int finish();
void move_hero (char direction);
void ghost(MAP* m, MAP* copy);
//void move_ghost(MAP* m, GHOST_POSITION* ghost_position);