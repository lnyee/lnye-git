#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "book_management.h"

int store_books(FILE *file)
{
}
int load_books(FILE *file)
{
	BookList *booklist;
	booklist = (BookList*)malloc(sizeof(BookList));  //Apply space for BookList
	booklist->length = 0;
	Book *book, *head, *end;
	head = (Book*)malloc(sizeof(Book));
	end = head;  //Create linked list
	book = (Book*)malloc(sizeof(Book));  //Apply space for Book
	while(fscanf(file, "%d", &book->id) != EOF)  //read file
	{
		fscanf(file, "\n");
		book->authors = (char*)malloc(10*sizeof(book->authors));
	  fscanf(file,"%[^\r\n]%*[\r\n]",book->authors);
		book->title = (char*)malloc(10*sizeof(book->title));
	  fscanf(file,"%[^\r\n]%*[\r\n]",book->title);
    fscanf(file, "%d", &book->year);
  	fscanf(file, "\n");
    fscanf(file, "%d", &book->copies);
  	fscanf(file, "\n");
		printf(" %d\n %s\n %s\n %d\n %d\n", book->id, book->title, book->authors, book->year, book->copies);
		booklist->length++;
		end->next = book;
		end = book;
		book = (Book*)malloc(sizeof(Book));
	}
	end->next = NULL;
	free(book);
	return booklist->length;
}