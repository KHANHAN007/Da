#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// Main menu
void displayMainMenu() {
    system("cls");
    printf("\n\t*** Library Management System ***\n");
    printf("=========================================\n");
    printf("[1] Book Management\n");
    printf("[2] Customer Management\n");
    printf("[3] Admin Authentication\n");
    printf("[0] Exit Program\n");
    printf("=========================================\n");
    printf("Enter your choice: ");
}
// Book Management
void bookManagementMenu(book bookTmp, book book[], int *bookCount, const char *fileName) {
    int choice;
    do {
        system("cls");
        readBooksFromFile(book, bookCount, fileName);
        printf("\n\t*** Book Management ***\n");
        printf("=======================\n");
        printf("[1] Display Books\n");
        printf("[2] Add Book\n");
        printf("[3] Edit Book Information\n");
        printf("[4] Delete Book\n");
        printf("[5] Search Book by Name\n");
        printf("[6] Sort Books by Price\n");
        printf("[7] Save Book Data\n");
        printf("[0] Back to Main Menu\n");
        printf("=======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                displayBooks(book, *bookCount);
                break;
            case 2:
                system("cls");
                addBook(book, bookCount, fileName);
                break;
            case 3:
                system("cls");
                editBook(book, *bookCount, fileName);
                break;
            case 4:
                system("cls");
                deleteBook(book, bookCount, fileName);
                break;
            case 5:
                system("cls");
                searchBookByName(book, *bookCount);
                break;
            case 6:
                system("cls");
                sortBookByPrice(bookTmp, book, *bookCount);
                writeBooksToFile(book, *bookCount, fileName);
                break;
            case 7:
                system("cls");
                writeBooksToFile(book, *bookCount, fileName);
                break;
        }
    } while (choice != 0);
}
// Display books
void displayBooks(book book[], int bookCount) {
    getchar();
    if (bookCount == 0) {
        getchar();
        printf("\n\t*** Display Books ***\n");
        printf("==========================================\n");
        printf("\t\tEmpty list\n");
        printf("\n--- Press any key to go back ---\n");
        getchar();
        printf("==========================================\n");
        return;
    }
    printf("\n\t*** Display Books ***\n");
    printf("=========================================================================================================\n");
    printf("| %-6s | %-25s | %-20s | %-8s | %-10s | %-10s |\n",
           "ID", "Title", "Author", "Price", "Quantity", "Publication");
    printf("=========================================================================================================\n");
    for (int i = 0; i < bookCount; ++i) {
        printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d  |\n",
               book[i].bookId, book[i].title, book[i].author,
               book[i].price, book[i].quantity,
               book[i].publication.day, book[i].publication.month, book[i].publication.year);
    }
    printf("=========================================================================================================\n");
    printf("\n--- Press any key to go back ---\n");
    getchar();
}
// Add book
void addBook(book books[], int *bookCount, const char *fileName) {
    getchar();
    int numBooksToAdd;
    printf("\n\t*** Add Books ***\n");
    printf("=========================\n");
    printf("Enter the number of books to add: ");
    scanf("%d", &numBooksToAdd);
    getchar();

    for (int i = 0; i < numBooksToAdd; i++) {
        char tempId[10];
        int isDuplicate;

        printf("\nAdding book number %d\n", *bookCount + 1);
        do {
            isDuplicate = 0;
            printf("Enter book Id: ");
            scanf("%s", tempId);
            getchar();
            for (int j = 0; j < *bookCount; j++) {
                if (strcmp(books[j].bookId, tempId) == 0) {
                    printf("Error: Book ID '%s' already exists. Please enter a different ID.\n", tempId);
                    isDuplicate = 1;
                    break;
                }
            }
        } while (isDuplicate);
        strcpy(books[*bookCount].bookId, tempId);
        printf("Enter title: ");
        scanf(" %[^\n]", books[*bookCount].title);
        getchar();
        printf("Enter author: ");
        scanf(" %[^\n]", books[*bookCount].author);
        getchar();
        printf("Enter quantity: ");
        scanf("%d", &books[*bookCount].quantity);
        getchar();
        printf("Enter price: ");
        scanf("%d", &books[*bookCount].price);
        getchar();
        printf("Enter publication date (dd mm yyyy): ");
        scanf("%d %d %d",
              &books[*bookCount].publication.day,
              &books[*bookCount].publication.month,
              &books[*bookCount].publication.year);
        getchar();
        (*bookCount)++;
        printf("Book added successfully!\n");
    }
    writeBooksToFile(books, *bookCount, fileName);
    getchar();
}
// Edit book
void editBook(book books[], int bookCount, const char *fileName) {
    if (bookCount == 0) {
        getchar();
        printf("\n\t*** Edit Book ***\n");
        printf("\t   Empty list\n");
        printf("--- Press any key to go back ---\n");
        getchar();
        return;
    }
    printf("\n\t*** Current Book List ***\n");
    printf("=========================================================================================================\n");
    printf("| %-6s | %-25s | %-20s | %-8s | %-10s | %-10s |\n",
           "ID", "Title", "Author", "Price", "Quantity", "Publication");
    printf("=========================================================================================================\n");
    for (int i = 0; i < bookCount; ++i) {
        printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d  |\n",
               books[i].bookId, books[i].title, books[i].author,
               books[i].price, books[i].quantity,
               books[i].publication.day, books[i].publication.month, books[i].publication.year);
    }
    printf("=========================================================================================================\n");
    char editID[10];
    int found = -1;
    printf("\n\t*** Edit Book ***\n");
    printf("Enter the book ID you want to edit: ");
    scanf("%s", editID);
    editID[strcspn(editID, "\n")] = '\0';
    system("cls");
    for (int i = 0; i < bookCount; ++i) {
        if (strcmp(books[i].bookId, editID) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        getchar();
        printf("Book with ID '%s' does not exist.\n", editID);
        printf("\n--- Press any key to go back ---\n");
        getchar();
        return;
    }

    printf("\nCurrent details of the book:\n");
    printf("-------------------------------------------------------------\n");
    printf("ID: %s\n", books[found].bookId);
    printf("Title: %s\n", books[found].title);
    printf("Author: %s\n", books[found].author);
    printf("Price: %d\n", books[found].price);
    printf("Quantity: %d\n", books[found].quantity);
    printf("Publication Date: %02d/%02d/%4d\n",
           books[found].publication.day,
           books[found].publication.month,
           books[found].publication.year);
    printf("-------------------------------------------------------------\n");

    printf("\nEnter new details: \n");
    printf("New title: ");
    scanf(" %[^\n]", books[found].title);
    getchar();
    printf("New author: ");
    scanf(" %[^\n]", books[found].author);
    getchar();
    printf("New price: ");
    scanf("%d", &books[found].price);
    getchar();
    printf("New quantity: ");
    scanf("%d", &books[found].quantity);
    getchar();
    printf("New publication date (dd mm yyyy): ");
    scanf("%d %d %d",
        &books[found].publication.day,
        &books[found].publication.month,
        &books[found].publication.year);
    getchar();
    printf("Book updated successfully!\n");
    writeBooksToFile(books, bookCount, fileName);
    printf("--- Press any key to go back ---\n");
    getchar();
}

void deleteBook(book books[], int *bookCount, const char *filename) {
    readBooksFromFile(books, bookCount, filename);
    if (*bookCount == 0) {
        getchar();
        printf("\n\t*** Delete Book ***\n");
        printf("\t   Empty list\n");
        printf("--- Press any key to go back ---\n");
        getchar();
        return;
    }
    printf("\n\t*** Current Book List ***\n");
    printf("=========================================================================================================\n");
    printf("| %-6s | %-25s | %-20s | %-8s | %-10s | %-10s |\n",
           "ID", "Title", "Author", "Price", "Quantity", "Publication");
    printf("=========================================================================================================\n");
    for (int i = 0; i < *bookCount; ++i) {
        printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d  |\n",
               books[i].bookId, books[i].title, books[i].author,
               books[i].price, books[i].quantity,
               books[i].publication.day, books[i].publication.month, books[i].publication.year);
    }
    printf("=========================================================================================================\n");
    char deleteID[10];
    int found = -1;

    printf("\n\t*** Delete Book ***\n");
    printf("Enter the book ID you want to delete: ");
    scanf("%s", deleteID);
    for (int i = 0; i < *bookCount; ++i) {
        if (strcmp(books[i].bookId, deleteID) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        getchar();
        printf("Book with ID '%s' does not exist.\n", deleteID);
        printf("\n--- Press any key to go back ---\n");
        getchar();
        return;
    }

    printf("Do you want to delete the book with ID '%s'? (Y/N)\nEnter your choice: ", deleteID);
    getchar();
    char choiceDelete;
    scanf("%c", &choiceDelete);
    if (choiceDelete == 'N' || choiceDelete == 'n') {
        getchar();
        printf("\n--- You did not delete ---\n");
        printf("\n--- Press any key to go back ---\n");
        getchar();
        return;
    }
    for (int i = found; i < *bookCount - 1; ++i) {
        books[i] = books[i + 1];
    }
    getchar();
    (*bookCount)--;
    writeBooksToFile(books, *bookCount, filename);
    printf("Book deleted successfully and data saved to file!\n");
    printf("--- Press any key to go back ---\n");
    getchar();
}
//search book
void searchBookByName(book book[], int bookCount)
{
    if (bookCount == 0)
    {
        getchar();
        printf("\n\t*** Search Book by Name ***\n");
        printf("\t   Empty list\n");
        printf("--- Press any key to go back ---\n");
        getchar();
        return;
    }
    char searchName[100];
    int found = 0;
    printf("\n\t*** Search Book by Name ***\n");
    printf("Enter the book name or part of the name to search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    for (int i = 0; i < bookCount; i++)
    {
        if (strstr(book[i].title, searchName) != NULL)
        {
            if (!found)
            {
                printf("\n=========================================================================================================\n");
                printf("| %-6s | %-25s | %-20s | %-8s | %-10s | %-10s |\n",
                       "ID", "Title", "Author", "Price", "Quantity", "Publication");
                printf("=========================================================================================================\n");
                found = 1;
            }
            printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d  |\n",
                   book[i].bookId, book[i].title, book[i].author,
                   book[i].price, book[i].quantity,
                   book[i].publication.day, book[i].publication.month, book[i].publication.year);
        }
    }
    if (!found)
        printf("\nNo books found containing the name '%s'.\n", searchName);
    printf("--- Press any key to go back ---\n");
    getchar();
}
//sort Price
void sortBookByPrice(book bookTmp,book book[], int bookCount)
{
    int choice;
    printf("\n\t*** Sort Books by Price ***\n");
    printf("1. Ascending Order\n");
    printf("2. Descending Order\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    int i;
    for (i = 0; i < bookCount - 1; i++)
    {
    	int j;
        for (j = i + 1; j < bookCount; j++)
        {
            if ((choice == 1 && book[i].price > book[j].price) ||
                (choice == 2 && book[i].price < book[j].price))
            {
                bookTmp = book[i];
                book[i] = book[j];
                book[j] = bookTmp;
            }
        }
    }
    printf("\n\t\t\t*** Books sorted successfully! ***\n");
    printf("\n=========================================================================================================\n");
    printf("| %-6s | %-25s | %-20s | %-8s | %-10s | %-10s |\n",
            "ID", "Title", "Author", "Price", "Quantity", "Publication");
    printf("=========================================================================================================\n");
    for (i = 0; i < bookCount; i++)
    {
        printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d  |\n",
            book[i].bookId, book[i].title, book[i].author,
            book[i].price, book[i].quantity,
            book[i].publication.day, book[i].publication.month, book[i].publication.year);
    }
    getchar();
    printf("\n--- Press any key to go back ---\n");
    getchar();
}
//read file
void readBooksFromFile(book books[], int *bookCount, const char *fileName) {
    *bookCount = 0;

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s' for writing.\n", fileName);
        return;
    }

    while (fscanf(file, "%s %s %s %d %d %d/%d/%d",
                  books[*bookCount].bookId,
                  books[*bookCount].title,
                  books[*bookCount].author,
                  &books[*bookCount].quantity,
                  &books[*bookCount].price,
                  &books[*bookCount].publication.day,
                  &books[*bookCount].publication.month,
                  &books[*bookCount].publication.year) == 8) {
        (*bookCount)++;
    }
    fclose(file);
}
//write file
void writeBooksToFile(book books[], int bookCount, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file '%s' for writing.\n", filename);
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s %s %s %d %d %02d/%02d/%04d\n",
                books[i].bookId, books[i].title, books[i].author,
                books[i].price, books[i].quantity,
                books[i].publication.day, books[i].publication.month, books[i].publication.year);
    }
    fclose(file);
    printf("Books saved successfully to file '%s'.\n", filename);
}
int isValidBookId(char *id, book books[], int bookCount) {
    if (strchr(id, ' ') != NULL) {
        printf("Error: Book ID cannot contain spaces. Please enter a valid ID without spaces.\n");
        return 0;
    }
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, id) == 0) {
            printf("Error: Book ID '%s' already exists. Please enter a different ID.\n", id);
            return 0;
        }
    }
    return 1;
}




//customers management
void displayCustomerMenu(customer customers[], int *customerCount,
                         book books[], int *bookCount,
                         const char *customerFileName, const char *bookFileName) {
    int choice;
    do {
        system("cls");
        printf("\n======= Customer Management =======\n");
        printf("1. Display all customers\n");
        printf("2. Add a new customer\n");
        printf("3. Edit customer information\n");
        printf("4. Lock/Unlock customer\n");
        printf("5. Search customer by name\n");
        printf("6. Borrow books\n");
        printf("7. Return books\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                system("cls");
                displayCustomers(customers, *customerCount);
                break;
            case 2:
                system("cls");
                addCustomer(customers, customerCount);
                writeCustomersToFile(customers, *customerCount, customerFileName);
                break;
            case 3:
                system("cls");
                editCustomer(customers, *customerCount);
                writeCustomersToFile(customers, *customerCount, customerFileName);
                break;
            case 4:
                system("cls");
                toggleCustomerLock(customers, *customerCount);
                writeCustomersToFile(customers, *customerCount, customerFileName);
                break;
            case 5:
                system("cls");
                searchCustomerByName(customers, *customerCount);
                break;
            case 6:
                system("cls");
                borrowBook(customers, *customerCount, books, *bookCount);
                writeCustomersToFile(customers, *customerCount, customerFileName);
                writeBooksToFile(books, *bookCount, bookFileName);
                break;
            case 7:
                system("cls");
                returnBook(customers, *customerCount, books, *bookCount);
                writeCustomersToFile(customers, *customerCount, customerFileName);
                writeBooksToFile(books, *bookCount, bookFileName);
                break;
            case 0:
                system("cls");
                printf("Exiting customer management.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

void displayCustomers(customer customers[], int customerCount) {
    if (customerCount == 0) {
        printf("\n--- No customers available ---\n");
        printf("\n--- Press any key to go back ---\n");
        getchar();
        return;
    }
    printf("\n======= Customer List =======\n");
    printf("+------------+--------------------------------------------------+-----------------+----------+\n");
    printf("| %-10s | %-50s | %-15s | %-8s |\n", "ID", "Name", "Phone", "Status");
    printf("+------------+--------------------------------------------------+-----------------+----------+\n");
    for (int i = 0; i < customerCount; i++) {
        printf("| %-10s | %-50s | %-15s | %-8s |\n",
               customers[i].memberId,
               customers[i].name,
               customers[i].phone,
               customers[i].status == 0 ? "Active" : "Locked");
    }
    printf("+------------+--------------------------------------------------+-----------------+----------+\n");
    printf("\n--- Press any key to go back ---\n");
    getchar();
}

void addCustomer(customer customers[], int *customerCount) {
    customer newCustomer;
    printf("Enter customer ID: ");
    scanf("%s", newCustomer.memberId);
    getchar();
    printf("Enter customer name: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0';
    printf("Enter customer phone: ");
    fgets(newCustomer.phone, sizeof(newCustomer.phone), stdin);
    newCustomer.phone[strcspn(newCustomer.phone, "\n")] = '\0';
    newCustomer.status = 0;
    customers[*customerCount] = newCustomer;
    (*customerCount)++;
    printf("Customer added successfully.\n");
    printf("\n--- Press any key to go back ---\n");
    getchar();
}

void editCustomer(customer customers[], int customerCount) {
        if (customerCount == 0) {
        printf("\n--- No customers available ---\n");
        printf("\n--- Press any key to go back ---\n");
        getchar();
        return;
    }
    printf("\n======= Customer List =======\n");
    printf("+------------+--------------------------------------------------+-----------------+----------+\n");
    printf("| %-10s | %-50s | %-15s | %-8s |\n", "ID", "Name", "Phone", "Status");
    printf("+------------+--------------------------------------------------+-----------------+----------+\n");
    for (int i = 0; i < customerCount; i++) {
        printf("| %-10s | %-50s | %-15s | %-8s |\n",
               customers[i].memberId,
               customers[i].name,
               customers[i].phone,
               customers[i].status == 0 ? "Active" : "Locked");}
    char memberId[10];
    printf("Enter customer ID to edit: ");
    scanf("%s", memberId);

    int found = 0;
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].memberId, memberId) == 0) {
            found = 1;
            printf("Editing customer: %s\n", customers[i].name);
            printf("Enter new name: ");
            getchar();
            fgets(customers[i].name, sizeof(customers[i].name), stdin);
            customers[i].name[strcspn(customers[i].name, "\n")] = '\0'; // Remove trailing newline

            printf("Enter new phone: ");
            fgets(customers[i].phone, sizeof(customers[i].phone), stdin);
            customers[i].phone[strcspn(customers[i].phone, "\n")] = '\0'; // Remove trailing newline

            printf("Customer information updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Customer with ID %s not found.\n", memberId);
    }
    printf("\n--- Press any key to go back ---\n");
    getchar();
}

void toggleCustomerLock(customer customers[], int customerCount) {
    if (customerCount == 0) {
        printf("\n--- No customers available ---\n");
        printf("\n--- Press any key to go back ---\n");
        getchar();
        return;
    }
    printf("\n======= Customer List =======\n");
    printf("+------------+--------------------------------------------------+-----------------+----------+\n");
    printf("| %-10s | %-50s | %-15s | %-8s |\n", "ID", "Name", "Phone", "Status");
    printf("+------------+--------------------------------------------------+-----------------+----------+\n");
    for (int i = 0; i < customerCount; i++) {
        printf("| %-10s | %-50s | %-15s | %-8s |\n",
               customers[i].memberId,
               customers[i].name,
               customers[i].phone,
               customers[i].status == 0 ? "Active" : "Locked");}
    char memberId[10];
    printf("Enter customer ID to lock/unlock: ");
    scanf("%s", memberId);

    int found = 0;
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].memberId, memberId) == 0) {
            found = 1;
            customers[i].status = customers[i].status == 0 ? 1 : 0;
            printf("Customer status updated to: %s\n", customers[i].status == 0 ? "Active" : "Locked");
            break;
        }
    }

    if (!found) {
        printf("Customer with ID %s not found.\n", memberId);
    }
    printf("\n--- Press any key to go back ---\n");
    getchar();
}

void searchCustomerByName(customer customers[], int customerCount) {
    char name[50];
    printf("Enter name to search: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    printf("\nSearch results for '%s':\n", name);
    printf("%-10s %-50s %-15s %-10s\n", "ID", "Name", "Phone", "Status");
    for (int i = 0; i < customerCount; i++) {
        if (strstr(customers[i].name, name) != NULL) {
            printf("%-10s %-50s %-15s %-10s\n",
                   customers[i].memberId,
                   customers[i].name,
                   customers[i].phone,
                   customers[i].status == 0 ? "Active" : "Locked");
            found = 1;
        }
    }
    if (!found) {
        printf("No customers found with the name '%s'.\n", name);
    }
    getchar();
    printf("\n--- Press any key to go back ---\n");
    getchar();
}

void borrowBook(customer customers[], int customerCount, book books[], int bookCount) {
    char customerId[10];
    printf("Enter customer ID to borrow books: ");
    scanf("%s", customerId);
    int customerIndex = -1;
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].memberId, customerId) == 0) {
            customerIndex = i;
            break;
        }
    }
    if (customerIndex == -1) {
        printf("Customer not found!\n");
        return;
    }
    if (customers[customerIndex].status == 1) {
        printf("Customer is locked, cannot borrow books!\n");
        return;
    }
    int borrowedCount = 0;
    for (int i = 0; i < 100; i++) {
        if (strlen(customers[customerIndex].borrowedBooks[i].bookId) > 0) {
            borrowedCount++;
        }
    }
    if (borrowedCount >= 5) {
        printf("Customer has already borrowed 5 books, cannot borrow more.\n");
        return;
    }
    char bookId[10];
    printf("Enter book ID to borrow: ");
    scanf("%s", bookId);
    int bookIndex = -1;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, bookId) == 0) {
            bookIndex = i;
            break;
        }
    }
    if (bookIndex == -1) {
        printf("Book not found!\n");
        return;
    }
    int quantity;
    printf("Enter quantity to borrow: ");
    scanf("%d", &quantity);
    if (quantity > books[bookIndex].quantity) {
        printf("Not enough books in the library!\n");
        return;
    }
    for (int i = 0; i < 100; i++) {
        if (strlen(customers[customerIndex].borrowedBooks[i].bookId) == 0) {
            strcpy(customers[customerIndex].borrowedBooks[i].bookId, books[bookIndex].bookId);
            strcpy(customers[customerIndex].borrowedBooks[i].title, books[bookIndex].title);
            customers[customerIndex].borrowedBooks[i].quantity = quantity;
            books[bookIndex].quantity -= quantity;
            printf("Book(s) borrowed successfully!\n");
            return;
        }
    }
}
void returnBook(customer customers[], int customerCount, book books[], int bookCount) {
    char customerId[10];
    printf("Enter customer ID to return books: ");
    scanf("%s", customerId);
    int customerIndex = -1;
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].memberId, customerId) == 0) {
            customerIndex = i;
            break;
        }
    }
    if (customerIndex == -1) {
        printf("Customer not found!\n");
        return;
    }
    char bookId[10];
    printf("Enter book ID to return: ");
    scanf("%s", bookId);
    int bookIndex = -1;
    int borrowedIndex = -1;
    for (int i = 0; i < 100; i++) {
        if (strcmp(customers[customerIndex].borrowedBooks[i].bookId, bookId) == 0) {
            borrowedIndex = i;
            break;
        }
    }
    if (borrowedIndex == -1) {
        printf("Book not found in borrowed list!\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, bookId) == 0) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found in the library!\n");
        return;
    }
    books[bookIndex].quantity += customers[customerIndex].borrowedBooks[borrowedIndex].quantity;
    memset(&customers[customerIndex].borrowedBooks[borrowedIndex], 0, sizeof(customers[customerIndex].borrowedBooks[borrowedIndex]));  // Xóa sách khỏi danh sách mượn
    printf("Book returned successfully!\n");
}

void readCustomersFromFile(customer customers[], int *customerCount, const char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Could not open file: %s\n", fileName);
        *customerCount = 0;
        return;
    }

    *customerCount = fread(customers, sizeof(customer),100, file);
    fclose(file);
    printf("Loaded %d customers from the file.\n", *customerCount);
}
void writeCustomersToFile(customer customers[], int customerCount, const char *fileName) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Could not open file: %s\n", fileName);
        return;
    }

    fwrite(customers, sizeof(customer), customerCount, file);
    fclose(file);
    printf("Saved %d customers to the file.\n", customerCount);
}


void readAdminFromFile(Admin *admin, const char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Admin file not found! Using default admin credentials.\n");
        strcpy(admin->username, "admin");
        strcpy(admin->password, "12345");
        writeAdminToFile(admin, fileName);
        return;
    }

    if (fread(admin, sizeof(Admin), 1, file) != 1) {
        printf("Error: Could not read admin data from file. Using default credentials.\n");
        strcpy(admin->username, "admin");
        strcpy(admin->password, "12345");
    }

    fclose(file);
}

void writeAdminToFile(const Admin *admin, const char *fileName) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", fileName);
        return;
    }

    if (fwrite(admin, sizeof(Admin), 1, file) != 1) {
        printf("Error: Could not write admin data to file.\n");
    } else {
        printf("Admin data successfully saved to file.\n");
    }

    fclose(file);
}

void getMaskedPassword(char *password, int maxLength) {
    char ch;
    int index = 0;
    while ((ch = getch()) != '\r') {
        if (ch == '\b' && index > 0) {
            printf("\b \b");
            index--;
        } else if (index < maxLength - 1 && ch != '\b') {
            password[index++] = ch;
            printf("*");
        }
    }
    password[index] = '\0';
    printf("\n");
}
void updateAdminCredentials(const char *fileName) {
    Admin newAdmin;
    printf("Enter new admin username: ");
    fgets(newAdmin.username, sizeof(newAdmin.username), stdin);
    newAdmin.username[strcspn(newAdmin.username, "\n")] = '\0'; // Xóa newline

    printf("Enter new admin password: ");
    getMaskedPassword(newAdmin.password, sizeof(newAdmin.password));

    writeAdminToFile(&newAdmin, fileName);
    printf("Admin credentials updated successfully!\n");
}

int login(const Admin *admin) {
    char enteredUsername[50];
    char enteredPassword[50];
    int attempts = 0;

    while (attempts < 3) {
        printf("Enter username: ");
        fgets(enteredUsername, sizeof(enteredUsername), stdin);
        enteredUsername[strcspn(enteredUsername, "\n")] = '\0';
        printf("Enter password: ");
        getMaskedPassword(enteredPassword, sizeof(enteredPassword));
        if (strcmp(admin->username, enteredUsername) == 0 && strcmp(admin->password, enteredPassword) == 0) {
            printf("Login successful!\n");
            return 1;
        } else {
            attempts++;
            printf("Invalid username or password. Attempts remaining: %d\n", 3 - attempts);
        }
    }
    printf("Too many failed attempts. Program will now exit.\n");
    return 0;
}
