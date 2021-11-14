#include "leds.h"

#define ALL_LEDS_OFF 0x0000
#define OFFSET_INDEX 1
#define LAST_LED_INDEX 16
#define POSITION 1
#define LED_BIT(X) (POSITION << (X - OFFSET_INDEX))
#define TO_BOOLEAN_MASK 1

void leds_create(uint16_t *port)
{
    *port = ALL_LEDS_OFF;
}

void leds_turn_on(uint16_t *port, uint8_t led_number)
{
    *port |= LED_BIT(led_number);
}

void leds_turn_off(uint16_t *port, uint8_t led_number)
{
    *port &= ~(LED_BIT(led_number));
}

void leds_turn_all_off(uint16_t *port)
{
    leds_create(port);
}

bool leds_read_led_state(uint16_t *port, uint8_t led_number)
{
    if (led_number < OFFSET_INDEX || led_number > LAST_LED_INDEX)
    {
        return LED_OFF;
    }
    else
    {
        return (*port >> (led_number - OFFSET_INDEX)) & TO_BOOLEAN_MASK;
    }
}