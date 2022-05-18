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