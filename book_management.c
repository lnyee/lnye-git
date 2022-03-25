#include<stdlib.h>
#include<string.h>

#include "book_management.h"
BookList *booklist;
Book *node, *head, *end, *tit, *au, *ye;

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
	node = (Book*)malloc(sizeof(Book));  //Apply space for Book
	booklist->length = 0;
	while(fscanf(file, "%d", &node->id) != EOF)  //read file
	{
		fscanf(file, "\n");
		node->title = (char*)malloc(10*sizeof(node->title));
		fscanf(file,"%[^\r\n]%*[\r\n]",node->title);
		node->authors = (char*)malloc(10*sizeof(node->authors));
		fscanf(file,"%[^\r\n]%*[\r\n]",node->authors);
		fscanf(file, "%d", &node->year);
		fscanf(file, "\n");
		fscanf(file, "%d", &node->copies);
		fscanf(file, "\n");
		printf("id: %d - %s - %s - %d - %d\n", node->id, node->title, node->authors, node->year, node->copies);
		booklist->length++;
		end->next = node;
		end = node;
		node = (Book*)malloc(sizeof(Book));
	}
	end->next = NULL;
	free(node);
	return 0;
}

Book enter()
{
	Book enterbook;
	char str[100], cop[100];
	int i = 0, j = 0;
	printf("Please enter the title:");
	enterbook.title = (char*)malloc(10*sizeof(enterbook.title));
	scanf("%[^\n]", enterbook.title);

	printf("Please enter the author:");
	getchar();
	enterbook.authors = (char*)malloc(10*sizeof(enterbook.authors));
	scanf("%[^\n]", enterbook.authors);

	enterbook.year = 0;
	printf("Please enter the year:");
	scanf("%s", str);
	while(str[i]!='\0' || !(enterbook.year>0 && enterbook.year<2022)){
		if(str[i]>='0'&&str[i]<='9'){
			enterbook.year=enterbook.year*10+(str[i]-'0');
			i++;
		}
		else{
			while(str[j]!='\0'){
				str[j] = '\0';
				j++;
			}
			printf("Please enter the correct year:");
			scanf("%s", &str);
			i = 0;
			enterbook.year = 0;
		}
	}
	getchar();
	enterbook.id = booklist->length+1;
	return enterbook;
}

int add_book(Book book)
{
	char cop[100];
	int i = 0, j = 0;
	Book *b;
	node = (Book*)malloc(sizeof(Book));
	b = (Book*)malloc(sizeof(Book));
	b = booklist->list;
	int k = 1;
	node->id = book.id;
	node->title = book.title;
	node->authors = book.authors;
	node->year = book.year;
	node->copies = book.copies;
	while(b->next != NULL){
		b = b->next;
		if(b->title == node->title && b->authors == node->authors && b->year == node->year)
		{
			printf("This book already exists.");
			k = 0;
			break;
		}
	}
	if(k){
		node->copies = 0;
		printf("Please enter the copies the library has:");
		scanf("%s", cop);
		while(cop[i]!='\0'){
			if(cop[i]>='0'&&cop[i]<='9'){
				node->copies=node->copies*10+(cop[i]-'0');
				i++;
			}
			else{
				while(cop[j]!='\0'){
					cop[j] = '\0';
					j++;
				}
			printf("Please enter the correct copies:");
			scanf("%s", &cop);
			i = 0;
			node->copies = 0;
			}
		}
		getchar();
		booklist->length++;
		end->next = node;
		end = node;
		end->next = NULL;
	}
	return 0;
}

int remove_book(Book book){
	Book *r, *w, *q;
	node = (Book*)malloc(sizeof(Book));
	r = (Book*)malloc(sizeof(Book));
	w = (Book*)malloc(sizeof(Book));
	w = booklist->list;
	q = booklist->list;
	r = w->next;
	int k = 1, a = 1;
	node->id = book.id;
	node->title = book.title;
	node->authors = book.authors;
	node->year = book.year;
	node->copies = book.copies;
	while(r != NULL){
		if(!strcmp(r->title, node->title) && !strcmp(r->authors, node->authors) && r->year == node->year)
		{
			w->next = r->next;
			booklist->length--;
			k = 0;
			break;
		}
		w = r;
		r = r->next;
	}
	if(k){
		printf("This book doesn't exists.");
	}
	while(q->next != NULL){
		q = q->next;
		q->id = a;
		a++;
	}
	return 0;
}

BookList find_book_by_title (const char *title){
	BookList t;
	Book *tit;
	int k = 1;
	tit = t.list;
	tit = (Book*)malloc(sizeof(Book));
	tit = head;
	while(tit->next != NULL){
		tit = tit->next;
		if(!strcmp(tit->title, title)){
			t.length++;
			k = 0;
			printf("%d %s %s %d %d\n", tit->id, tit->title, tit->authors, tit->year, tit->copies);
		}
	}
	if(k){
		printf("This book doesn't exists.\n");
	}
	return t;
}

BookList find_book_by_author (const char *author){
	BookList a;
	Book *au;
	int k = 1;
	au = a.list;
	au = (Book*)malloc(sizeof(Book));
	au = head;
	while(au->next != NULL){
		au = au->next;
		if(!strcmp(au->authors, author)){
			k = 0;
			a.length++;
			printf("%d %s %s %d %d\n", au->id, au->title, au->authors, au->year, au->copies);
		}
	}
	if(k){
		printf("This author doesn't exists.\n");
	}
	return a;
}

BookList find_book_by_year (unsigned int year){
	BookList y;
	Book *ye;
	int k = 1;
	ye = y.list;
	ye = (Book*)malloc(sizeof(Book));
	ye = head;
	while(ye->next != NULL){
		ye = ye->next;
		if(ye->year == year){
			k = 0;
			y.length++;
			printf("%d %s %s %d %d\n", ye->id, ye->title, ye->authors, ye->year, ye->copies);
		}
	}
	if(k){
		printf("There are no books published this year.\n");
	}
	return y;
}
int main(){
	char *title, *author;
	char yy[20];
	int year = 0, i = 0, j = 0;
	title = (char*)malloc(10*sizeof(title));
	author = (char*)malloc(10*sizeof(author));
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

	add_book(enter());
	remove_book(enter());

	printf("Please enter the title you want to find:");
	scanf("%s", title);
	find_book_by_title (title);
	printf("Please enter the author you want to find:");
	scanf("%s", author);
	find_book_by_author (author);
	printf("Please enter the year of the book you want to find:");
	scanf("%s", yy);
	while(yy[i]!='\0' || !(year>0 && year<2022)){
		if(yy[i]>='0'&&yy[i]<='9'){
			year=year*10+(yy[i]-'0');
			i++;
		}
		else{
			while(yy[j]!='\0'){
				yy[j] = '\0';
				j++;
			}
			printf("Please enter the correct year:");
			scanf("%s", &yy);
			i = 0;
			j = 0;
			year = 0;
		}
	}
	find_book_by_year(year);

	FILE *fpw = fopen("book.txt", "w");
	store_books(fpw);
	fclose(fpw);
	return 0;
}