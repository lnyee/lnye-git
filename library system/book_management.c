#include<stdlib.h>
#include<string.h>

#include "book_management.h"
BookList *booklist;
Book *node, *head, *end;
Bookin *h, *e, *n;

int initlist(){  //Initialize linked list
	booklist = (BookList*)malloc(sizeof(BookList));
	head = (Book*)malloc(sizeof(Book));
	end = head;
	booklist->list = head;
	return 0;
}

int store_books(FILE *file)  //Save the book in a text file
{
	int len;
	rewind(file);
	Book *temp;
	temp = (Book*)malloc(sizeof(Book));
	temp = booklist->list;
	while(temp->next != NULL){  //Traversal linked list
		temp = temp->next;                      //Format:
		fprintf(file, "%d\n", temp->id);        //Book ID
		len = strlen(temp->title);
		fprintf(file, "%d\n", len);             //The length of book title
		fprintf(file, "%s\n",temp->title);      //Book title
		len = strlen(temp->authors);
		fprintf(file, "%d\n", len);             //The length of book author
		fprintf(file, "%s\n",temp->authors);    //Book author
		fprintf(file, "%d\n", temp->year);      //Book year
		fprintf(file, "%d\n", temp->copies);    //Book copies
		fprintf(file, "\n");                    //Empty line
	}
	free(temp);
	return 0;
}

int load_books(FILE *file)
{
	Book *temp;
	char *load;
	load = (char*)malloc(100*sizeof(char));
	int len = 0;
	temp = (Book*)malloc(sizeof(Book));  //Apply space for Book
	node = (Book*)malloc(sizeof(Book));  //Apply space for Book
	booklist->length = 0;

	while(fscanf(file, "%[^\n]", load) != EOF)    //load book ID
	{
		len = digit(load);                          //Check if it is a number
		if(len == -1){
			printf("The book file is corrupt.\n");
			exit(1);								//If it is not a number, return -1 and exit the program.
		}
		node->id = len;
		fscanf(file, "\n");

		// load book title
		// 1. read the length of title
		fscanf(file, "%[^\n]", load);
		len = digit(load);
		if(len == -1){
			printf("The book file is corrupt.\n");
			exit(1);
		}
		fscanf(file, "\n");
		// 2. Apply space and load title
		node->title = (char*)malloc(len+1);
		fscanf(file, "%[^\n]", node->title);
		if(strlen(node->title) != len){
			printf("The book file is corrupt.\n");
			exit(1);
		}
		len = 0;
		fscanf(file, "\n");

		// load book author
		// 1. read the length of author
		fscanf(file, "%[^\n]", load);
		len = digit(load);
		if(len == -1){
			printf("The book file is corrupt.\n");
			exit(1);
		}
		fscanf(file, "\n");
		// 2. Apply space and load author
		node->authors = (char*)malloc(len+1);
		fscanf(file, "%[^\n]", node->authors);
		if(strlen(node->authors) != len){
			printf("The book file is corrupt.\n");
			exit(1);
		}
		fscanf(file, "\n");

		// load book year
		fscanf(file, "%[^\n]", load);
		len = digit(load);
		if(len == -1){
			printf("The book file is corrupt.\n");
			exit(1);
		}
		node->year = len;
		fscanf(file, "\n");

		// load book copies
		fscanf(file, "%[^\n]", load);
		len = digit(load);
		if(len == -1){
			printf("The book file is corrupt.\n");
			exit(1);
		}
		node->copies = len;
		fscanf(file, "\n");

		fscanf(file, "\n");
		booklist->length++;
		end->next = node;
		end = node;
		node = (Book*)malloc(sizeof(Book));
	}
	end->next = NULL;
	free(load);
	free(node->title);
	free(node->authors);
	free(node);
	return 0;
}

int showbooks(){   //Format: ID  title  authors  year  copies
	Book *show;
	show = (Book*)malloc(sizeof(Book));
	show = head;
	while(show->next != NULL){
		show = show->next;
		if(show->copies != 0){
			printf("%-3d\t%-45s\t%-20s\t%-4d\t%-6d\n", show->id, show->title, show->authors, show->year, show->copies);
		}
	}
	return 0;
}

int loadbookin(FILE *file){
	char *load;
	load = (char*)malloc(100*sizeof(char));
	int len, line = 0;
	h = (Bookin*)malloc(sizeof(Bookin));
	e = (Bookin*)malloc(sizeof(Bookin));
	h = e;
	n = (Bookin*)malloc(sizeof(Bookin));
	while(fscanf(file, "%[^\n]", load) != EOF)
	{
		line++;
		len = digit(load);
		if(len == -1){
			printf("The bookin file is corrupt.\n");
			exit(1);
		}
		n->id = len;
		fscanf(file, "\n");
		fscanf(file, "%[^\n]", load);
		line++;
		len = digit(load);
		if(len == -1){
			printf("The bookin file is corrupt.\n");
			exit(1);
		}
		n->oriquantity = len;
		fscanf(file, "\n");
		e->next = n;
		e = n;
		n = (Bookin*)malloc(sizeof(Bookin));
	}
	if(line > booklist->length*2){
		printf("The book file is corrupt.\n");
		exit(1);
	}
	else if(line < booklist->length*2){
		printf("The bookin file is corrupt.\n");
		exit(1);
	}
	e->next = NULL;
	free(load);
	free(n);
	return 0;
}

int storebookin(FILE *file){
	rewind(file);
	Bookin *temp;
	temp = (Bookin*)malloc(sizeof(Bookin));
	temp = h;
	while(temp->next != NULL){                      //Format:
		temp = temp->next;
		fprintf(file, "%d\n", temp->id);              //Book ID
		fprintf(file, "%d\n", temp->oriquantity);     //Book original copies
	}
	free(temp);
	return 0;
}

Book enter()                                      // Read data for adding books and removing books
{
	Book enterbook;
	char *str;
	str = (char*)malloc(100*sizeof(char));
	char a[100], b[100];
	int i = 0, len;
	printf("\nPlease enter the title: ");           // Read book title
	scanf("%[^\n]", a);
	getchar();
	len = strlen(a);
	char c[len];
	for(i=0; *(a+i)!='\0'; i++){
		c[i] = *(a+i);
	}
	c[i] = '\0';
	enterbook.title = (char*)malloc(len);
  strcpy (enterbook.title, c);

	printf("Please enter the author: ");            // Read book author
	scanf("%[^\n]", b);
	getchar();
	len = strlen(b);
	char d[len];
	for(i=0; *(b+i)!='\0'; i++){
		d[i] = *(b+i);
	}
	d[i] = '\0';
	enterbook.authors = (char*)malloc(len);
  strcpy (enterbook.authors, d);

  i = 0;
	enterbook.year = 0;
	printf("Please enter the year: ");              // Read book year
	scanf("%[^\n]", str);                           // Check if it is a number
	getchar();
	len = digit(str);                               // Is a number: year = number
	if(len >= 0){									// Not: year = 0
		enterbook.year = len;
	}
	enterbook.id = booklist->length+1;
	return enterbook;
}

int add_book(Book book)
{
	char cop[100];
	int i = 0;
	Book *b;
	node = (Book*)malloc(sizeof(Book));
	b = (Book*)malloc(sizeof(Book));
	b = booklist->list;
	n = (Bookin*)malloc(sizeof(Bookin));
	int k = 1;
	n->id = book.id;
	node->id = book.id;
	node->title = book.title;
	node->authors = book.authors;
	node->year = book.year;                          // Put the book's data into a linked list

	node->copies = 0;																 // Read book copies
	printf("Please enter the copies the library has: ");
	scanf("%[^\n]", cop);
	while(cop[i]!='\0'){
		if(cop[i]>='0'&&cop[i]<='9'){
			node->copies=node->copies*10+(cop[i]-'0');
			i++;
		}
		else{
			node->copies = 0;
			break;
		}
	}
	getchar();
	if(!(node->year>0) || !(node->copies>0)){       // Check if year and copies are valid
		printf("Sorry, you attempted to add an invalid book, please try again.\n");
		return 1;
	}

	while(b->next != NULL){													 // Check if the added book already exists
		b = b->next;
		if(!strcmp(b->title, node->title) && !strcmp(b->authors, node->authors) && b->year == node->year)
		{
			printf("This book already exists.\n");
			k = 0;
			return 1;
		}
	}

	if(k){
		printf("Added successfully.\n");
		n->oriquantity = node->copies;
		e->next = n;
		e = n;
		e->next = NULL;
		booklist->length++;
		end->next = node;
		end = node;
		end->next = NULL;
	}
	return 0;
}

int remove_book(Book book){
	Book *r, *w, *q;
	r = (Book*)malloc(sizeof(Book));
	w = (Book*)malloc(sizeof(Book));
	w = head;
	r = w->next;
	q = head;
	Bookin *c, *d;
	c = (Bookin*)malloc(sizeof(Bookin));
	d = (Bookin*)malloc(sizeof(Bookin));
	c = h;
	d = c->next;
	int k = 1, a = 1;
	while(r != NULL){
		if(!strcmp(r->title, book.title) && !strcmp(r->authors, book.authors) && r->year == book.year)  // Check whether the book already exists
		{
			if(d->oriquantity != r->copies){                   // Check if this book is on loan
				printf("Some of the books are being borrowed. Please try again after they are all returned.\n");
				return 1;
			}
			if(r->next == NULL){
				end = w;
				end->next = NULL;
				e = c;
				e->next = NULL;
			}
			else{
			w->next = r->next;
			c->next = d->next;
			}
			booklist->length--;
			k = 0;
			c = h;
			printf("Removed successfully.\n");
			break;
		}
		w = r;
		r = r->next;
		c = d;
		d = d->next;
	}
	if(k){
		printf("This book doesn't exists.\n");
		return 1;
	}
	while(q->next != NULL){
		q = q->next;
		q->id = a;
		c = c->next;
		c->id = a;
		a++;
	}
	return 0;
}

BookList find_book_by_title (const char *title){
	BookList t;
	Book *tit, *hd, *ed, *go;
	int k = 1;
	t.length = 0;
	hd = (Book*)malloc(sizeof(Book));
	go = (Book*)malloc(sizeof(Book));
	ed = hd;
	tit = (Book*)malloc(sizeof(Book));
	tit = head;
	while(tit->next != NULL){
		tit = tit->next;
		if(!strcmp(tit->title, title)){
			k = 0;
			go = tit;
			t.length++;
			ed->next = go;
			ed = go;
			go = (Book*)malloc(sizeof(Book));
		}
	}
	t.list = hd;
	if(k){
		printf("This book doesn't exists.\n");
	}
	return t;
}

BookList find_book_by_author (const char *author){
	BookList a;
	Book *au, *hd, *ed, *go;
	int k = 1;
	a.length = 0;
	hd = (Book*)malloc(sizeof(Book));
	go = (Book*)malloc(sizeof(Book));
	// ed = (Book*)malloc(sizeof(Book));
	ed = hd;
	au = (Book*)malloc(sizeof(Book));
	au = head;
	while(au->next != NULL){
		au = au->next;
		if(!strcmp(au->authors, author)){
			k = 0;
			go = au;
			a.length++;
			ed->next = go;
			ed = go;
			go = (Book*)malloc(sizeof(Book));
		}
	}
	a.list = hd;
	if(k){
		printf("This author doesn't exists.\n");
	}
	return a;
}

BookList find_book_by_year (unsigned int year){
	BookList y;
	Book *ye, *hd, *ed, *go;
	int k = 1;
	y.length = 0;
	hd = (Book*)malloc(sizeof(Book));
	go = (Book*)malloc(sizeof(Book));
	ed = hd;
	ye = (Book*)malloc(sizeof(Book));
	ye = head;
	while(ye->next != NULL){
		ye = ye->next;
		if(ye->year == year){
			k = 0;
			go = ye;
			y.length++;
			ed->next = go;
			ed = go;
			go = (Book*)malloc(sizeof(Book));
		}
	}
	y.list = hd;
	if(k){
		printf("There are no books published this year.\n");
	}
	return y;
}

void showfind(BookList blist){
	BookList go;
	go.list = (Book*)malloc(sizeof(Book));
	if(blist.length == 0){
		return;
	}
	go.list = blist.list;
	printf("\nID \tTitle                                        \tAuthors             \tyear\tcopies\n");
	for(int i=0; i<blist.length; i++){
		go.list = go.list->next;
		printf("%-3d\t%-45s\t%-20s\t%-4d\t%-6d\n", go.list->id, go.list->title, go.list->authors, go.list->year, go.list->copies);
	}
	return;
}

void releaseLibrary(){  //Free the memory of Book linked list and Bookin linked list
	Book *temp;
	temp = (Book*)malloc(sizeof(Book));
	head = head->next;
	Bookin *a;
	a = (Bookin*)malloc(sizeof(Bookin));
	h = h->next;
	while(head != NULL){
		temp = head;
		head = head->next;
		free(temp->title);
		free(temp->authors);
		free(temp);
	}
	while(h != NULL){
		a = h;
		h = h->next;
		free(a);
	}
}

int digit(char *str){                       // Check if the input is a number
	int digit = 0, i = 0, j = 0;
	while(*(str+i) != '\0'){
		if(*(str+i) >= '0'&&*(str+i) <= '9'){
			digit = digit*10 + (*(str+i) - '0');
			i++;
		}
		else{
			while(*(str+j) != '\0'){
				*(str+j) = '\0';
				j++;
			}
			return -1;
		}
	}
	while(*(str+j) != '\0'){
		*(str+j) = '\0';
		j++;
	}
	return digit;
}
