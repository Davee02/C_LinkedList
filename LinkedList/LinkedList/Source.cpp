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

int main(int argc, char* argv[]) 
{
	srand((unsigned)time(NULL));

	return 0;
}