#include "leds.h"

#define ALL_LEDS_OFF 0x0000

void leds_create(uint16_t *port)
{
    *port = ALL_LEDS_OFF;
}

void leds_turn_on(uint16_t *port, uint8_t led_number)
{
    *port |= 1 << (led_number - 1);
}

void leds_turn_off(uint16_t *port, uint8_t led_number)
{
    *port &= ~(1 << (led_number -1));
}

void leds_turn_all_off(uint16_t *port)
{
    leds_create(port);
}