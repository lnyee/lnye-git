typedef struct _User {
	char *username;
	char *password;
	Book *Borrowed[4];
	int numborrowed;
	struct _User *next;
}User;

User *load_users(FILE *file);

int store_users(FILE *file, User *head);

int registeruser(User *head);

User *login(User *head);

void listAvailableBooks(Book *book);

void borrowBook(User *theUser, User *head, Book *book, int numBooks);