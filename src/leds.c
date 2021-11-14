#include "leds.h"

#define ALL_LEDS_OFF 0x0000

void leds_create(uint16_t *port)
{
    *port = ALL_LEDS_OFF;
}