#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "homepage.h"
#include "CLI.h"

int main(int argc, char **argv){
	char bookFile[40];
	char userFile[40];
	char bookinFile[40];
	if (argc != 4)
	{
		printf("Error\nExpected use: ./library books.txt user.txt bookin.txt\n");
		exit(1);
	}
	strcpy(bookFile, argv[1]);
	strcpy(userFile, argv[2]);
	strcpy(bookinFile, argv[3]);
	FILE *book = fopen(bookFile, "r");
	FILE *user = fopen(userFile, "r");
	FILE *bookin = fopen(bookinFile, "r");
	printf("\nIntialising library system!\n");
	libraryCLI(book, user, bookin);
	printf("\nClosing library system!\n\n");
	FILE *bookw = fopen(bookFile, "w");
	FILE *userw = fopen(userFile, "w");
	FILE *bookinw = fopen(bookinFile, "w");
	storebookin(bookinw);
	fclose(bookinw);
	store_users(userw);
	fclose(userw);
	store_books(bookw);
	fclose(bookw);
	releaseLibrary();
	return 0;
}
