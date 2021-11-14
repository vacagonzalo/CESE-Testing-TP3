#include "unity.h"
#include "leds.h"

void test_system_starts_with_all_leds_off(void)
{
    uint16_t virtualPort = 0xFFFF;
    leds_create(&virtualPort);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualPort);
}