#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
	const char *fileName="dataLibrary.dat";
	book b; 
	book book[100];
	int bookCount;
	int choice;
	do{	
		displayMainMenu();
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				system("cls");
				bookManagementMenu(b, book, &bookCount, fileName);
				break;
		}
	}while(choice !=0);
}
