/* Andrew Kolarits */
#include <stdio.h>
#include "debug.h"
#include "libfire.h"
#include "structures.h"
#include "bitShifting.h"

/* Prints elapsed time in proper format */
void printElapsedTime(double time)
{
	printf("Total runtime is %.9f seconds.\n", time);
}

/* Prints final size of input in proper format */
void printFinalSize(int size)
{
	if(TEXT) printf("\n");
	printf("Done reading: scanf returned %d\n", size);
}

/* Prints fw_status message for when a fireworks yVel is negative */
void graphicFwFallingWarning()
{
        fw_status("RANGE SAFETY: Freefall!\n");
}

/* Prints fw_status message for when a firework hits the ground */
void graphicFWImpactMSG()
{
        fw_status("RAMGE SAFETY: Impact!\n");
}

/* Updates to graphical output for the exit of the simulation */
void runExitLoop(struct simulation *world)
{
	double thousand = 1000 /* conversion factor for millisleep */, fadeTime = 2 /*Exit loop last 2 seconds */, time = now();
	while(now() - time < fadeTime)
	{
		fw_clear();
		fw_refresh();
		millisleep(world->dt * thousand);
	}
}

/* Give a firework from void *data prints the position to the graphical screen */
void printGraphicFW(void *data)
{
        struct firework *fw = data;
	struct simulation *world = fw->p2World;
	int color = convertHexValue(COLOR_SHIFT, COLOR_BITS, fw->hexValue);;
	if(fw->yPos > 0) fw_dot(color, fw->xPos, fw->yPos); /* Checks if yPos 0 negative, can not plot if it is */
	else if(fw->warningMsg) graphicFWImpactMSG(), fw->boomMsg++; /* Checks if needs the print impact msg */
}

/* Prints the end graphics for a given firework */
void printBoomGraphics(struct firework *fw)
{
	if(convertHexValue(EFFECT_SHIFT, STAR_BITS, fw->hexValue))
		fw_star(convertHexValue(COLOR_SHIFT, COLOR_BITS, fw->hexValue), fw->xPos, fw->yPos);
	if(convertHexValue(EFFECT_SHIFT, FLASH_BITS, fw->hexValue))
		fw_flash(); /* This is the line that causes the sreen tearing, I do not know why */
	if(convertHexValue(EFFECT_SHIFT, BOOM_BITS, fw->hexValue))
		fw_bang();
}

/* Prints the header for each iteration of the simulation loop when in TEXT mode */
void printHeader(struct simulation *world)
{
	printf("\n\n At ET =  %.3f (%.15f) second:\n", world->ET, world->ET);
	printf("    Code     (      X,       Y)'  (     VX,      VY) fps       Fuse sec\n");
}

/* Prints the second half of the firework data line if the firwork is in the air */
void printFWInAir(struct firework *fw)
{
	printf("(%7.2f, %7.2f) fps with %1.3f sec\n", fw->xVel, fw->yVel, fw->fuse);
}

/* Prints the second half of the firework data line if the firwork is not in the air */
void printFWNotInAir(struct firework *fw)
{
	printf("Holding until %.3f\n", fw->currTime);
}

/* Prints the first half of the firework data line, determines what other half should be printed */
void printLineFW(void *data)
{
	struct firework *fw = data;
	struct simulation *world = fw->p2World;	
	printf("%X at  (%7.2f, %7.2f)'  ", fw->hexValue, fw->xPos, fw->yPos);
	if(fw->currTime <= world->ET)
		printFWInAir(fw);
	else
		printFWNotInAir(fw);
}

/* Prints the ERRROR message when a firework yVel becomes negative, for when the simulation is in TEXT mode */
void printFwFallingWarning(struct firework *fw)
{
	printf("RANGE SAFETY WARNING: %X is falling at %.1f' alt'",fw->hexValue, fw->yPos);
	printf(" and %.1f' downrange with %.3fs till detonation.\n", fw->xPos, fw->fuse);
}

/* Prints the ERRROR message when a firework hits the ground, for when the simulation is in TEXT mode */
void printFWHitGoundMsg(struct firework *fw)
{
	struct simulation *world = fw->p2World;
	int day = convertHexValue(DAY_SHIFT, DAY_BITS, fw->hexValue);
	int month = convertHexValue(MONTH_SHIFT, MONTH_BITS, fw->hexValue);
	int year = convertHexValue(YEAR_SHIFT, YEAR_BITS, fw->hexValue);
	printf("RANGE SAFETY WARNING: At %.3f sec %X (made on %d-%d-%d)", world->ET, fw->hexValue, day, month , year);
	printf("impacts at (%.2f, %.2f)' with %.3f seconds reamaining\n", fw->xPos, fw->yPos, fw->fuse);
}

/* Prints the corresponding boom message for a give firework when simulation is in TEXT mode */
void printBoomMsg(struct firework *fw)
{
	int color = convertHexValue(COLOR_SHIFT, COLOR_BITS, fw->hexValue);
	printf("Color #%1d", color, fw->xPos, fw->yPos);
	if(convertHexValue(EFFECT_SHIFT, STAR_BITS, fw->hexValue))
		printf(" starburst at (%6.2f, %6.2f)'\n", fw->xPos, fw->yPos);
	else
		printf("\n");
	if(convertHexValue(EFFECT_SHIFT, FLASH_BITS, fw->hexValue))
		printf("Flash at (%6.2f, %6.2f)'\n", fw->xPos, fw->yPos);
	if(convertHexValue(EFFECT_SHIFT, BOOM_BITS, fw->hexValue))
		printf("Boom at (%6.2f, %6.2f)'\n", fw->xPos, fw->yPos);
}

/* Prints error message if allocation fails */
void printErrorAllocatingMemMsg()
{
	printf("ERROR: dynamicMemory.c: allocateFirework: malloc failed");
}

/* Prints the allocating memory message */
void printAllocationMemMsg(unsigned int hexValue, int currSizeOfList)
{
	printf("DIAGNOSTIC: Allocating space for code %X.  %d allocated.\n", hexValue, currSizeOfList);
}

/* Prints the unallocating memory message */
void printFreeingMemMsg(struct firework *fw)
{
	struct simulation *world = fw->p2World;
	printf("DIAGNOSTIC: Freeing firework with code %X. %d freed.\n", fw->hexValue, ++world->size);
}

/* Prints error message if inserting a firework into the list fails */
void printErrorInsertMsg(struct firework *fw)
{
	printf("ERROR: listMachine.c: putIntoList: failed inserting firework with code: %X", fw->hexValue);
}

/* Given the debug ID prints out the coresponding debug msg for a firework */
void printDebugDT(struct firework *fw, double ET, int debugID)
{
	struct simulation *world = fw->p2World;
	double rval = world->ET - fw->currTime;
	if(debugID == 0) printf("getEffectiveDt: %X HOLD ET=%.4f, L=%.4f, F=%.4f dt=%.6f. rval= 0.0000\n", fw->hexValue, world->ET, fw->currTime, fw->fuse, world->dt);
	else if(debugID == 1) printf("getEffectiveDt: %X IN AIR ET=%.4f, L=0.0000, F=%.4f dt=%.6f. rval=%.4f\n", fw->hexValue, world->ET, fw->fuse, world->dt, rval);
	else if(debugID == 2) printf("getEffectiveDt: %X LAUNCH ET=%.4f, L=0.0000, F=%.4f dt=%.6f. rval=%.4f\n", fw->hexValue, world->ET, fw->fuse, world->dt, rval);
	else printf("getEffectiveDt: %X IN AIR ET=%.4f, L=0.0000, F=%.4f dt=%.6f. rval=%.4f\ngetEffectiveDt: %X  - clipping to fuse time.\n", fw->hexValue, world->ET, fw->fuse, world->dt, rval, fw->hexValue);
}

