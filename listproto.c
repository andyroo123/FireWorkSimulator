
/* Copyright 2021 Neil Kirby - not for disclosure. */
/*  Example prototypes using strings and the list code */
/* you may NOT turn these in.  They do show using the list */

#include <stdio.h>

#include "linkedlist.h"

/* a criteria function */
int always_true(void *data)
{
	/* no actual determination, always return true */
	/* a real criteria would assign data to a real pointer type and then
	 * do something with that to say yes or no */
	return(1==1);
}


/* a comparison function that compares the first character of two strings */
int firstchar(void *data1, void *data2)
{
	char *s1 = data1, *s2 = data2;

	return( *s1 < *s2);
}

/* an action function to print a string */
void printIt(void *data)
{
	char *s1 = data;

	printf ("String is: %s\n", s1);
}

int main()
{

	void *list = NULL; /* MUST set it to NULL to begin with! */

	/* test insert */
	insert(&list, "Go Bucks!", firstchar, 1);
	/* now test iterate */
	printf("Calling iterate\n");
	iterate(list, printIt);
	    /* the code to here is a good prototype that tests insert and iterate */

	/* test insert again - this will test the comparison as well */
	insert(&list, "ZZZ", firstchar, 1);
	/* now test iterate */
	printf("Calling iterate\n");
	iterate(list, printIt);

	/* test insert again - this will test the comparison as well */
	insert(&list, "AAA", firstchar, 1);
	/* now test iterate */
	printf("Calling iterate\n");
	iterate(list, printIt);
	    /* the code to here is a good prototype that proves comparison is correct */

	    /* I could write a different comparison function and use it to call sort (then iterate) to 
	     * show how sort works */

	/* now test deleteSome */
	printf("Deleting entire list\n");
	/* for "disposal" I print the string since I didn't use malloc to allocate it */
	deleteSome(&list, always_true, printIt, 1);
	/* prove the list is empty */
	printf("Calling iterate\n");
	iterate(list, printIt);
	printf("Done!\n");
		/* code to here is a final prototype proving that delete works */

	return 0;
}

	
