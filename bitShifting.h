/* Andrew Kolarits */

#define STAR_BITS 8
#define FLASH_BITS 4
#define BOOM_BITS 2
#define COLOR_BITS 15
#define DAY_BITS 255
#define MONTH_BITS 15
#define YEAR_BITS 4095

#define EFFECT_SHIFT 28
#define COLOR_SHIFT 24
#define DAY_SHIFT 16
#define MONTH_SHIFT 12
#define YEAR_SHIFT 0

int convertHexValue(const int SHIFT, const int BITS, unsigned int CODE);
