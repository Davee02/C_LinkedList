#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

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
Person *Dispose(Person *pHead);
Person *Remove(Person *pHead, char firstName[], char lastName[]);
Person *Sort(Person *pHead);
void Output(Person *pHead);

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	Person *pHead = NULL;

	int command = 0;

	DisplayMenu();
	while (true)
	{
		printf("Please write the command you want to execute(0-6, -1 to quit):\n");
		scanf("%d", &command);
		fgetchar();
		if (command == -1)
			break;

		switch (command)
		{
		case 0:
			DisplayMenu();
			break;

		case 1:
		{
			printf("How many people do you want to create? ");
			int numberOfElements = 0;
			scanf("%d", &numberOfElements);
			fgetchar();
			pHead = Create(numberOfElements);
		}
		break;

		case 2:
		{
			pHead = Dispose(pHead);
		}
		break;

		case 3:
		{
			char firstName[40], lastName[40];
			printf("What's the firstname of the person to be deleted? ");
			fgets(firstName, sizeof(firstName), stdin);

			printf("What's the lastname of the person to be deleted? ");
			fgets(lastName, sizeof(lastName), stdin);

			pHead = Remove(pHead, strtok(firstName, "\n"), strtok(lastName, "\n"));
		}
		break;

		case 4:
		{
			pHead = Sort(pHead);
		}
		break;

		case 5:
		{
			Output(pHead);
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
	printf("5) Output the list\n");
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

Person *Dispose(Person *pHead)
{
	return NULL;
}

Person *Remove(Person *pHead, char firstName[], char lastName[])
{
	if(firstName == NULL || lastName == NULL)
		return pHead;

	for (Person *pTmp = pHead; pTmp != NULL; pTmp = pTmp->pNext)
	{
		if(strcmp(firstName, pTmp->Firstname) == 0 && 
			strcmp(lastName, pTmp->Lastname) == 0)
		{
			printf("Found matching person\n");
		}
	}

	return pHead;
}

Person *Sort(Person *pHead)
{
	return NULL;
}

void Output(Person *pHead)
{
	int i = 1;
	for (Person *pTmp = pHead; pTmp != NULL; pTmp = pTmp->pNext, i++)
	{
		printf("Person #%i: %s %s (%i)\n", i, pTmp->Firstname, pTmp->Lastname, pTmp->Birthyear);
	}
}