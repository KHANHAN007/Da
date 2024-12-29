#include <stdio.h>
#include "function.h"

int main()
{
	book book[100];
	int bookCount=0;
	int choice;
	do
	{
		displayMainMenu();
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				bookManagementMenu(book, &bookCount);
				break;
		}
	}while(choice !=0);
}
