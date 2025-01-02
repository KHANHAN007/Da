#include <stdbool.h>

struct Date
{
	int month, day,year;
};
typedef struct Date date;

struct Book
{
	char bookId[10];
	char title[30];
	char author[20];
	int quantity;
	int price;
	date publication;
};
typedef struct Book book;

struct member
{
	char memberId[10];
	char name[20];
	char phone[10];
	bool status;
	book borrowedBooks[];
};
typedef struct member customer;
typedef struct {
    char username[50];
    char password[50];
} Admin;
