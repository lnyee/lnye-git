#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// #include "homepage.h"
typedef struct _User {
		char *username;
		char *password;
		struct _User *next;
}User;

User *inituserlist(){
	User *head, *end;
	head = (User*)malloc(sizeof(User));
	end = head;
	return head;
}

int registeruser(User *head){
	User *temp, *user;
	int k = 1;
	temp = (User*)malloc(sizeof(User));
	temp = head;
	user = (User*)malloc(sizeof(User));
	user->username = (char*)malloc(10*sizeof(user->username));
	printf("Please enter a user name:");
	scanf("%s", user->username);
	user->password = (char*)malloc(10*sizeof(user->password));
	printf("Please enter a password:");
	scanf("%s", user->password);
	while(temp->next != NULL){
		temp = temp->next;
		if(!strcmp(temp->username, user->username)){
			printf("Sorry, registration unsuccessful, the username you entered already exists. ");
			k = 0;
			break;
			return 1;
		}
	}
	if(k){
		printf("Registered library account successfully\n");
		temp->next = user;
		temp = user;
		temp->next = NULL;
	}
	return 0;
}

User *login(User *head){
	User *temp;
	int k = 1;
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
				return temp;
			}
			else{
				printf("Password error, please try again.\n");
				return head;
			}
		}
	}
	printf("The user name does not exist.");
	return head;
}

int main(){
	User *user;
	user = (User*)malloc(sizeof(User));
	user = inituserlist();
	registeruser(user);
	login(user);
}
