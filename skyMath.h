/* Andrew Kolarits */

double getDt(void *data);
double getEffectiveDt(void *data);
void updateET(struct simulation *world);
void updateFirework(void *data);
void updateFuse(struct firework *fw, double effectiveDt);
void updateXPos(struct firework *fw, double effectiveDt);
void updateYPos(struct firework *fw, double effectiveDt);
void updateYVel(struct firework *fw, double effectiveDt);
