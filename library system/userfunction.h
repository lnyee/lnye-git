typedef struct _User {
	char *username;
	char *password;
	int numborrowed;
	Book *Borrowed[4];
	struct _User *next;
}User;

int load_users(FILE *file);

int store_users(FILE *file);

int registeruser();

User *login();

void listAvailableBooks();

void borrowBook(User *theUser, int numBooks);

void listMyBooks(User *theUser);

void returnBook(User *theUser, int numBooks);

void releaseUser();
