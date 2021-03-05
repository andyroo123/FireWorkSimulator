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

/* scanf loop, uses size of 6 to know when to stop readin in data.
 *  * Returns a pointer to firework becuase I wanted to learn how it worked
 *   * if I needed it during the lab */
struct fw* readInput(struct fw firework)
{
        struct fw *fwCopy = &firework;
        int properSize;
        while((properSize = scanf("%lf %x %lf %lf %lf %lf", &firework.time, &firework.hexValue, &firework.fuse, &firework.xPos, &firework.xVel, &firework.yVel)) == 6)
        {
                firework.yPos = 0.0;
                printFirework(&firework);
        }
        return fwCopy;
}

int main()
{
        struct fw firework; /* Creates a firework struct */
	struct fw *testFirework; /* Creates a pointer to a firework struct */

	testFirework = readInput(firework);

	printFirework(&(*testFirework));/* Prints the last firework read */

	return 0;
}

