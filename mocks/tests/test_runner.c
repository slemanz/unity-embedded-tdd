#include "unity.h"

void test_init_drives_the_led_pin_low(void);
void test_turn_on_writes_high_to_the_led_pin(void);
void test_turn_off_writes_low_to_the_led_pin(void);
void test_toggle_from_low_reads_then_writes_high(void);
void test_toggle_from_high_reads_then_writes_low(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_drives_the_led_pin_low, __LINE__);
    RUN_TEST(test_turn_on_writes_high_to_the_led_pin, __LINE__);
    RUN_TEST(test_turn_off_writes_low_to_the_led_pin, __LINE__);
    RUN_TEST(test_toggle_from_low_reads_then_writes_high, __LINE__);
    RUN_TEST(test_toggle_from_high_reads_then_writes_low, __LINE__);

    return UNITY_END();
}
