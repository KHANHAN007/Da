#include "dataType.h"
#include <stdlib.h>

void displayMainMenu();

// Function prototypes for book management
void displayBookMenu();
void bookManagementMenu(book b,book book[], int *bookCount, const char *fileName);
void addBook(book books[], int *bookCount,const char *fileName);
void editBook(book book[],int bookCount);
void deleteBook(book book[], int *bookCount);
void searchBookByName(book book[], int bookCount);
void sortBookByPrice(book bookTmp,book book[], int bookCount);
void saveBooksToFile();


void displayCustomerMenu();


