int x, y;

void init(FILE *file, int initcells[256][256], int cells[256][256]);
void drawscreen();
void drawlife(int cells[256][256]);
void update(int cells[256][256], int newcells[256][256]);
bool gameover(int cells[256][256], int newcells[256][256]);
void store(FILE *file, int initcells[256][256], int cells[256][256]);
void destroy();