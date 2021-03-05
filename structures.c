/* Andrew Kolarits */

/* This file containes the structures that are used throughout the labe */

/* struct firework: resembles a firework in the simulation.
 * 	currTime: the currTime of the simulation or the launctime, once launctime is elapsed by
 * 		ET of simulation, currTime becomes ET of simulation.
 * 	fuse: the remaining fuse time of the firework.
 * 	xPos: the current xPos of the firework.
 * 	yPos: the current yPos of the firework.
 * 	xVel: the current xVel of the firework.
 * 	yVel: the current yVel of the firework.
 * 	hexValue: the hexValue of the firework.
 * 	warningMsg: acts as boolean value to see if warning message has been displayed for the firework.
 * 	boomMsg: acts as boolean value to see if boom  message has been displayed for the firework.
 *	*p2World: points the the struct simulation that the firework is in
 */
struct firework {
	double currTime, fuse, xPos, yPos, xVel, yVel;
	int warningMsg, boomMsg;
	unsigned int hexValue;	
	struct simulation *p2World;
};

/* struct simulation: resembles the world that the simulation is running in
 *	ET: the elapsed time of the simulation at any given moment.
 *	dt: to change in time for each frame, changes throughout simulation.
 *	*listOfFireworks: linked list of all fireworks being simulated.
 */
struct simulation {
	double ET, dt;
	void *listOfFireworks;
};

