#include "dataType.h"

void displayMainMenu();

// Function prototypes for book management
void displayBookMenu();
void bookManagementMenu(book b,book book[], int *bookCount, const char *fileName);
void addBook(book books[], int *bookCount,const char *fileName);
void editBook(book books[], int bookCount, const char *fileName);
void deleteBook(book books[], int *bookCount, const char *filename);
void searchBookByName(book book[], int bookCount);
void sortBookByPrice(book bookTmp,book book[], int bookCount);
void saveBooksToFile();
void readBooksFromFile(book books[], int *bookCount, const char *fileName);

void displayCustomerMenu();
int isValidBookId(char *id, book books[], int bookCount);
