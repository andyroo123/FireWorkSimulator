/* Andrew Kolarits */

#include <stdio.h>
#include "debug.h"
#include "libfire.h"
#include "structures.h"
#include "output.h"
#include "listMachine.h"

/* Macro for GRAVITY constant */
#define GRAVITY -32.17405

/* Adds the current dt to the ET */
void updateET(struct simulation *world)
{
	world->ET += world->dt;
}

/* Calculates the basic dt for a firework */
/* THIS IS BASIC DT */
double getDt(void *data)
{
	struct firework *fw = data;
	double oneQuarter = 0.25;
	return oneQuarter * fw_get_delta_Y() / fw->yVel;
}

/* Calculates the effective given the edge cases discussed in the lab write up */
double getEffectiveDt(void *data)
{
	struct firework *fw = data;
	struct simulation *world = fw->p2World;
	double currDt = world->dt, newDt = currDt, currET = world->ET;	
	int debugID = 0;
	if(currET < fw->currTime) newDt = 0;
	else if(currET > fw->currTime + currDt) newDt = currDt, debugID = 1;
	else newDt = currET - fw->currTime, debugID = 2;
	if(newDt > 0 && newDt > fw->fuse) newDt = fw->fuse, debugID = 3;
	if(VERBOSE && !GRAPHICS) printDebugDT(fw, newDt, debugID);
	return newDt;
}

/* Updates the fuse for a firework given the effective dt for that frame */
void updateFuse(struct firework *fw, double effectiveDt)
{
	struct simulation *world = fw->p2World;
	if(fw->fuse - effectiveDt > 0) /* Does let fuse go below 0 */
		fw->fuse -= effectiveDt;
	else  	 
		fw->boomMsg++;
}

/* Updates the xPos of a firework given the effective dt for that fram */
void updateXPos(struct firework *fw, double effectiveDt)
{
	struct simulation *world = fw->p2World;
	fw->xPos += fw->xVel * effectiveDt;
}

/* Updates the yPos of a firework given the effective dt for that fram */
void updateYPos(struct firework *fw, double effectiveDt)
{
	struct simulation *world = fw->p2World;
	fw->yPos = fw->yPos +  fw->yVel * effectiveDt + 0.5 * GRAVITY * effectiveDt * effectiveDt;
	if(fw->yPos < 0) /* if yPos < 0 print coressponding msg */
	{
		if(TEXT) printFWHitGoundMsg(fw), fw->boomMsg++;
		fw->yPos = 0;
	}
}

/* Updates the yVel of a firework given the effective dt for that fram */
void updateYVel(struct firework *fw, double effectiveDt)
{
	struct simulation *world = fw->p2World;
	fw->yVel += GRAVITY * effectiveDt;
	/* Checks to see if warning msgs need to be dispayed */
	if(TEXT && fw->yVel < 0 && !fw->warningMsg)
		printFwFallingWarning(fw), fw->warningMsg++;
	else if(GRAPHICS && fw->yVel < 0 && !fw->warningMsg)
		graphicFwFallingWarning(), fw->warningMsg++;
}

/* Master function that updates a firework from the give void *data */
void updateFirework(void *data)
{
	struct firework *fw = data;
	struct simulation *world = fw->p2World;
	double basicDt = world->dt, effectiveDt = basicDt;
	effectiveDt = getEffectiveDt(fw);
	if(fw->currTime < world->ET && !(fw->warningMsg && fw->yPos < 0))
	{
		updateFuse(fw, effectiveDt);
		updateXPos(fw, effectiveDt);
		updateYPos(fw, effectiveDt);
		updateYVel(fw, effectiveDt);
		fw->currTime+=effectiveDt;
	}
}
