#include "unity_fixture.h"
#include "adc.h"

TEST_GROUP(Adc);

TEST_SETUP(Adc)
{
}

TEST_TEAR_DOWN(Adc)
{
}

TEST(Adc, FillSetsEverySampleToTheBaseline)
{
    uint16_t samples[4];

    Adc_Fill(samples, 2048, 4);

    /* EACH_EQUAL: every element of the array equals the same scalar. */
    TEST_ASSERT_EACH_EQUAL_UINT16(2048, samples, 4);
}

TEST(Adc, ConvertsRawReadingToVolts)
{
    /* EQUAL_FLOAT uses a built-in tolerance, WITHIN lets you set your own. */
    TEST_ASSERT_EQUAL_FLOAT(0.0f, Adc_ToVolts(0));
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 3.3f, Adc_ToVolts(4095));
}

TEST(Adc, ConversionIsAlwaysAFiniteNumber)
{
    float volts = Adc_ToVolts(1000);

    TEST_ASSERT_FLOAT_IS_DETERMINATE(volts);
    TEST_ASSERT_FLOAT_IS_NOT_NAN(volts);
}

TEST_GROUP_RUNNER(Adc)
{
    RUN_TEST_CASE(Adc, FillSetsEverySampleToTheBaseline);
    RUN_TEST_CASE(Adc, ConvertsRawReadingToVolts);
    RUN_TEST_CASE(Adc, ConversionIsAlwaysAFiniteNumber);
}
