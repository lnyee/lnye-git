[URL]https://github.com/lnyee/lnye-git
![Screenshot](https://github.com/lnyee/lnye-git/commit/97d82a82ba73be640d99b00732257ad57872b76f)
##GAME OF LIFE
* gameoflife.c
> This file contains all the functions required by the game, such as initialization, game logic implementation, game end detection, saving to file, etc.
* gameoflife.h
> This file contains the creation of pointers required for SDL.
* function.h
> This file contains all the functions in the file "gameoflife.c".
* main.c
> This file connects all functions together so that the game can run normally.
* initial_file.txt
> This file stores the length, width, initial state and final state of the world.
##How To Run
Save all files to the same folder and directly run the make command to generate an executable file named gameoflife. 
Then enter "./gameoflife file times" OR "./gameoflife file" on the command line.(file is initial file, times is the number of times you want the game to iterate)
