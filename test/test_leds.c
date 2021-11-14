#include "unity.h"
#include "leds.h"

#define ALL_LEDS_ON 0xFFFF
#define ALL_LEDS_OFF 0x0000
#define NUMBER_OF_LEDS 16
#define OFFSET_INDEX 1
#define LED_BIT(X) (1 << (X - 1))

static uint16_t virtual_port;

void setUp()
{
    leds_create(&virtual_port);
}

void tearDown() {}

void test_system_starts_with_all_leds_off(void)
{
    virtual_port = ALL_LEDS_ON;
    leds_create(&virtual_port);
    TEST_ASSERT_EQUAL_HEX16(ALL_LEDS_OFF, virtual_port);
}

void test_turn_on_one_led(void)
{
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
    for (uint16_t test_case = OFFSET_INDEX;
         test_case < NUMBER_OF_LEDS + OFFSET_INDEX;
         ++test_case)
    {
        leds_create(&virtual_port);
        virtual_port = ALL_LEDS_ON;
        leds_turn_off(&virtual_port, test_case);
        TEST_ASSERT_EQUAL_HEX16(~LED_BIT(test_case), virtual_port);
    }
}

void test_turn_on_and_off_one_led(void)
{
    for (uint16_t test_case = OFFSET_INDEX;
         test_case < NUMBER_OF_LEDS + OFFSET_INDEX;
         ++test_case)
    {
        leds_create(&virtual_port);
        leds_turn_on(&virtual_port, test_case);
        leds_turn_off(&virtual_port, test_case);
        TEST_ASSERT_EQUAL_HEX16(ALL_LEDS_OFF, virtual_port);
    }
}

void test_turn_off_all_leds(void)
{
    uint16_t test_case = 1;
    while (test_case++)
    {
        virtual_port = test_case;
        leds_turn_all_off(&virtual_port);
        TEST_ASSERT_EQUAL_HEX16(ALL_LEDS_OFF, virtual_port);
    }
}

void test_read_off_led_state(void)
{
    for (uint16_t test_case = OFFSET_INDEX;
         test_case < NUMBER_OF_LEDS + OFFSET_INDEX;
         ++test_case)
    {
        virtual_port = ALL_LEDS_ON;
        leds_turn_off(&virtual_port, test_case);
        bool led_state = leds_read_led_state(&virtual_port, test_case);
        TEST_ASSERT_EQUAL_HEX16(LED_OFF, led_state);
    }
}

void test_read_on_led_state(void)
{
    for (uint16_t test_case = OFFSET_INDEX;
         test_case < NUMBER_OF_LEDS + OFFSET_INDEX;
         ++test_case)
    {
        virtual_port = ALL_LEDS_OFF;
        leds_turn_on(&virtual_port, test_case);
        bool led_state = leds_read_led_state(&virtual_port, test_case);
        TEST_ASSERT_EQUAL_HEX16(LED_ON, led_state);
    }
}

// note: the test "verify parameters' limits" is embedded in each previous test

// INVALID CASES

void test_turn_on_invalid_led(void)
{
    uint8_t test_cases[] = {0, 17, 255};
    uint32_t size = sizeof(test_cases[0]) / sizeof(test_cases);
    for (uint32_t i = 0; i < size; ++i)
    {
        leds_turn_on(&virtual_port, test_cases[i]);
        TEST_ASSERT_EQUAL_HEX16(ALL_LEDS_OFF, virtual_port);
    }
}

void test_turn_off_invalid_led(void)
{
    uint8_t test_cases[] = {0, 17, 255};
    uint32_t size = sizeof(test_cases[0]) / sizeof(test_cases);
    virtual_port = ALL_LEDS_ON;
    for (uint32_t i = 0; i < size; ++i)
    {
        leds_turn_off(&virtual_port, test_cases[i]);
        TEST_ASSERT_EQUAL_HEX16(ALL_LEDS_ON, virtual_port);
    }
}

void test_read_invalid_led(void)
{
    uint8_t test_cases[] = {0, 17, 255};
    uint32_t size = sizeof(test_cases[0]) / sizeof(test_cases);
    virtual_port = ALL_LEDS_ON;
    for (uint32_t i = 0; i < size; ++i)
    {
        bool status = leds_read_led_state(&virtual_port, test_cases[i]);
        TEST_ASSERT_EQUAL_HEX16(LED_OFF, status);
    }
}