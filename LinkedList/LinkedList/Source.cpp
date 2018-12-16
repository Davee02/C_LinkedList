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
Person *Remove(Person *pHead, Person *pToDelete);
Person *Sort(Person *pHead);
void Output(Person *pHead);

int main(int argc, char *argv[])
{
	// Initialize the pseudo-random number-generator and use the current time since midnight in milliseconds as the seed
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

			// "strtok" is used to remove the newline-char "\n" from the end of the string, so that comparing doesn't fail
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
// This function displays all the menu-points which can be used
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
// This function returns a random uppercase character
char GetRandomCharacter()
{
	return GetRandomNumber('A', 'Z');
}

// Author: David
// This function returns a random integer, which is between the under-bound and the upper-bound
// The two bounds are inclusive
int GetRandomNumber(int underBound, int upperBound)
{
	return rand() % (upperBound + 1 - underBound) + underBound;
}

// Author: David
// This function takes a integer as a parameter, which is for the number of the to be created elements
// This function creates a new list of people with the provided count of elements
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
// This function creates a new person with a random birthyear, first- nad lastname
Person *CreateNewPerson()
{
	Person *pNew = (Person *)malloc(sizeof(Person));

	// The birthyear is between 1900 and 2018
	pNew->Birthyear = GetRandomNumber(1900, 2018);

	// The firstname is a random uppercase char
	pNew->Firstname[0] = GetRandomCharacter();
	// The string has to be terminated with '\0'
	pNew->Firstname[1] = '\0';

	// The lastname is a random uppercase char
	pNew->Lastname[0] = GetRandomCharacter();
	// The string has to be terminated with '\0'
	pNew->Lastname[1] = '\0';

	// The next element of the list is set to NULL
	pNew->pNext = NULL;

	return pNew;
}

// This function takes the pointer to first node of a linked-list and two strings as a parameter
// This function deletes all peoplem from the list and frees the memory
Person *Dispose(Person *pHead)
{
	return NULL;
}

// This function takes the pointer to first node of a linked-list and two strings as a parameter
// This function removes all people with the provided first- and lastname from the list
Person *Remove(Person *pHead, char firstName[], char lastName[])
{
	if (firstName == NULL || lastName == NULL)
		return pHead;

	for (Person *pTmp = pHead; pTmp != NULL; pTmp = pTmp->pNext)
	{
		if (strcmp(firstName, pTmp->Firstname) == 0 &&
			strcmp(lastName, pTmp->Lastname) == 0)
		{
			printf("Found matching person\n");
			pHead = Remove(pHead, pTmp);
		}
	}

	return pHead;
}

// This function takes the pointer to first node of a linked-list as a parameter
// This functions sorts the whole list by the fist- and then by the lastname
Person *Sort(Person *pHead)
{
	return NULL;
}

// This function takes the pointer to first node of a linked-list as a parameter
// This function displays all people in the list.
// Example: "Person #21: Max Muster"
void Output(Person *pHead)
{
	int i = 1;
	for (Person *pTmp = pHead; pTmp != NULL; pTmp = pTmp->pNext, i++)
	{
		printf("Person #%i: %s %s (%i)\n", i, pTmp->Firstname, pTmp->Lastname, pTmp->Birthyear);
	}
}

// This function takes the pointer to first node of a linked-list and the pointer to the to be removed element as a parameter
// This function removes the provided person from the list
Person *Remove(Person *pHead, Person *pToDelete)
{
	// If the start-point of the list is NULL, return NULL
	if (pHead == NULL)
	{
		return NULL;
	}
	// If the element, which should be removed, is NULL, change nothing
	if (pToDelete == NULL)
	{
		return pHead;
	}

	// When the start-point equals the to-be-deleted-element, the to-be-deleted-element is the first element in the list
	if (pHead == pToDelete)
	{
		pHead = pHead->pNext;
	}
	// When the next element of the to-be-deleted-element is NULL, the to-be-deleted-element is the last element in the list
	else if (pToDelete->pNext == NULL)
	{
		Person *pTmp = pHead;

		// Traverse to the specified element
		while (pTmp->pNext != pToDelete)
			pTmp = pTmp->pNext;

		pTmp->pNext = NULL;
	}
	// The to-be-deleted-element is in the middle of the list
	else
	{
		Person *pTmp = pHead;
		
		// Traverse to the specified element
		while (pTmp->pNext != pToDelete)
			pTmp = pTmp->pNext;

		pTmp->pNext = pToDelete->pNext;
	}

	return pHead;
}