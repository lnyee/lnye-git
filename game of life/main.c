#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include"function.h"

int main(int argc, char *argv[]){
    int way;

    if(argc == 1){
        printf("Please enter the initial file! \n");
    }

    printf("\n1. Use the initial file. \n");
    printf("2. Click initialize. \n\n");
    printf("Please select the initialization method: ");
    scanf("%d", &way);

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

    if(init(way) == -1){
        return -1;
    }
    drawscreen(way);
    drawplay(way);
    // SDL_Delay(500);

    int *p[y], *c[y], *n[y], *nn[y];
    int initcells[y][x];
    int cells[y][x];
    int newcells[y][x];
    int newnewcells[y][x];
    for(int i=0; i<y; i++){
        p[i] = initcells[i];
        c[i] = cells[i];
        n[i] = newcells[i];
        nn[i] = newnewcells[i];
    }

    if(way == 1){
        if(fileinit(file, p, c) == -1){
            return -1;
        }
        fclose(file);

        drawlife(c);
        SDL_Delay(500);
    }
    if(way == 2){
        if(clickinit(p, c) == -1)
            return -1;
        SDL_Delay(500);
    }

    if(argc == 2){
        printf("\n");
        int t = 0;
        while(1){
            int flag = 0;
            while(1){
                SDL_Event event;
                if(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                        flag = 1;
                        break;
                    }
                }
                else
                    break;
            }
            if(flag){
                break;
            }
            update(c, n);
            int over = gameover(c, n, nn);
            if(over == 0 || over == 2){
                drawscreen(way);
                drawlife(c);
                t++;
                SDL_Delay(500);
                if(over == 2){
                    printf("Oscillation stability is formed after iterating %d times\n", t);
                    t = -1;
                    break;
                }
            }
            else{
                break;
            }
        }
        if(t != -1)
            printf("Iterated %d times\n", t);
    }
    else if(argc == 3){
        printf("\n");
        int flag = 0, t = 0, times = atoi(argv[2]);
        for(int i=0; i<times; i++){
            while(1){
                SDL_Event event;
                if(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                        flag = 1;
                        break;
                    }
                }
                else
                    break;
            }
            if(flag){
                break;
            }
            update(c, n);
            int over = gameover(c, n, nn);
            if(over == 0 || over == 2){
                drawscreen(way);
                drawlife(c);
                t++;
                SDL_Delay(500);
                if(over == 2){
                    printf("Oscillation stability is formed after iterating %d times\n", t);
                    t = -1;
                    break;
                }
            }
            else{
                break;
            }
        }
        if(t != -1){
            if(t == times && flag == 0){
                printf("Iterated %d times\n", times);
            }
            else if(t != times && flag == 1){
                printf("You closed the window, iterated %d times\n", t);
            }
            else{
                printf("It was stable after iterating %d times.\n", t);
            }
        }
    }

    FILE *wfile = fopen(File, "w");
    store(wfile, p, c);
    fclose(wfile);

    destroy();

    return 0;
}