#include<stdlib.h>
#include <string.h>

#include "book_management.h"
#include "homepage.h"
#include "CLI.h"
BookList *booklist;
Book *node, *head, *end;
Bookin *h, *e;
User *uhead, *unode, *uend;

void libraryCLI(FILE *f, FILE *fi, FILE *fp) {
    int libraryOpen = 1;
    int option;
    User *log;
    log = (User*)malloc(sizeof(User));

    initlist();

    load_books(f);
    loadbookin(fp);
    load_users(fi);

    while(libraryOpen){
        printf("\nPlease choose an option:\n1 Register an account\n2 Login\n3 Search for books\n4 Display all books\n5 Quit\nChoice: ");
        option = optionChoice();

        if(option == 1) {
            registeruser();
        }
        else if( option == 2 ) {
            printf("\n");
            log = login();
            if(log != uhead){
                UsersCLI(log);
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
            printf("\nClosing\n");
        }
        else
            printf("\nUnknown option\n");
    }
    return;
}
