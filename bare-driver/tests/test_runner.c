#include "unity.h"

void test_led_init_enables_gpioa_and_configures_pa5_output_start_off(void);
void test_led_on_sets_bsrr_set_bit_only(void);
void test_led_off_sets_bsrr_reset_bit_only(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_led_init_enables_gpioa_and_configures_pa5_output_start_off, __LINE__);
    RUN_TEST(test_led_on_sets_bsrr_set_bit_only, __LINE__);
    RUN_TEST(test_led_off_sets_bsrr_reset_bit_only, __LINE__);

    return UNITY_END();
}