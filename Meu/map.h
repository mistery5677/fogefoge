#define HERO '@'
#define EMPTY '.'
#define GHOST 'F'
#define VERTICAL_WALL '-'
#define HORIZONTAL_WALL '|'

struct map{ 
    char** matrix;
    int lines;
    int columns;
};

typedef struct map MAP;

struct hero_position{ 
    int x;
    int y;
};

typedef struct hero_position HERO_POSITION;

struct ghost_position{ 
    int x;
    int y;
};

typedef struct ghost_position GHOST_POSITION;

void alloc_map(MAP* m);
void free_map(MAP* m);
void read_map(MAP* m, HERO_POSITION* hero_position);
void draw_map(MAP* m);
//Read and draw map;

void find_hero(MAP* m, HERO_POSITION* hero_position);

int wall(MAP*m, int next_movex, int next_movey);


void move_ghost(MAP* m, GHOST_POSITION* ghost_position, int direction); //Moves the ghosts

void copy_map(MAP* destiny, MAP* origin);
