#include "unity_fixture.h"
#include "gpio_reg.h"

TEST_GROUP(GpioReg);

TEST_SETUP(GpioReg)
{
}

TEST_TEAR_DOWN(GpioReg)
{
}

TEST(GpioReg, CountsSetPinsAsAnInteger)
{
    /* TEST_ASSERT_EQUAL is the alias for the platform int width. */
    TEST_ASSERT_EQUAL(3, GpioReg_CountSetPins(0x0Eu));
    TEST_ASSERT_EQUAL_UINT8(0, GpioReg_CountSetPins(0x00u));
    TEST_ASSERT_NOT_EQUAL(1, GpioReg_CountSetPins(0x0Eu));
}

TEST(GpioReg, SettingAPinProducesTheExpectedRegister)
{
    /* HEX variants print the failure in hex, lined up with the datasheet. */
    TEST_ASSERT_EQUAL_HEX32(0x00000001u, GpioReg_SetPin(0x00000000u, 0));
    TEST_ASSERT_EQUAL_HEX8(0x81u, (uint8_t)GpioReg_SetPin(0x01u, 7));
}

TEST(GpioReg, SettingAPinDrivesTheRightBits)
{
    uint32_t reg = GpioReg_SetPin(0x00u, 4);

    /* Single bit: index 4 is high, index 0 stays low. */
    TEST_ASSERT_BIT_HIGH(4, reg);
    TEST_ASSERT_BIT_LOW(0, reg);

    /* Masked fields: only bit 4 of the low nibble mask is high. */
    TEST_ASSERT_BITS_HIGH(0x10u, reg);
    TEST_ASSERT_BITS_LOW(0x0Fu, reg);
    TEST_ASSERT_BITS(0xFFu, 0x10u, reg);
}

TEST(GpioReg, ClearingAPinDrivesItLow)
{
    uint32_t reg = GpioReg_ClearPin(0xFFu, 3);

    TEST_ASSERT_BIT_LOW(3, reg);
    TEST_ASSERT_BITS_LOW(0x08u, reg);
}

TEST_GROUP_RUNNER(GpioReg)
{
    RUN_TEST_CASE(GpioReg, CountsSetPinsAsAnInteger);
    RUN_TEST_CASE(GpioReg, SettingAPinProducesTheExpectedRegister);
    RUN_TEST_CASE(GpioReg, SettingAPinDrivesTheRightBits);
    RUN_TEST_CASE(GpioReg, ClearingAPinDrivesItLow);
}
