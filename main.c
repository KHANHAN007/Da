#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
    Admin admin;
    const char *adminFileName = "admin.dat";
    readAdminFromFile(&admin, adminFileName);
    if (!login(&admin)) {
        printf("Exiting program.\n");
        return 0;
    }
    printf("Welcome to the program!\n");

    const char *fileName1 = "dataLibrary.dat";
    const char *fileName2 = "customers.dat";

    book books[100];
    int bookCount = 0;
    customer customers[100];
    int customerCount = 0;

    readBooksFromFile(books, &bookCount, fileName1);
    readCustomersFromFile(customers, &customerCount, fileName2);
    int choice;
    do {
        displayMainMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                system("cls");
                bookManagementMenu(books[0], books, &bookCount, fileName1);
                break;
            case 2:
                system("cls");
                displayCustomerMenu(customers, &customerCount,
                         books, &bookCount,
                         fileName2, fileName1);
                break;
            case 0:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid input. Please enter a number.\n");
                getchar();
                break;
        }
    } while (choice != 0);
    writeBooksToFile(books, bookCount, fileName1);
    return 0;
}
