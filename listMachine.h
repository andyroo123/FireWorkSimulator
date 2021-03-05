/* Andrew Kolarits */

void checkForBoom(void *data);
void checkForFinalEffect(struct simulation *world);
double getLowestDt(void *listOfFireworks);
int hasItBoomed(void *data);
int isFuseGone(void *data);
int lowestCurrTime(void *fw1, void *fw2);
int lowestYPos(void *data1, void *data2);
void printFuse(void *data);
void printList(struct simulation *world);
void putIntoList(struct simulation *world, struct firework *fwPTR, int currSize);
void sortList(struct simulation *world);
void updateList(struct simulation *world);
