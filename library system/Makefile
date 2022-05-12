# code details

EXE = ./library_system
SRC= main.c libraryCLI.c userCLI.c book_management.c userfunction.c 

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= 

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o: main.c book_management.h userfunction.h CLI.h
libraryCLI.o: libraryCLI.c book_management.h userfunction.h CLI.h
user.o: user.c  book_management.h userfunction.h CLI.h
book_management.o: book_management.c book_management.h
userfunction.o: userfunction.c book_management.h userfunction.h CLI.h

