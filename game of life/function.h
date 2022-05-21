int x, y;

int init(int way);
void drawscreen(int way);
int fileinit(FILE *file, int **initcells, int **cells);
int drawplay(int way);
int clickinit(int **initcells, int **cells);
void drawlife(int **cells);
void update(int **cells, int **newcells);
int gameover(int **cells, int **newcells, int **newnewcells);
void store(FILE *file, int **initcells, int **cells);
void destroy();