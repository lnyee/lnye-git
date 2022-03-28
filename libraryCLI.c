#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "book_management.h"
#include "homepage.h"
#include "CLI.h"
BookList *booklist;
Book *node, *head, *end;
Bookin *h, *e, *n;

void libraryCLI() {
    int libraryOpen = 1;
    int option;
	Book *load;
	load = (Book*)malloc(sizeof(Book));
    User *user, *log;
    user = (User*)malloc(sizeof(User));
    log = (User*)malloc(sizeof(User));

	initlist();
	load = head;

	FILE *fpr = fopen("books.txt", "r");
	load_books(fpr);
	FILE *fpb = fopen("bookin.txt", "w");
	loadstorebookin(load, fpb);
	fclose(fpb);
	fclose(fpr);
    FILE *fp = fopen("user.txt", "r");
    if(fp == NULL){
        printf("!");
    }
    user = load_users(fp);
    fclose(fp);
   
    while(libraryOpen){
        printf("\nPlease choose an option:\n1 Register an account\n2 Login\n3 Search for books\n4 Display all books\n5 Quit\nChoice: ");
        option = optionChoice();

        if(option == 1) {
            registeruser(user);
        }
        else if( option == 2 ) {
            printf("\n");
            log = login(user);
            if(log != user){
                UsersCLI(log, user);
            }
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
            libraryOpen = 0;
            FILE *fpp = fopen("user.txt", "w");
            store_users(fpp, user);
            fclose(fpp);
            FILE *fpw = fopen("books.txt", "w");
            store_books(fpw);
            fclose(fpw);
            printf("\nClosing\n");
        }
        else
            printf("\nUnknown option\n");
    }
    return;
}
