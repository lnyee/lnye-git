#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include"function.h"

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("请输入初始文件！\n");
        return 1;
    }
    char File[40];
    strcpy(File, argv[1]);
    FILE *file = fopen(File, "r");
    if (file == NULL)
    {
        printf("Error\nBook file does not exist: %s\n",File);
        exit(1);
    }
    fscanf(file,"%d\n",&x);
    fscanf(file,"%d\n",&y);
    fscanf(file, "\n");
    int initcells[y][x];
    int cells[y][x];
    int newcells[y][x];

    init(file, initcells, cells);
    fclose(file);

    drawscreen();
    drawlife(cells);    
    SDL_Delay(500);

    if(argc == 2){
        int t = 0;
        while(1){
            update(cells, newcells);
            if(!gameover(cells, newcells)){
                drawscreen();
                drawlife(cells);   
                SDL_Delay(500);
                t++;
            }
            else{
                break;
            }
        }
        printf("迭代%d次\n", t);
    }
    else if(argc == 3){
        int t = 0, times = atoi(argv[2]);
        for(int i=0; i<times; i++){
            update(cells, newcells);
            if(!gameover(cells, newcells)){
                drawscreen();
                drawlife(cells);   
                SDL_Delay(500);
                t++;
            }
            else{
                break;
            }
        }
        if(t == times){
            printf("迭代%d次\n", times);
        }
        else{
            printf("没能迭代%d次，迭代%d次就稳定了\n", times, t);
        }
    }

    FILE *wfile = fopen(File, "w");
    store(wfile, initcells, cells);
    fclose(wfile);

    destroy();

    return 0;
}