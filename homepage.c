#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "1.h"
#include "homepage.h"
// typedef struct _User {
// 		char *username;
// 		char *password;
// 		struct _User *next;
// }User;

User *load_users(FILE *file)
{
	User *head, *node, *end;
	head = (User*)malloc(sizeof(User));
	end = head;
	node = (User*)malloc(sizeof(User));
	node->username = (char*)malloc(10*sizeof(node->username));
	while(fscanf(file, "%[^\r\n]%*[\r\n]", node->username) != EOF)
	{
		node->password = (char*)malloc(10*sizeof(node->password));
		fscanf(file, "%[^\r\n]%*[\r\n]", node->password);
		end->next = node;
		end = node;
		node = (User*)malloc(sizeof(User));
		node->username = (char*)malloc(10*sizeof(node->username));
	}
	end->next = NULL;
	free(node);
	free(node->username);
	return head;
}

int store_users(FILE *file, User *head)
{
	User *temp;
	temp = (User*)malloc(sizeof(User));
	temp = head;
	while(temp->next != NULL){
		temp = temp->next;
		fprintf(file, "%s\n",temp->username);
		fprintf(file, "%s\n",temp->password);
		fprintf(file, "\n");
	}
	return 0;
}

int registeruser(User *head){
	User *temp, *node;
	int k = 1;
	temp = (User*)malloc(sizeof(User));
	temp = head;
	node = (User*)malloc(sizeof(User));
	node->username = (char*)malloc(10*sizeof(node->username));
	printf("Please enter a user name:");
	scanf("%s", node->username);
	node->password = (char*)malloc(10*sizeof(node->password));
	printf("Please enter a password:");
	scanf("%s", node->password);

	while(temp->next != NULL){
		temp = temp->next;
		if(!strcmp(temp->username, node->username)){
			printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
			k = 0;
			break;
			return 1;
		}
	}
	if(k){
		printf("Registered library account successfully\n");
		temp->next = node;
		temp = node;
		temp->next = NULL;
	}
	return 0;
}

User *login(User *head){
	User *temp;
	temp = (User*)malloc(sizeof(User));
	temp = head;
	char *username, *password;
	username = (char*)malloc(20*sizeof(char));
	printf("Please enter your user name:");
	scanf("%s", username);
	while(temp->next != NULL){
		temp = temp->next;
		if(!strcmp(temp->username, username)){
			password = (char*)malloc(20*sizeof(char));
			printf("Please enter your password:");
			scanf("%s", password);
			if(!strcmp(temp->password, password)){
				printf("\n(logged in as: %s)\n", username);
				// if(!strcmp(username, 'library')){
				// 	LibraryCLI();
				// }
				return temp;
			}
			else{
				printf("Password error, please try again.\n");
				return head;
			}
		}
	}
	printf("The user name does not exist.\n");
	return head;
}

void listAvailableBooks(Book *book){
	printf("\nID \tTitle                                        \tAuthors             \tyear\tcopies\n");
	while(book->next != NULL){
		book = book->next;
		if(book->copies != 0){
			printf("%-3d\t%-45s\t%-20s\t%-4d\t%-6d\n", book->id, book->title, book->authors, book->year, book->copies);
  		}
	}
}

void borrowBook(User *theUser, User *head, Book *book, int numBooks){
	theUser->numborrowed = 0;
	if(theUser == head){
		return;
	}
	if(theUser->numborrowed == 4){
		printf("You have to return a book before you can borrow another\n");
	}
	else{
		int choice;
		printf("Which book?(number)");
		scanf("%d",&choice);
		getchar();
		if(choice<0||choice>numBooks)
			printf("Error\nInvalid choice\n");
		else
		{
			for(int i = 0; i<choice; i++){
				book = book->next;
			}
			if(book->copies == 0)
				printf("Book is not available\n");
			else
			{
				book->copies--; 
				theUser->Borrowed[theUser->numborrowed] = book;
				theUser->numborrowed++; 
			}
	      }
	}
  return; 
}

void listMyBooks( User *theUser, Book *bookList) {
	int i;
	if(theUser->numborrowed > 0){
		printf("\nID \tTitle                                        \tAuthors             \tyear\tcopies\n");
	}
	for(i=0;i<theUser->numborrowed;i++)
	{
	printf("%-3d\t%-45s\t%-20s\t%-4d\n", theUser->borrowed[i]->id, theUser->borrowed[i]->title,theUser->borrowed[i]->authors, theUser->borrowed[i]->year);
	}

  return;
}

void returnBook(User *theUser, Book *book, int numBooks) {
	if(theUser->numborrowed == 0)
	{
		printf("Error\nYou have not borrowed any books\n");
	}
	else
	{
		int choice, i = 0, k = 0;
		printf("Which book? (number):");
		scanf("%d",&choice);
		getchar();
		for(i=0; i<theUser->numborrowed; i++){
			if(choice != theUser->Borrowed[i]->id)
			{
				k++;
				if(k = theUser->numborrowed){
					printf("Error\nInvalid choice\n");
					return;
				}
			}
			else{
				break;
			}
		}
		theUser -> Borrowed[i] -> copies++;
		for(i;(i+1)<theUser->numBorrowed;i++)
		{
			theUser->Borrowed[i] = theUser->Borrowed[i+1];
		}
		theUser->numBorrowed--;
		theUser->borrowed[theUser->numBorrowed] = NULL;
	}
	return;
}

// int main(){
// 	User *user;
// 	user = (User*)malloc(sizeof(User));
//   	FILE *fp = fopen("user.txt", "r");
//   	if(fp == NULL){
//   		printf("!");
//   	}
// 	user = load_users(fp);
// 	fclose(fp);
// 	registeruser(user);
//   	FILE *fpw = fopen("user.txt", "w");
// 	store_users(fpw, user);
// 	listAvailableBooks(head);
// 	borrowBook(login(user), head, booklist->length);
// }
