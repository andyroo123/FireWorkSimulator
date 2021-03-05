/* Andrew Kolarits */

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "structures.h"
#include "output.h"

/* Unallocate fireowrk from memory by using free() command,
 * prints free message if in TEXT mode*/
void unallocateFirework(void *data)
{
	struct firework *fw = data;
	struct simulation *world = fw->p2World;
	if(!GRAPHICS) printFreeingMemMsg(fw);
	free(fw);		
}

/* Allocates memory for a given firework by using malloc(),
 * if malloc succeeds/fails a corresponding message is printed if in TEXT mode */
struct firework* newAllocateData(void *data, unsigned int hexValue, int currSizeOfList)
{
	struct firework *mallocFW, *fwPTR = data;
	mallocFW  = malloc(sizeof(struct firework));
	if(fwPTR == NULL) {
		if(TEXT) printErrorAllocatingMemMsg();
	}
	else {
		if(TEXT) printAllocationMemMsg(hexValue, ++currSizeOfList);
	}
	return mallocFW;
}

