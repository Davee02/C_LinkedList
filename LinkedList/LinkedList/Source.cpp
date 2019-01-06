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
void Dispose(Person *pHead);
Person *Remove(Person *pHead, char firstName[], char lastName[]);
Person *Remove(Person *pHead, Person *pToDelete);
Person *Quicksort(Person *pHead);
Person *Bubblesort(Person *pHead);
void Swap(Person *p1, Person *p2);
void Output(Person *pHead);
bool IsFirstPersonBigger(Person *p1, Person *p2);
int GetLength(Person *pHead);
Person *GetRandomPerson(Person *pHead);
Person *GetLastElement(Person *pHead);
Person *JoinLists(Person *pList1, Person *pPivot, Person *pList2);

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
			Dispose(pHead);
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
			printf("Which sorting-algorithm do you want to use? [q]uicksort or [b]ubblesort? ");
			char answer;
			scanf("%c", &answer);

			clock_t startTime = clock();
			if (answer == 'q')
			{
				pHead = Quicksort(pHead);
			}
			else
			{
				pHead = Bubblesort(pHead);
			}
			clock_t endTime = clock();

			double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("Sorting took %f seconds\n", timeSpent);
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

// Displays all the menu-points which can be used
void DisplayMenu()
{
	printf("___________________________________________________________________________\n");
	printf("------------------ LinkedList by David H. and Yannick F. ------------------\n");
	printf("___________________________________________________________________________\n\n");
	printf("0) Display the menu\n");
	printf("1) Create new list\n");
	printf("2) Delete whole list\n");
	printf("3) Delete specific item\n");
	printf("4) Sort list\n");
	printf("5) Output the list\n");
	printf("-1) Quit program\n");
	printf("___________________________________________________________________________\n\n");
}

// Returns a random uppercase character
char GetRandomCharacter()
{
	return GetRandomNumber('A', 'Z');
}

// Returns a random integer, which is between the under-bound and the upper-bound
// The two bounds are inclusive
int GetRandomNumber(const int underBound, const int upperBound)
{
	return rand() % (upperBound + 1 - underBound) + underBound;
}

// Takes a integer as a parameter, which is for the number of the to be created elements
// Creates a new list of people with the provided count of elements
Person *Create(const int elementCount)
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

// Creates a new person with a random birthyear, first- nad lastname
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

// Takes the pointer to first node of a linked-list and two strings as a parameter
// Deletes all people from the list and frees the memory
void Dispose(Person *pHead)
{
	Person *pTmp = pHead;

	while (pTmp != NULL)
	{
		Person *pNextElement = pTmp;
		pTmp = pTmp->pNext;
		free(pNextElement);
	}
}

// Takes the pointer to first node of a linked-list and two strings as a parameter
// Removes all people with the provided first- and lastname from the list
Person *Remove(Person *pHead, char firstName[], char lastName[])
{
	if (firstName == NULL || lastName == NULL)
		return pHead;

	int deleteCounter = 0;
	for (Person *pTmp = pHead; pTmp != NULL; pTmp = pTmp->pNext)
	{
		if (strcmp(firstName, pTmp->Firstname) == 0 &&
			strcmp(lastName, pTmp->Lastname) == 0)
		{
			pHead = Remove(pHead, pTmp);
			deleteCounter++;
		}
	}

	printf("%d %s %s deleted\n\n", deleteCounter, deleteCounter > 1 ? "people" : "person", deleteCounter > 1 ? "were" : "was");

	return pHead;
}

// Takes the pointer to first node of a linked-list as a parameter
// Sorts the whole list by the first- and then by the lastname with the algorithm "quicksort"
// The algorithm works like this:
/* 
1) If the list has 0 or 1 element, the list is sorted.
2) Otherwise:
	2.1) Choose a random element in the list (=pivot).
	2.2) Split the list into three sub-lists: elements smaller than the pivot, elements equal to the pivot, and elements bigger than the pivot.
	2.3) Sort the smaller- and bigger-sublist (begin at step 1)).
	2.4) Merge the three lists to get a single, sorted list
	
Here's a short example with 5 elements:

Unsorted: [5]→[7]→[1]→[9]→[3]
The pivot is [7]
Split the list into three sublists: [5]→[1]→[3] (smaller than pivot); [7] (pivot); [9] (bigger than pivot)
	Sort the two sublists:
	Sublist 1: [5]→[1]→[3]
	The pivot is [5]
	Split the list into three sublists: [1]→[3] (smaller than pivot); [5] (pivot); [] (bigger than pivot)
		Sort the two sublists:
		Sublist 1: [1]→[3]
		The pivot is [1]
		Split the list into three sublists: [] (smaller than pivot); [1] (pivot); [3] (bigger than pivot)
			Sort the two sublists:
			Sublist 1: []
			List is 0 element big so the list is already sorted
			Sublist 3: []
			List is 1 element big so the list is already sorted
			Because no list can be split more, merge the two lists with the pivot in the middle: [1]→[3]
		Sublist 2: []
		List is 0 element big so the list is already sorted
		Because no list can be split more, merge the two lists with the pivot in the middle: [1]→[3]→[5]
	Sublist 2: [9]
	List is 1 element big so the list is already sorted
	Because no list can be split more, merge the two lists with the pivot in the middle: [1]→[3]→[5]→[7]→[9]
Sorted: [1]→[3]→[5]→[7]→[9]
*/
Person *Quicksort(Person *pHead)
{
	if (pHead == NULL || pHead->pNext == NULL)
		return pHead; // The list is already sorted because there are 0 or 1 elements in it
	Person *pTmp = pHead;

	Person *pLeftSubList = NULL, *pRightSubList = NULL;
	Person *pPivot = GetRandomPerson(pTmp);

	for (Person *pCurrentElement = pTmp; pCurrentElement != NULL;)
	{
		Person *pNextElement = pCurrentElement->pNext;

		if (pCurrentElement != pPivot)
		{
			if (IsFirstPersonBigger(pCurrentElement, pPivot))
			{
				pCurrentElement->pNext = pRightSubList;
				pRightSubList = pCurrentElement;
			}
			else
			{
				pCurrentElement->pNext = pLeftSubList;
				pLeftSubList = pCurrentElement;
			}
		}
		pCurrentElement = pNextElement;
	}

	return JoinLists(Quicksort(pLeftSubList), pPivot, Quicksort(pRightSubList));
}

// Takes the pointer to first node of a linked-list as a parameter
// Sorts the whole list by the first- and then by the lastname with the algorithm "bubblesort"
// The algorithm works like this:

/*
1) If the list has 0 or 1 element, the list is sorted.
2) Otherwise:
	2.1) Compares current element with the next element
	2.2) if the first element is bigger the date between both gets swapped
	2.3) current elements gets set to next element
	2.4) those steps repeat until no no swaps were made

Here's a short example with 5 elements:

Unsorted: [5]→[7]→[1]→[9]→[3]

current element: [5]
	[5] is smaller than [7] -> nothing happens

current element: [7]
	[7] is bigger than [1] -> [7] and [1] swaps

new order: [5]→[1]→[7]→[9]→[3]

current element: [7]
	[7] is smaller than [9] -> nothing happens

current element: [9]
	[9] is bigger than [3] -> [9] and [3] swaps

new order: [5]→[1]→[7]→[3]→[9]

repeat(swapped == true):

current element: [5]
	[5] is bigger than [1] -> [5] and [1] swaps

new order: [1]→[5]→[7]→[3]→[9]

current element: [5]
	[5] is smaller than [7] -> nothing happens

current element: [7]
	[7] is bigger than [3] -> [7] and [3] swaps

new order: [1]→[5]→[3]→[7]→[9]

current element: [7]
	[7] is smaller than [9] -> nothing happens

repeat(swapped == true):

current element: [1]
	[1] is smaller than [5] -> nothing happens

current element: [5]
	[5] is bigger than [3] -> [5] and [3] swaps

new order: [1]→[3]→[5]→[7]→[9]

current element: [5]
	[5] is smaller than [7] -> nothing happens

current element: [7]
	[7] is smaller than [9] -> nothing happens

repeat(swapped == true):

current element: [1]
	[1] is smaller than [3] -> nothing happens

current element: [3]
	[3] is smaller than [5] -> nothing happens

current element: [5]
	[5] is smaller than [7] -> nothing happens

current element: [7]
	[7] is smaller than [9] -> nothing happens

no repeat(swapped == false)
*/
Person *Bubblesort(Person *head)
{
	int swapped;

	Person *pCurrentElement = head;

	if (pCurrentElement == NULL)
	{
		return head;
	}

	do
	{
		swapped = 0;
		pCurrentElement = head;

		while (pCurrentElement->pNext != NULL)
		{
			if (IsFirstPersonBigger(pCurrentElement, pCurrentElement->pNext))
			{
				Swap(pCurrentElement, pCurrentElement->pNext);
				swapped = 1;
			}

			pCurrentElement = pCurrentElement->pNext;
		}		
	}
	while (swapped);

	return head;
}

//Swaps the data between two Elements
void Swap(Person *p1, Person *p2)
{
	char tmpFirstname[40];
	char tmpLastname[40];
	strcpy_s(tmpFirstname, p1->Firstname);
	strcpy_s(tmpLastname, p1->Lastname);
	int tmpBirthyear = p1->Birthyear;
	
	strcpy_s(p1->Firstname, p2->Firstname);
	strcpy_s(p1->Lastname, p2->Lastname);
	p1->Birthyear = p2->Birthyear;

	strcpy_s(p2->Firstname, tmpFirstname);
	strcpy_s(p2->Lastname, tmpLastname);
	p2->Birthyear = tmpBirthyear;
}

// Takes the pointer to first node of a linked-list as a parameter
// Displays all people in the list.
// Example: "Person #21: Max Muster"
void Output(Person *pHead)
{
	int i = 1;
	for (Person *pTmp = pHead; pTmp != NULL; pTmp = pTmp->pNext, i++)
	{
		printf("Person #%i: %s %s (%i)\n", i, pTmp->Firstname, pTmp->Lastname, pTmp->Birthyear);
	}
}

// Takes the pointer to first node of a linked-list and the pointer to the to be removed element as a parameter
// Removes the provided person from the list
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


bool IsFirstPersonBigger(Person *p1, Person *p2)
{
	if (p1->Firstname[0] > p2->Firstname[0])
		return true;
	if (p1->Firstname[0] < p2->Firstname[0])
		return false;

	if (p1->Lastname[0] > p2->Lastname[0])
		return true;
	if (p1->Lastname[0] < p2->Lastname[0])
		return false;

	return false;
}

// Returns the count of people in the linked list
int GetLength(Person *pHead)
{
	int counter = 0;
	for (Person *pTmp = pHead; pTmp != NULL; pTmp = pTmp->pNext)
	{
		++counter;
	}
	return counter;
}

// Returns a random person in the linked list
Person *GetRandomPerson(Person *pHead)
{
	int listLength = GetLength(pHead);
	int personIndex = GetRandomNumber(0, listLength - 1);

	Person *pTmp = pHead;
	for (int currentIndex = 0; currentIndex < personIndex; currentIndex++)
	{
		pTmp = pTmp->pNext;
	}

	return pTmp;
}

// Returns the last element in the linked list
Person *GetLastElement(Person *pHead)
{
	Person *pTmp = NULL;
	for (pTmp = pHead; pTmp->pNext != NULL; pTmp = pTmp->pNext)
		;

	return pTmp;
}

// This is a utility-function for the quicksort-algorithm.
// It joins the left list, the pivot and the right list to one list
// The order is the following: [Head left list]→[...]→[Tail left list]→[Head pivot]→[...]→[Tail pivot]→[Head right list]→[...]→[Tail right list]
Person *JoinLists(Person *pList1, Person *pPivot, Person *pList2)
{
	pPivot->pNext = pList2;

	if (pList1 == NULL)
	{
		return pPivot;
	}

	Person *pList1LastElement = GetLastElement(pList1);
	pList1LastElement->pNext = pPivot;

	return pList1;
}