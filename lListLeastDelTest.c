/* Andrew Kolarits */
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Test the insert, iterate, least and deleteSome functions of linkedlist */

/* When used as comparision function with insert,
 * sorts items from greatest to least */
int lastChar(void *p1, void *p2)
{
	char *s1 = p1, *s2 = p2;
	return (*s1 > *s2);
}

/* When used as numberic function with least,
 * returns the smallest numberic element of the list */
double getLeast(void *data)
{
	char *s1 = data;
	return atof(s1);
}

/* Practice delete function, that when used with delete some,
 *  * removes any element that is '2' */
int delNumTwo(void *data)
{
	char *s1 = data;
	if(atof(s1) == 2)
		return 1;
	return 0;
}

/* Practice action function, that when used with delete some,
 * prints to the screen what element got deleted */
void rid(void *data)
{
	char *s1 = data;
	printf("\nDELETING: %s\n", s1);
}

/* Both comparison functions only compare the first char of a string */

/* When used with iterate function,
 * prints the elemnts of the list */
void print(void *data)
{
	char *s = data;
	printf("String is: %s\n", s);
}

int main()
{
	void *list = NULL;
	char *one = "1", *two = "2", *three = "3";
	double leastWhenListEmpty, leastWhenListNotEmpty;
	
	/* Testing what exactly least returns when called on an empty list */
	leastWhenListEmpty = least(list, getLeast);
	printf("\nCALLING LEAST ON EMPTY LIST\nleast: %f\n", leastWhenListEmpty);
	if(leastWhenListEmpty != leastWhenListEmpty) printf("list is empty\n");
	else printf("list is not empty\n");

	/* Add '1' to list */
	insert(&list, one, lastChar, 1);

	printf("\nCALLING ITERATE\n");
	iterate(list, print);
	
	/* Add '2' to list */
	insert(&list, two, lastChar, 1);
	
	printf("\nCALLING ITERATE\n");
	iterate(list, print);
	
	/* Add '2' to list */
	insert(&list, three, lastChar, 1);

	printf("\nCALLING ITERATE\n");
	iterate(list,print);
	
	/* Testing what least returns on a list that is not empty */
	leastWhenListNotEmpty = least(list, getLeast);
	printf("\nLEAST: %.0f\n", leastWhenListNotEmpty);
	if(leastWhenListNotEmpty != leastWhenListNotEmpty) printf("list is empty\n");
	else printf("list is not empty\n");


	printf("\nCALLING ITERATE\n");
	iterate(list,print);
	
	/* Delete any term that is '2' */
	printf("\nCAllING DELETESOME\n");
	deleteSome(&list, delNumTwo, rid, 1);

	printf("\nCALLING ITERATE\n");
	iterate(list,print);

	return 0;
}
