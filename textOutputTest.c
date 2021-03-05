/* Andrew Kolarits */
#include <stdio.h>

/* Creates the struct, in the actual lab there will be an additional trait for a fireworks dt */
struct fw {
	double time, fuse, xPos, yPos, xVel, yVel;
	unsigned int hexValue;
};

/* Prints every aspect of a firework to the screen */
void printFirework(struct fw *firework)
{
	printf("\nPOINTER FIREWORK\n");
	printf("time: %.1f\n", firework->time);
	printf("fuse: %.1f\n", firework->fuse);
	printf("xPos: %.1f\n", firework->xPos);
	printf("yPos: %.1f\n", firework->yPos);
	printf("xVel: %.1f\n", firework->xVel);
	printf("yVel: %.1f\n", firework->yVel);
	printf("hexValue: %x\n", firework->hexValue);
}

/* Prints header lined up properly */
void printHeader()
{
	double time = 0; /* Used to simulate starting time to get format correct */
	printf("\n At ET =  %.3f (%.15f) second:\n", time);
	printf("    Code     (      X,       Y)'  (     VX,      VY) fps       Fuse sec\n");
}

/* Prints the half of the line required when the firework has taken off */
void printFWInAir(struct fw *firework)
{
	printf("( %6.2f,  %6.2f) fps with %1.3f sec\n", firework->xVel, firework->yVel, firework->fuse);
}

/* Prints the half of the line required when the firework ahs not taken off */
void printFWNotInAir(struct fw *firework)
{
	printf("Holding until %.3f\n", firework->time);
}

/* Prints the first half of line, decides what other half to print */
void printLineFW(struct fw *firework)
{
	double currTime = 0; /* Used to simulate starting time to get format correct */
	printf("%X at  ( %6.2f,  %6.2f)'  ", firework->hexValue, firework->xPos, firework->yPos);
	if(firework->time == currTime)
		printFWInAir(firework);
	else
		printFWNotInAir(firework);
}

/* scanf loop, uses size of 6 to know when to stop readin in data.
 * Returns a pointer to firework becuase I wanted to learn how it worked
 * if I needed it during the lab */
struct fw* readInput(struct fw firework)
{
	struct fw *fwCopy = &firework;
	int properSize;
	while((properSize = scanf("%lf %x %lf %lf %lf %lf", &firework.time, &firework.hexValue, &firework.fuse, &firework.xPos, &firework.xVel, &firework.yVel)) == 6)
	{
		firework.yPos = 0.0;
		printLineFW(fwCopy);
	}
	return fwCopy;
}

int main()
{
	struct fw firework; /* Creates a firework struct */
	struct fw *testFirework; /* Creates a pointer to a firework struct */

	printHeader();
	testFirework = readInput(firework);
	/*printFirework(&(*testFirework)); Prints the last firework read */

	return 0;
}
