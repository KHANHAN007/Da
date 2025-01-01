#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
    const char *fileName = "dataLibrary.dat";
    book books[100];
    int bookCount = 0;
    readBooksFromFile(books, &bookCount, fileName);
    int choice;
    do {
        displayMainMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                system("cls");
                bookManagementMenu(books[0], books, &bookCount, fileName);
                break;
            default:
                getchar();
                printf("Invalid input. Please enter a number.\n");
                getchar();
            break;
        }
    } while (choice != 0);
    writeBooksToFile(books, bookCount, fileName);
    return 0;
}
