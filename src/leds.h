#ifndef __LEDS_H__
#define __LEDS_H__

#include <stdint.h>
#include <stdbool.h>

#define LED_ON  1
#define LED_OFF 0

void leds_create(uint16_t *port);

void leds_turn_on(uint16_t*port, uint8_t led_number);

void leds_turn_off(uint16_t *port, uint8_t led_number);

void leds_turn_all_off(uint16_t *port);

bool leds_read_led_state(uint16_t *port, uint8_t led_number);

#endif