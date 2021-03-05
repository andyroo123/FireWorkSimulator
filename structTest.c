/* Andrew Kolarits */
#include <stdio.h>

struct fw {
	double time, fuse, xPos, yPos, xVel, yVel;
	unsigned int hexValue;
} testFirework, *pointerToFirework;

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

int main()
{
	/* Asign date to members of struct */
	testFirework.time = 0.1;
	testFirework.fuse = 0.2;
	testFirework.xPos = 0.3;
	testFirework.yPos = 0.4;
	testFirework.xVel = 0.5;
	testFirework.yVel = 0.6;
	testFirework.hexValue = 123;

	pointerToFirework = &testFirework;

	pointerToFirework->time = 5.32;

	/* Print out struct */
	printf("DIRECT FIREWORK\n");
	printf("time: %.1f\n", testFirework.time); 
	printf("fuse: %.1f\n", testFirework.fuse);
	printf("xPos: %.1f\n", testFirework.xPos);
	printf("yPos: %.1f\n", testFirework.yPos);
	printf("xVel: %.1f\n", testFirework.xVel);
	printf("yVel: %.1f\n", testFirework.yVel);
	printf("hexValue: %d\n", testFirework.hexValue);
	
	printFirework(pointerToFirework);

	return 0;
}
