/* Andrew Kolarits */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "debug.h"
#include "libfire.h"
#include "dynamicMemory.h"
#include "listMachine.h"
#include "output.h"

#include "linkedlist.h"
#include "skyMath.h"

/* Runs the simulation loop */
void simLoop(struct simulation *world)
{
	double isListEmpty = getLowestDt(world->listOfFireworks);
	world->dt = getLowestDt(world->listOfFireworks);
	while(!(isListEmpty != isListEmpty))
	{
		if(TEXT)printHeader(world);
		sortList(world);
		printList(world);
		updateList(world);
		checkForFinalEffect(world);
		isListEmpty = getLowestDt(world->listOfFireworks);
	}
	if(GRAPHICS) runExitLoop(world);
}

/* Runs the read in data loop */
int readLoop(struct simulation *world)
{
	int properSize, currSizeOfList = 0;
	struct firework fw1, *fwPTR = &fw1;
	fw1.warningMsg = 0, fw1.boomMsg = 0, fw1.yPos = 0;
	while((properSize = scanf("%lf %x %lf %lf %lf %lf", &fw1.currTime, &fw1.hexValue, &fw1.fuse, &fw1.xPos, &fw1.xVel, &fw1.yVel)) == 6)
	{
		fw1.p2World = world;
		fwPTR = newAllocateData(&fwPTR, fw1.hexValue, currSizeOfList);	
		*fwPTR = fw1;
		putIntoList(world, fwPTR, currSizeOfList);
		currSizeOfList++;
	}
	return properSize;
}

/* Makes high level decisions that can not fit in main */
int dataSequence()
{
	struct simulation world = {0, 0, 0, NULL};
	int finalSize = readLoop(&world);
	simLoop(&world);	
	return finalSize;
}

/* Simulates fireworks from a linked list data structure */
int main()
{
	int finalInputSize;
	double startTime = now();
	if(TEXT || (GRAPHICS && fw_initialize()))
	finalInputSize = dataSequence();
	if(GRAPHICS)fw_teardown();
	printFinalSize(finalInputSize);
	printElapsedTime(now() - startTime);
	return 0;
}
