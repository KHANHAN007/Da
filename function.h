#include "dataType.h"

void displayMainMenu();

// Function prototypes for book management
void displayBookMenu();
void displayBooks(book book[], int bookCount);
void addBook(book book[], int *bookCount);
void editBook(book book[],int bookCount);
void deleteBook(book book[], int *bookCount);
void searchBookByName();
void sortBooksByPrice();
void saveBooksToFile();


void displayCustomerMenu();


