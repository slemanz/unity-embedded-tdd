#include "unity.h"

void test_led_init_enables_gpioa_and_configures_pa5_output_start_off(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_led_init_enables_gpioa_and_configures_pa5_output_start_off, __LINE__);

    return UNITY_END();
}