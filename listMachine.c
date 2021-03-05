/* Andrew Kolarits */

#include <stdio.h>
#include "debug.h"
#include "libfire.h"
#include "structures.h"
#include "linkedlist.h"
#include "output.h"
#include "skyMath.h"
#include "bitShifting.h"
#include "dynamicMemory.h"

/* Decides if the loop should be graphically or textually printed, iterates through list */
void printList(struct simulation *world)
{
	if(TEXT) iterate(world->listOfFireworks, printLineFW);
	else
	{
		fw_clear();
		iterate(world->listOfFireworks, printGraphicFW);	
		fw_refresh();
		millisleep(world->dt * 1000);
	}
}

/* Comparison function that returns the lowest currTime of all the fireworks in the list */
int lowestCurrTime(void *fw1, void *fw2)
{
	struct firework *f1 = fw1, *f2 = fw2;	
	return f1->currTime < f2->currTime;
}

/* Comparison function that returns the lowest yPos of all the fireworks in the list */
int lowestYPos(void *data1, void *data2)
{
	struct firework *fw1 = data1, *fw2 = data2;
	return fw1->yPos > fw2->yPos;
}

/* Returns the lowest dt of all the fireworks in the list */
double getLowestDt(void *listOfFireworks)
{
	return least(listOfFireworks, getDt);
}

/* Sorts the list by the increasing yPos value of the fireworks */
void sortList(struct simulation *world)
{
	sort(world->listOfFireworks, lowestYPos);	
}

/* Iterates through list to call the updateFirework function */
void updateList(struct simulation *world)
{
	
	updateET(world);
	iterate(world->listOfFireworks, updateFirework);
}

/* Puts fwPTR into the linked list in world, prints fail message if needed */
void putIntoList(struct simulation *world, struct firework *fwPTR, int currSize)
{
	if(!insert(&world->listOfFireworks, fwPTR, lowestCurrTime, TEXT)){
		printErrorInsertMsg(fwPTR);
	}
}

/* Action fuction that checks if a fire work needs to print a boom msg, and calls function to print it
 * accordingly */
void checkForBoom(void *data)
{
	struct firework *fw = data;
	if(fw->boomMsg && fw->yPos >= 0) {
		if(TEXT && fw->yPos > 0) printBoomMsg(fw);
		else if(GRAPHICS && (!fw->warningMsg || fw->warningMsg && fw->yPos > 0))printBoomGraphics(fw);
	}
}

/* Criteria function that decides if a firework has printed a boom message yet */
int hasItBoomed(void *data)
{
	struct firework *fw = data;
	if(fw->boomMsg || fw->yPos < 0) return 1;
	return 0;
	
}

/* Iterates through list seeing if any fireworks fuses's have run out, deletes any if they have */
void checkForFinalEffect(struct simulation *world)
{
	void *list = world->listOfFireworks;
	iterate(world->listOfFireworks, checkForBoom);
	deleteSome(&world->listOfFireworks, hasItBoomed, unallocateFirework, TEXT);
}

