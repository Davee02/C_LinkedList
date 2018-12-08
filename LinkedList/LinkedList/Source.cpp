#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef struct Person
{
	char Firstname[40];
	char Lastname[40];
	int Birthyear;
	struct Person* pNext;
} Person;

void DisplayMenu();
char GetRandomCharacter();
int GetRandomNumber(int underBound, int upperBound);
Person* Create(int elementCount);
Person* Dispose(Person* pHead);
Person* Remove(char firstName[], char lastName[]);
Person* Sort(Person* pHead);
void Output(Person* pHead);

int main(int argc, char* argv[]) 
{
	srand((unsigned)time(NULL));
	int command = 0;

	DisplayMenu();
	while(true)
	{
		printf("Please the command you want to execute(0-6, -1 to quit):\n");
		scanf_s("%d", &command);
		if (command == -1)
			break;

		switch(command)
		{
		case 0:
			DisplayMenu();
			break;

		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		default:
			DisplayMenu();
			break;
		}
	}

	return 0;
}


// Author: David
void DisplayMenu()
{
	printf("---------- LinkedList by David H. and Yannick F. ----------\n");
	printf("0) Display the menu\n");
	printf("1) Create new list\n");
	printf("2) Delete whole list\n");
	printf("3) Delete specific item\n");
	printf("4) Sort list\n");
	printf("6) Output the list\n");
	printf("-1) Quit program\n");
	printf("------------------------------------------------------------------------\n");
}