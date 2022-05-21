// int x, y;

int init(int way);
void drawscreen(int way, int x, int y);
int fileinit(FILE *file, int **initcells, int **cells, int x, int y);
int drawplay(int way);
int clickinit(int **initcells, int **cells, int x, int y);
void drawlife(int **cells, int x, int y);
void update(int **cells, int **newcells, int x, int y);
int gameover(int **cells, int **newcells, int **newnewcells, int x, int y);
void store(FILE *file, int **initcells, int **cells, int x, int y);
void destroy();