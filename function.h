#include "dataType.h"

void displayMainMenu();

// Function prototypes for book management
void displayBookMenu();
void bookManagementMenu(book b,book book[], int *bookCount, const char *fileName);
void addBook(book books[], int *bookCount,const char *fileName);
void editBook(book books[], int bookCount, const char *fileName);
void deleteBook(book books[], int *bookCount, const char *filename);
void searchBookByName(book book[], int bookCount);
void sortBookByPrice(book books[], int bookCount);
void saveBooksToFile();
void readBooksFromFile(book books[], int *bookCount, const char *fileName);



void displayCustomerMenu(customer customers[], int *customerCount,
                         book books[], int *bookCount,
                         const char *customerFileName, const char *bookFileName);
void displayCustomers(customer customers[], int customerCount);
void addCustomer(customer customers[], int *customerCount);
void readCustomersFromFile(customer customers[], int *customerCount, const char *fileName);
void writeCustomersToFile(customer customers[], int customerCount, const char *fileName);
void editCustomer(customer customers[], int customerCount);
void borrowBook(customer customers[], int customerCount, book books[], int bookCount);
void borrowBook(customer customers[], int customerCount, book books[], int bookCount);


int login(const Admin *admin);
void getMaskedPassword(char *password, int maxLength);
void writeAdminToFile(const Admin *admin, const char *fileName);
void readAdminFromFile(Admin *admin, const char *fileName);
void updateAdminCredentials(const char *fileName);
