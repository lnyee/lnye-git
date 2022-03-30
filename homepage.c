#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "book_management.h"
#include "homepage.h"
#include "CLI.h"
Book *node, *head, *end;
User *uhead, *unode, *uend;

int load_users(FILE *file)
{
	Book *temp;
	temp = (Book*)malloc(sizeof(Book));
	temp = head;
	uhead = (User*)malloc(sizeof(User));
	uend = uhead;
	unode = (User*)malloc(sizeof(User));
	unode->username = (char*)malloc(10*sizeof(unode->username));
	while(fscanf(file, "%[^\r\n]%*[\r\n]", unode->username) != EOF)
	{
		unode->password = (char*)malloc(10*sizeof(unode->password));
		fscanf(file, "%[^\r\n]%*[\r\n]", unode->password);
		fscanf(file, "%d", &unode->numborrowed);

		for(int i=0; i<unode->numborrowed; i++){
			unode->Borrowed[i] = (Book*)malloc(sizeof(Book));
			fscanf(file, "%d", &unode->Borrowed[i]->id);
			for(int j=0; j<unode->Borrowed[i]->id; j++){
				temp = temp->next;
			}
			unode->Borrowed[i] = temp;
			temp = head;
		}

		fscanf(file, "\n");
		uend->next = unode;
		uend = unode;
		unode = (User*)malloc(sizeof(User));
		unode->username = (char*)malloc(10*sizeof(unode->username));
	}
	uend->next = NULL;
	free(unode);
	free(unode->username);
	return 0;
}

int store_users(FILE *file)
{
	rewind(file);
	User *temp;
	temp = (User*)malloc(sizeof(User));
	temp = uhead;
	while(temp->next != NULL){
		temp = temp->next;
		fprintf(file, "%s\n",temp->username);
		fprintf(file, "%s\n",temp->password);
		fprintf(file, "%d\n",temp->numborrowed);
		for(int i=0; i<temp->numborrowed; i++){
			fprintf(file, "%d\n", temp->Borrowed[i]->id);
		}
		fprintf(file, "\n");
	}
	return 0;
}

int registeruser(){
	User *temp;
	int k = 1;
	temp = (User*)malloc(sizeof(User));
	temp = uhead;
	unode = (User*)malloc(sizeof(User));
	unode->username = (char*)malloc(10*sizeof(unode->username));
	printf("\nPlease enter a user name: ");
	scanf("%[^\n]", unode->username);
	getchar();
	unode->password = (char*)malloc(10*sizeof(unode->password));
	printf("Please enter a password: ");
	scanf("%[^\n]", unode->password);
	getchar();

	while(temp->next != NULL){
		temp = temp->next;
		if(!strcmp(temp->username, unode->username)){
			printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
			k = 0;
			break;
			return 1;
		}
	}
	if(k){
		unode->numborrowed = 0;
		printf("Registered library account successfully\n");
		uend->next = unode;
		uend = unode;
		uend->next = NULL;
	}
	return 0;
}

User *login(){
	User *temp;
	temp = (User*)malloc(sizeof(User));
	temp = uhead;
	char *username, *password;
	username = (char*)malloc(20*sizeof(char));
	printf("Please enter your user name: ");
	scanf("%[^\n]", username);
	getchar();
	while(temp->next != NULL){
		temp = temp->next;
		if(!strcmp(temp->username, username)){
			password = (char*)malloc(20*sizeof(char));
			printf("Please enter your password: ");
			scanf("%[^\n]", password);
			if(!strcmp(temp->password, password)){
				if(!strcmp(username, "librarian")){
					LibrarianCLI();
					return uhead;
				}
				else{
					return temp;
				}
			}
			else{
				printf("Password error, please try again.\n");
				return uhead;
			}
		}
	}
	printf("The user name does not exist.\n");
	return uhead;
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

void borrowBook(User *theUser, int numBooks){
	Book *temp;
	temp = (Book*)malloc(sizeof(Book));
	temp = head;
	if(theUser == uhead){
		return;
	}
	if(theUser->numborrowed >= 4){
		printf("You have to return a book before you can borrow another\n");
	}
	else{
		int choice;
		printf("Which book?(number): ");
		scanf("%d",&choice);
		getchar();
		if(choice<0||choice>numBooks)
			printf("Error\nInvalid choice\n");
		else
		{
			for(int i = 0; i<choice; i++){
				temp = temp->next;
			}
			if(temp->copies == 0)
				printf("Book is not available\n");
			else
			{
				temp->copies--;
				theUser->Borrowed[theUser->numborrowed] = temp;
				theUser->numborrowed++;
			}
		}
	}
  return; 
}

void listMyBooks( User *theUser) {
	int i;
	if(theUser->numborrowed != 0){
		printf("\nID \tTitle                                        \tAuthors             \tyear\tcopies\n");
	}
	for(i=0;i<theUser->numborrowed;i++)
	{
	printf("%-3d\t%-45s\t%-20s\t%-4d\n", theUser->Borrowed[i]->id, theUser->Borrowed[i]->title,theUser->Borrowed[i]->authors, theUser->Borrowed[i]->year);
	}

	return;
}

void returnBook(User *theUser, int numBooks) {
	Book *temp;
	temp = (Book*)malloc(sizeof(Book));
	temp = head;
	if(theUser->numborrowed == 0)
	{
		printf("Error\nYou have not borrowed any books\n");
	}
	else
	{
		int choice, i = 0, k = 0;
		printf("Which book? (number): ");
		scanf("%d",&choice);
		getchar();
		for(i=0; i<theUser->numborrowed; i++){
			if(choice != theUser->Borrowed[i]->id)
			{
				k++;
				if(k == theUser->numborrowed){
					printf("Error\nInvalid choice\n");
					return;
				}
			}
			else{
				break;
			}
		}
		for(i=i;(i+1)<theUser->numborrowed;i++)
		{
			theUser->Borrowed[i] = theUser->Borrowed[i+1];
		}
		theUser->numborrowed--;
		theUser->Borrowed[theUser->numborrowed] = NULL;
		for(int i = 0; i<choice; i++){
			temp = temp->next;
		}
		temp->copies++;
	}
	return;
}
