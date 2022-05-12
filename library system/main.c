#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "userfunction.h"
#include "CLI.h"

int main(int argc, char **argv){
	char bookFile[40];
	char userFile[40];
	char bookinFile[40];
	if (argc != 4)
	{
		printf("Error\nExpected use: ./library_system books.txt user.txt bookin.txt\n");
		exit(1);
	}
	strcpy(bookFile, argv[1]);
	strcpy(userFile, argv[2]);
	strcpy(bookinFile, argv[3]);
	FILE *book = fopen(bookFile, "r");
	if(book == NULL){
		printf("The file %s does not exist\n", bookFile);
		return 1;
	}
	FILE *user = fopen(userFile, "r");
	if(user == NULL){
		printf("The file %s does not exist\n", userFile);
		return 1;
	}
	FILE *bookin = fopen(bookinFile, "r");
	if(bookin == NULL){
		printf("The file %s does not exist\n", bookinFile);
		return 1;
	}
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
	releaseUser();
	releaseLibrary();
	return 0;
}
