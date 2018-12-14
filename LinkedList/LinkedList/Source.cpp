#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef struct Person
{
	char Firstname[40];
	char Lastname[40];
	int Birthyear;
	struct Person *pNext;
} Person;

void DisplayMenu();
char GetRandomCharacter();
int GetRandomNumber(int underBound, int upperBound);
Person *Create(int elementCount);
Person *CreateNewPerson();
void Dispose(Person *pHead);
Person *Remove(char firstName[], char lastName[]);
Person *Sort(Person *pHead);
void Output(Person *pHead);

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	Person *pHead = Create(1);
	int command = 0;

	DisplayMenu();
	while (true)
	{
		printf("Please the command you want to execute(0-6, -1 to quit):\n");
		scanf("%d", &command);
		fflush(stdin);
		if (command == -1)
			break;

		switch (command)
		{
		case 0:
			DisplayMenu();
			break;

		case 1:
		{
			printf("How many people do you want to create?");
			int numberOfElements = 0;
			scanf("%d", &numberOfElements);
			fflush(stdin);
			pHead = Create(numberOfElements);
		}
		break;

		case 2:
		{
			// Code here
		}
		break;

		case 3:
		{
			// Code here
		}
		break;

		case 4:
		{
			// Code here
		}
		break;

		case 5:
		{
			// Code here
		}
		break;

		case 6:
		{
			// Code here
		}
		break;
		
		default:
			DisplayMenu();
			break;
		}
	}

	Dispose(pHead);
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

// Author: David
char GetRandomCharacter()
{
	return GetRandomNumber('A', 'Z');
}

// Author: David
int GetRandomNumber(int underBound, int upperBound)
{
	return rand() % (upperBound + 1 - underBound) + underBound;
}

// Author: David
Person *Create(int elementCount)
{
	Person *pHead = NULL;

	for (int i = 0; i < elementCount; i++)
	{
		Person *pHeadOld = pHead;
		pHead = CreateNewPerson();
		pHead->pNext = pHeadOld;
	}

	return pHead;
}

// Author: David
Person *CreateNewPerson()
{
	Person *pNew = (Person *)malloc(sizeof(Person));
	pNew->Birthyear = GetRandomNumber(1900, 2018);
	pNew->Firstname[0] = GetRandomCharacter();
	pNew->Firstname[1] = '\0';
	pNew->Lastname[0] = GetRandomCharacter();
	pNew->Lastname[1] = '\0';
	pNew->pNext = NULL;

	return pNew;
}

void Dispose(Person *pHead)
{
}

Person *Remove(char firstName[], char lastName[])
{
	return NULL;
}

Person *Sort(Person *pHead)
{
	return NULL;
}

void Output(Person *pHead)
{
}