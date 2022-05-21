#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include"gameoflife.h"
#include"function.h"

int init(int way){
    if(way!=1 && way!=2){
        printf("Please enter the correct number.\n");
        return -1;
    }
    image = SDL_LoadBMP("play.bmp");
    if(!image){
        printf("Unable to open picture: %s\n", SDL_GetError());
        return -1;
    }
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Initialization failed: %s\n", SDL_GetError());
        return -1;
    }
    else{
        if(way == 1){
            window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
        }
        else if(way == 2){
            window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 900, SDL_WINDOW_SHOWN);
        }
        if(!window){
            printf("Window creation failed: %s\n", SDL_GetError());
            return -1;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
        }
    }
    return 0;
}

void drawscreen(int way){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); 

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(int i=1; i<x; i++){
        SDL_RenderDrawLine(renderer, (800/x)*i, 0, (800/x)*i, 800);
    }
    for(int i=1; i<y; i++){
        SDL_RenderDrawLine(renderer, 0, (800/y)*i, 800, (800/y)*i);
    }
    if(way == 2){
        SDL_RenderDrawLine(renderer, 0, 800, 800, 800);
    }

    SDL_RenderPresent(renderer);
}

int fileinit(FILE *file, int **initcells, int **cells){
    if(file == NULL || initcells == NULL || cells == NULL){
        return -1;
    }
    for (int i=0;i<y;i++){
        for (int j=0;j<x;j++){
            fscanf(file,"%d",&initcells[i][j]);
            cells[i][j] = initcells[i][j];
            getc(file);
        }
    }
    return 0;
}

int drawplay(int way){
    if(way == 1){
        return 0;
    }
    else if(way == 2){
        SDL_Rect rect = {50, 805, 700, 90};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
        return 0;
    }
    return -1;
}

int clickinit(int **initcells, int **cells){
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            cells[i][j] = 0;
            initcells[i][j] = 0;
        }
    }
    while(1){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                return -1;
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                int flag = 0;
                int a = event.button.x;
                int b = event.button.y;
                if(b>800 && b<900){
                    return 0;
                }
                for(int i=0; i<y; i++){
                    for(int j=0; j<x; j++){
                        if(b>(800/y)*i && b<(800/y)*(i+1) && a>(800/x)*j && a<(800/x)*(j+1)){
                            cells[i][j] = 1;
                            initcells[i][j] = 1;
                            SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
                            SDL_Rect redrect = {(800/x)*j, (800/y)*i, (800/x), (800/y)};
                            SDL_RenderFillRect(renderer, &redrect);
                            SDL_RenderPresent(renderer);
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 1){
                        break;
                    }
                }
                break;
            }
        }
    }
}

void drawlife(int **cells){
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

void update(int **cells, int **newcells){
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

int gameover(int **cells, int **newcells, int **newnewcells){
    int num = 0, n = 0;
    update(newcells, newnewcells);
    for (int i=0;i<y;i++){
        for (int j=0;j<x;j++)
        {
            if(cells[i][j] == newcells[i][j]){
                num++;
            }
            if(cells[i][j] == newnewcells[i][j]){
                n++;
            }
            cells[i][j] = newcells[i][j];
            newcells[i][j] = 0;
        }
    }
    if(num == x*y){
        return 1;
    }
    if(n == x*y){
        return 2;
    }
    return 0;
}

void store(FILE *file, int **initcells, int **cells){
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
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
