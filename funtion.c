#include <stdio.h>
#include <string.h>
#include "function.h"

//Main menu
void displayMainMenu() {
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
void bookManagementMenu(book book[], int *bookCount)
{
	int choice;
	do{
		printf("\n\t*** Book Management ***\n");
		printf("=======================\n");
        printf("[1] Display Books\n");
        printf("[2] Add Book\n");
        printf("[3] Edit Book Information\n");
        printf("[4] Delete Book\n");
        printf("[5] Search Book by Name\n");
        printf("[6] Sort Books by Price\n");
        printf("[7] Validate Book Data\n");
        printf("[8] Save Book Data\n");
        printf("[0] Back to Main Menu\n");
        printf("=======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice)
        {
        	case 1:
        		displayBooks(book, *bookCount);
        		break;
        	case 2:
        		addBook(book, bookCount);
        		break;
        	case 3:
        		editBook(book, *bookCount);
        		break;
		}
	}while(choice !=0);
}

//display book
void displayBooks(book book[], int bookCount)
{
	if (bookCount==0)
	{
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
	int i;
	for (i = 0; i < bookCount; ++i) 
	{
       	printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d |\n", 
               book[i].bookId, book[i].title, book[i].author, 
               book[i].price, book[i].quantity, 
               book[i].publication.day, book[i].publication.month, book[i].publication.year);
    }
	 printf("=========================================================================================================\n");
}
//add book
void addBook(book books[], int *bookCount) {
    int numBooksToAdd;
    printf("\n\t*** Add Books ***\n");
    printf("=========================\n");
    printf("Enter the number of books to add: ");
    scanf("%d", &numBooksToAdd);
    getchar();
    int i; 
    for (i = 0; i < numBooksToAdd; i++) {
        char tempId[10];
        int isDuplicate;

        printf("\nAdding book number %d\n", *bookCount + 1);
        do {
            isDuplicate = 0;
            printf("Enter book Id: ");
            scanf("%s", tempId);
            getchar();
			int j; 
            for (j = 0; j < *bookCount; j++) {
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
}
//edit book
void editBook(book book[], int bookCount)
{
	if (bookCount==0)
	{
		getchar(); 
		printf("\n\t*** Edit Book ***\n");
		printf("\t   Empty list\n");
		printf("--- Press any key to go back ---\n"); 
		getchar(); 
		return;
	}
	char editID[10];
	int found = -1;
	printf("\n\t*** Edit Book ***\n");
	printf("Enter the book ID you want to edit: ");
	scanf("%s", editID);
	editID[strcspn(editID,"\n")]='\0';
	int i; 
	for(i=0;i<bookCount;++i)
	{
		if(strcmp(book[i].bookId, editID)==0)
		{
			found=i;
			break; 
		}
	}
	if(found==-1)
	{
		printf("Book with ID '%s' does not exist.\n", editID);
		return;
	}
	printf("\nCurrent details of the book:\n");
	printf("-------------------------------------------------------------\n");
	printf("ID: %s\n", book[found].bookId);
	printf("Title: %s\n", book[found].title);
	printf("Author: %s\n", book[found].author);
	printf("Price: %d\n", book[found].price);
	printf("Quantity: %d\n",book[found].quantity);
	printf("Publication Date: %02d/%02d/%4d\n",  
			book[found].publication.day,
           	book[found].publication.month,
           	book[found].publication.year); 
    printf("-------------------------------------------------------------\n");
    printf("\nEnter new details: \n"); 
    printf("New title: ");
    scanf(" %[^\n]", book[found].title);
    getchar();
    printf("New author: ");
    scanf(" %[^\n]", book[found].author);
    getchar();
    printf("New price: ");
    scanf("%d", &book[found].price);
    getchar();
    printf("New quantity: ");
    scanf("%d", &book[found].quantity);
    getchar();
    printf("New publication date (dd mm yyyy): ");
    scanf("%d %d %d",
        &book[found].publication.day,
        &book[found].publication.month,
        &book[found].publication.year);
    getchar();
    displayBooks(book,bookCount);
}
