/* Andrew Kolarits */
#include <stdio.h>

/* BIT MACROS */
#define STAR_BITS 8
#define FLASH_BITS 6
#define BOOM_BITS 2
#define DAY_BITS 255
#define MONTH_BITS 15
#define YEAR_BITS 4095

/* SHIFT MACROS */
#define EFFECT_SHIFT 28
#define COLOR_SHIFT 24
#define DAY_SHIFT 16
#define MONTH_SHIFT 12
#define YEAR_SHIFT 0

/* NOTE: I did not figure out masking/shifting for lab2 so this is me ptrototyping that now */

/* Struct for resembling a firework */
struct fw {
	double time, fuse, xPos, yPos, xVel, yVel;
	unsigned int hexValue;
};

/* Prints all aspects of a firework give a pointer to a fireworks */
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

/* Different way to read input, returning a struct. Incase it would be better in the labe. 'it was not' */
struct fw readInput()
{
	int properSize;
	struct fw firework;
	while((properSize = scanf("%lf %x %lf %lf %lf %lf", &firework.time, &firework.hexValue, &firework.fuse, &firework.xPos, &firework.xVel, &firework.yVel)) == 6)
	{
		firework.yPos = 0.0;	
	}
	printf("%X\n", firework.hexValue);
	return firework;
}

/* Given the coressponding shift, bits and hexValue will return the actual value from it */
int bits(const unsigned int SHIFT, const unsigned int BITS, const unsigned int CODE)
{
	return CODE>>SHIFT&BITS;
}

int main()
{
	struct fw firework; /* Create struct firework to read in data */

	int month, color, day, year, star, flash, boom; /* All data that can be read from hexValue */

	firework = readInput();	/* Get input from file */
	
	/* Convert hexValue into all the information */
	color = bits(COLOR_SHIFT, MONTH_BITS, firework.hexValue);
	day = bits(DAY_SHIFT, DAY_BITS, firework.hexValue);
	month = bits(MONTH_SHIFT, MONTH_BITS, firework.hexValue);
	year = bits(YEAR_SHIFT, YEAR_BITS, firework.hexValue);
	star = bits(EFFECT_SHIFT, STAR_BITS, firework.hexValue);
	flash = bits(EFFECT_SHIFT, FLASH_BITS, firework.hexValue);
	boom = bits(EFFECT_SHIFT, BOOM_BITS, firework.hexValue);
	
	/* Print the newly obtained information */
	printf("COLOR: %d\n", color);
	printf("DAY: %d\n", day);
	printf("MONTH: %d\n", month);
	printf("YEAR: %d\n", year);
	printf("EFFECTS KNOW BY NON-ZERO TRUE\n");
	printf("STAR: %d\n", star);
	printf("FLASH: %d\n", flash);
	printf("BOOM: %d\n", boom);

	return 0;
}
