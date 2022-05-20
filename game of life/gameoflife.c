#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include"gameoflife.h"
#include"function.h"

void init(FILE *file, int initcells[256][256], int cells[256][256]){
    for (int i=0;i<y;i++){
        for (int j=0;j<x;j++){
            fscanf(file,"%d",&initcells[i][j]);
            cells[i][j] = initcells[i][j];
            getc(file);
        }
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("初始化失败\n");
    }
    else{
        window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
        if(!window){
            printf("窗口创建失败\n");
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);        
        }
    }
}

void drawscreen(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); 

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(int i=1; i<x; i++){
        SDL_RenderDrawLine(renderer, (800/x)*i, 0, (800/x)*i, 800);
    }
    for(int i=1; i<y; i++){
        SDL_RenderDrawLine(renderer, 0, (800/y)*i, 800, (800/y)*i);
    }

    SDL_RenderPresent(renderer);
}

void drawlife(int cells[256][256]){
    for (int i=0;i<y;i++){
        for (int j=0;j<x;j++)
        {
            if(cells[i][j] == 1){
                SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
                SDL_Rect redrect = {(800/x)*j, (800/y)*i, (800/x), (800/y)};
                SDL_RenderFillRect(renderer, &redrect);
                SDL_RenderPresent(renderer);
            }
        }
    }
}

void update(int cells[256][256], int newcells[256][256]){
    for (int i=0;i<y;i++){
        for (int j=0;j<x;j++)
        {
            int num = 0;
            if(i>0 && i<y-1 && j>0 && j<x-1){
                num = cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]+cells[i][j-1]+cells[i][j+1]+cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
            }

            else if(i == y-1){
                if(j == 0){
                    num = cells[i-1][j]+cells[i-1][j+1]+cells[i][j+1];
                }
                else if(j == x-1){
                    num = cells[i-1][j-1]+cells[i-1][j]+cells[i][j-1];
                }
                else{
                    num = cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]+cells[i][j-1]+cells[i][j+1];
                }
            }

            else if(i == 0){
                if(j == 0){
                    num = cells[i][j+1]+cells[i+1][j]+cells[i+1][j+1];
                }
                else if(j == x-1){
                    num = cells[i][j-1]+cells[i+1][j-1]+cells[i+1][j];
                }
                else{
                    num = cells[i][j-1]+cells[i][j+1]+cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
                }
            }

            else if(j == 0){
                num = cells[i-1][j]+cells[i-1][j+1]+cells[i][j+1]+cells[i+1][j]+cells[i+1][j+1];
            }

            else if(j == x-1){
                num = cells[i-1][j-1]+cells[i-1][j]+cells[i][j-1]+cells[i+1][j-1]+cells[i+1][j];
            }

            if(cells[i][j] == 1){
                if(num == 2 || num == 3){
                    newcells[i][j] = 1;
                }
                else{
                    newcells[i][j] = 0;
                }
            }
            else if(cells[i][j] == 0){
                if(num == 3){
                    newcells[i][j] = 1;
                }
                else{
                    newcells[i][j] = 0;
                }
            }
        }
    }
}

bool gameover(int cells[256][256], int newcells[256][256]){
    int num = 0;
    for (int i=0;i<y;i++){
        for (int j=0;j<x;j++)
        {
            if(cells[i][j] == newcells[i][j]){
                num++;
            }
            cells[i][j] = newcells[i][j];
            newcells[i][j] = 0;
        }
    }
    if(num == x*y){
        return true;
    }
    return false;
}

void store(FILE *file, int initcells[256][256], int cells[256][256]){
    fprintf(file, "%d\n", x); 
    fprintf(file, "%d\n", y); 
    fprintf(file, "\n"); 
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            fprintf(file, "%d ", initcells[i][j]); 
        }
        fprintf(file, "\n"); 
    }
    fprintf(file, "\n"); 
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            fprintf(file, "%d ", cells[i][j]); 
        }
        fprintf(file, "\n"); 
    }
}

void destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
