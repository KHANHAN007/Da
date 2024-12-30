#include <stdio.h>
#include "function.h"

int main()
{
	const char *fileName="dataLibrary.dat";
	book b; 
	book book[100];
	int bookCount=countBooksInFile(fileName);
	int choice;
	do
	{
		displayMainMenu();
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				bookManagementMenu(b, book, &bookCount, fileName);
				break;
		}
	}while(choice !=0);
}
