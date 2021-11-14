#include "unity.h"
#include "leds.h"

#define NUMBER_OF_LEDS 16
#define OFFSET_INDEX 1
#define LED_BIT(X) (1 << (X - 1))

void setUp() {}
void tearDown() {}

void test_system_starts_with_all_leds_off(void)
{
    uint16_t virtual_port = 0xFFFF;
    leds_create(&virtual_port);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtual_port);
}

void test_turn_on_one_led(void)
{
    uint16_t virtual_port;
    for (uint16_t test_case = OFFSET_INDEX;
         test_case < NUMBER_OF_LEDS + OFFSET_INDEX;
         ++test_case)
    {
        leds_create(&virtual_port);
        leds_turn_on(&virtual_port, test_case);
        TEST_ASSERT_EQUAL_HEX16(LED_BIT(test_case), virtual_port);
    }
}

void test_turn_off_one_led(void)
{
    uint16_t virtual_port;
    for (uint16_t test_case = OFFSET_INDEX;
         test_case < NUMBER_OF_LEDS + OFFSET_INDEX;
         ++test_case)
    {
        leds_create(&virtual_port);
        virtual_port = 0xFFFF;
        leds_turn_off(&virtual_port, test_case);
        TEST_ASSERT_EQUAL_HEX16(~LED_BIT(test_case), virtual_port);
    }
}

void test_turn_on_and_off_one_led(void)
{
    uint16_t virtual_port;
    for (uint16_t test_case = OFFSET_INDEX;
         test_case < NUMBER_OF_LEDS + OFFSET_INDEX;
         ++test_case)
    {
        leds_create(&virtual_port);
        leds_turn_on(&virtual_port, test_case);
        leds_turn_off(&virtual_port, test_case);
        TEST_ASSERT_EQUAL_HEX16(0x0000, virtual_port);
    }
}