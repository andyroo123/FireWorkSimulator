/* Andrew Kolarits */

void graphicFWImpactMSG();
void graphicFwFallingWarning();
void printAllocationMemMsg(unsigned int hexValue, int currSizeOfList);
void printBoomGraphics(struct firework *fw);
void printBoomMsg(struct firework *fw);
void printDebugDT(struct firework *fw, double ET, int debugID);
void printElapsedTime(double time);
void printErrorAllocatingMemMsg();
void printErrorInsertMsg(struct firework *fw);
void printFWHitGoundMsg(struct firework *fw);
void printFWInAir(struct firework *fw);
void printFWNotInAir(struct firework *fw);
void printFinalSize(int size);
void printFreeingMemMsg(struct firework *fw);
void printFwFallingWarning(struct firework *fw);
void printGraphicFW(void *data);
void printHeader(struct simulation *world);
void printLineFW(void *data);
void runExitLoop(struct simulation *world);
