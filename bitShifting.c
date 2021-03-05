/* Andrew Kolarits */

/* Macros of bits for data that could be needed */
#define STAR_BITS 8
#define FLASH_BITS 6
#define BOOM_BITS 2
#define COLOR_BITS 15
#define DAY_BITS 255
#define MONTH_BITS 15
#define YEAR_BITS 4095

/* Macros of shift for data that could be needed */
#define EFFECT_SHIFT 28
#define COLOR_SHIFT 24
#define DAY_SHIFT 16
#define MONTH_SHIFT 12
#define YEAR_SHIFT 0

/* Given a SHIFT and BIT value, along with the hexValue code,
 * will return the data coresponding the the given shift and bits */
int convertHexValue(const int SHIFT, const int BITS, unsigned int CODE)
{
	return CODE>>SHIFT&BITS;
}
