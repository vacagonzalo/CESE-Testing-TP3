#ifndef __LEDS_H__
#define __LEDS_H__

#include <stdint.h>

void leds_create(uint16_t *port);

void leds_turn_on(uint16_t*port, uint8_t led_number);

void leds_turn_off(uint16_t *port, uint8_t led_number);
#endif