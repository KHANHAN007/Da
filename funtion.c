#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void bookManagementMenu(book bookTmp,book book[], int *bookCount, const char *fileName)
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
        printf("[7] Save Book Data\n");
        printf("[0] Back to Main Menu\n");
        printf("=======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice)
        {
        	case 1:
        		system("cls");
        		displayBooks(book, *bookCount);
        		break;
        	case 2:
        		system("cls");
        		addBook(book, bookCount, fileName);
        		break;
        	case 3:
        		editBook(book, *bookCount);
        		break;
        	case 4:
        		deleteBook(book, bookCount);
        		break;
        	case 5:
        		searchBookByName(book,*bookCount);
        		break;
        	case 6:
				sortBookByPrice(bookTmp, book, *bookCount);
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
       	printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d  |\n", 
               book[i].bookId, book[i].title, book[i].author, 
               book[i].price, book[i].quantity, 
               book[i].publication.day, book[i].publication.month, book[i].publication.year);
    }
	 printf("=========================================================================================================\n");
}
//add book
void addBook(book books[], int *bookCount,const char *fileName) {
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
        writeBooksToFile(books, *bookCount, fileName);
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
		getchar();
		printf("Book with ID '%s' does not exist.\n", editID);
		printf("\n--- Press any key to go back ---\n"); 
		getchar();
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
//delete book
void deleteBook(book book[], int *bookCount)
{
    if (*bookCount == 0)
    {
    	getchar();
        printf("\n\t*** Edit Book ***\n");
        printf("\t   Empty list\n");
        printf("--- Press any key to go back ---\n");
        getchar();
        return;
    }

    char deleteID[10];
    int found = -1;

    printf("\n\t*** Delete Book ***\n");
    printf("Enter the book ID you want to delete: ");
    scanf("%s", deleteID);
	int i;
    for (i = 0; i < *bookCount; ++i)
    {
        if (strcmp(book[i].bookId, deleteID) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
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

    if (choiceDelete == 'N' || choiceDelete == 'n')
    {
        printf("\n--- You did not delete ---\n");
        printf("\n--- Press any key to go back ---\n");
        getchar();
        return;
    }
    for (i = found; i < *bookCount - 1; ++i)
    {
        book[i] = book[i + 1];
    }

    (*bookCount)--;
    printf("Book deleted successfully!\n");
}
//search book
void searchBookByName(book book[], int bookCount)
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
    char searchName[100];
    int found = 0;

    printf("\n\t*** Search Book by Name ***\n");
    printf("Enter the book name or part of the name to search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    printf("\n=========================================================================================================\n");
    printf("| %-6s | %-25s | %-20s | %-8s | %-10s | %-10s |\n", 
           "ID", "Title", "Author", "Price", "Quantity", "Publication");
    printf("=========================================================================================================\n");
	int i; 
    for (i = 0; i < bookCount; i++)
    {
        if (strstr(book[i].title, searchName) != NULL)
        {
            printf("| %-6s | %-25s | %-20s | %-8d | %-10d | %02d/%02d/%4d  |\n", 
                book[i].bookId, book[i].title, book[i].author, 
               	book[i].price, book[i].quantity, 
               	book[i].publication.day, book[i].publication.month, book[i].publication.year);
            found = 1;
        }
    }
    if (!found)
        printf("\nNo books found containing the name '%s'.\n", searchName);
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
    printf("\nBooks sorted successfully!\n");
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
}
//read file
//void readBooksFromFile(book books[], int *bookCount, const char *filename)
//{
//    FILE *file = fopen(filename, "r");
//    if (!file)
//    {
//        printf("Error: Could not open file '%s' for reading.\n", filename);
//        return;
//    }
//    *bookCount = 0;
//    while (fscanf(file, "%s %[^\n] %[^\n] %d %d %d %d %d", 
//			books[*bookCount].bookId, books[*bookCount].title, books[*bookCount].author, 
//            books[*bookCount].price, books[*bookCount].quantity, 
//            books[*bookCount].publication.day, books[*bookCount].publication.month, books[*bookCount].publication.year) != EOF)
//    {
//        (*bookCount)++;
//    }
//    fclose(file);
//    printf("Books loaded successfully from file '%s'.\n", filename);
//}
//write file
//void writeBooksToFile(book books[], int bookCount, const char *filename)
//{
//    FILE *file = fopen(filename, "w");
//    if (!file)
//    {
//        printf("Error: Could not open file '%s' for writing.\n", filename);
//        return;
//    }
//    int i;
//    for (i = 0; i < bookCount; i++)
//    {
//        fprintf(file, "%s %[^\n] %[^\n] %d %d %d %d %d", 
//			books[bookCount].bookId, books[bookCount].title, books[bookCount].author, 
//            books[bookCount].price, books[bookCount].quantity, 
//            books[bookCount].publication.day, books[bookCount].publication.month, books[bookCount].publication.year);
//    }
//    fclose(file);
//    printf("Books saved successfully to file '%s'.\n", filename);
//}
//count book 
//int countBooksInFile(const char *fileName)
//{
//    FILE *file = fopen(fileName, "r");
//    if (!file)
//    {
//        printf("File not found.\n");
//        return 0;
//    }
//
//    int count = 0;
//    char buffer[256];
//    while (fgets(buffer, sizeof(buffer), file))
//    {
//        count++;
//    }
//    fclose(file);
//    return count / 7;
//}

