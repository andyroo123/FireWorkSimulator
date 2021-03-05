/* Andrew Kolarits */
#include <stdio.h>
#include "linkedlist.h"

/*Test the insert, iterate and sort functions of linkedlist */

/* Comparision function that puts list in increasing order */
int lastChar(void *p1, void *p2)
{
	char *s1 = p1, *s2 = p2;
	return (*s1 > *s2);
}

/* Comparision function that puts list in decreasing order */
int firstChar(void *p1, void *p2)
{
	char *s1 = p1, *s2 = p2;
	return (*s1 < *s2);
}
/* Both comparison functions only compare the first char of a string */

/* Print function that prints the void pointer */
void print(void *data)
{
	char *s = data;
	printf("String is: %s\n", s);
}

int main()
{
	void *list = NULL; /* Instantiate list as NULL */
	char *first = "D", *second = "B"; /* Things to add to list */
	
	
	/* Add 'D' to list */
	insert(&list, first, lastChar, 1);

	printf("\nCALLING ITERATE\n");
	iterate(list, print);
	
	/* Add 'B' to list */
	insert(&list, second, lastChar, 1);
	
	printf("\nCALLING ITERATE\n");
	iterate(list, print);

	printf("\nSORTING");
	sort(list, firstChar); /*Sort list in increasing order */
	printf("\nCALLING ITERATE\n");
	iterate(list,print);

	return 0;
}
