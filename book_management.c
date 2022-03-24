#include<stdlib.h>
#include<string.h>

#include "book_management.h"
BookList *booklist;
Book *book, *head, *end;

int store_books(FILE *file)
{
	Book *temp;
	temp = (Book*)malloc(sizeof(Book));
	temp = booklist->list;
	while(temp->next != NULL){
		temp = temp->next;
		fprintf(file, "%d\n", temp->id);
		fprintf(file, "%s\n",temp->title);
		fprintf(file, "%s\n",temp->authors);
		fprintf(file, "%d\n", temp->year);
		fprintf(file, "%d\n", temp->copies);
		fprintf(file, "\n");
	}
	return 0;
}

int load_books(FILE *file)
{
	book = (Book*)malloc(sizeof(Book));  //Apply space for Book
	booklist->length = 0;
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
	return 0;
}

int main(){
	booklist = (BookList*)malloc(sizeof(BookList));  //Apply space for BookList
	head = (Book*)malloc(sizeof(Book));
	end = head;  //Create linked list
	booklist->list = head;
  if ((fopen("books.txt", "r")) == NULL)
  {
    printf("Error\nBook file does not exist\n");
    exit(1);
  }
	FILE *fpr = fopen("books.txt", "r");
	load_books(fpr);
	fclose(fpr);
	FILE *fpw = fopen("book.txt", "w");
	store_books(fpw);
	fclose(fpw);
	return 0;
}