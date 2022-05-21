all : gameoflife test
.PHONY : clean

gameoflife: gameoflife.o main.o
	cc -lSDL2 -lSDL2_image -o gameoflife gameoflife.o main.o
 
test : gameoflife.o test.o
	cc -lSDL2 -lSDL2_image -lcunit -o test gameoflife.o test.o
 
gameoflife.o : gameoflife.h function.h

main.o : function.h
 
test.o : function.h
 
clean : 
	rm    gameoflife 
	rm    test
	rm    *.o
