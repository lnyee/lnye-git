#include<stdlib.h>
#include <string.h>

#include "book_management.h"
#include "homepage.h"
#include "CLI.h"
BookList *booklist;
Book *node, *head, *end;
Bookin *h, *e;
User *uhead, *unode, *uend;

int optionChoice() {
	int option = -1;
	char line[80];
	fgets(line,80,stdin);
	option = (int)atoi(line);
	return option;
}

void findbooksCLI(){
	char *title, *author;
	char yy[20];
	int year = 0, i = 0;
	title = (char*)malloc(10*sizeof(title));
	author = (char*)malloc(10*sizeof(author));
	int option;
	printf("\nPlease choose an option:\n1 Find books by title\n2 Find books by author\n3 Find books by year\nChoice: ");
	option = optionChoice();
	    
	if(option == 1){
		printf("\nPlease enter the title you want to find: ");
		scanf("%[^\n]", title);
		getchar();
		showfind(find_book_by_title (title));
	}

	else if(option == 2){
		printf("\nPlease enter the author you want to find: ");
		scanf("%[^\n]", author);
		getchar();
		showfind(find_book_by_author (author));
	}

	else if(option == 3){
		printf("\nPlease enter the year of the book you want to find: ");
		scanf("%[^\n]", yy);
		getchar();
		while(yy[i]!='\0'){
			if(yy[i]>='0'&&yy[i]<='9'){
				year=year*10+(yy[i]-'0');
				i++;
			}
			else{
				year = 0;
				break;
			}
		}
		showfind(find_book_by_year (year));
	}

	else{
		printf("\nUnknown option\n");
	}
}

void LibrarianCLI(){
	int librarianlogin = 1, option;
	option = optionChoice();

	while(librarianlogin){
		printf("\n(logged in as: librarian)");
		printf("\nPlease choose an option:\n1 Add a book\n2 Remove a book\n3 Search for books\n4 Display all books\n5 Log out\nChoice: ");
		option = optionChoice();

		if(option == 1){
			add_book(enter());
		}

		else if(option == 2){
			remove_book(enter());
		}

		else if(option == 3) {
			findbooksCLI();
		}
		else if(option == 4) {
			printf("\nID \tTitle                                        \tAuthors             \tyear\tcopies\n");
			showbooks();
			printf("\n");
		}
		else if(option == 5) {
			librarianlogin = 0;
			printf("\nLogging out\n");
		}
		else
			printf("\nUnknown option\n");
	}
	return;
}

void UsersCLI(User *user){
	int userlogin = 1, option;
	option = optionChoice();

	while(userlogin){
		printf("\n(logged in as: %s)", user->username);
		printf("\nPlease choose an option:\n1 Borrow a book\n2 Return a book\n3 Search for books\n4 Display all books\n5 Log out\nChoice: ");
		option = optionChoice();

		if(option == 1){
			borrowBook(user, booklist->length);
		}

		else if(option == 2){
			listMyBooks(user);
			returnBook(user, booklist->length);
		}

		else if(option == 3) {
			findbooksCLI();
		}
		else if(option == 4) {
			printf("\nID \tTitle                                        \tAuthors             \tyear\tcopies\n");
			showbooks();
			printf("\n");
		}
		else if(option == 5) {
			userlogin = 0;
			printf("\nLogging out\n");
		}
		else
			printf("\nUnknown option\n");
	}
	return;
}
