#include "unity_fixture.h"
#include "calculator.h"
#include <limits.h>

TEST_GROUP(Calculator);

TEST_SETUP(Calculator)
{
}

TEST_TEAR_DOWN(Calculator)
{
}

TEST(Calculator, MultiplyingByZeroGivesZero)
{
    TEST_ASSERT_EQUAL_INT(0, Calculator_Multiply(1, 0));
    TEST_ASSERT_EQUAL_INT(0, Calculator_Multiply(0, 2));
}

TEST(Calculator, MultipliesPositiveNumbers)
{
    TEST_ASSERT_EQUAL_INT(5, Calculator_Multiply(5, 1));
    TEST_ASSERT_EQUAL_INT(8, Calculator_Multiply(2, 4));
}

TEST(Calculator, MultipliesNegativeNumbers)
{
    TEST_ASSERT_EQUAL_INT(-20, Calculator_Multiply(10, -2));
    TEST_ASSERT_EQUAL_INT(100, Calculator_Multiply(-10, -10));
}

TEST(Calculator, SaturatesWhenTheResultOverflows)
{
    TEST_ASSERT_EQUAL_INT(INT_MAX, Calculator_Multiply(INT_MAX, 2));
}

TEST_GROUP_RUNNER(Calculator)
{
    RUN_TEST_CASE(Calculator, MultiplyingByZeroGivesZero);
    RUN_TEST_CASE(Calculator, MultipliesPositiveNumbers);
    RUN_TEST_CASE(Calculator, MultipliesNegativeNumbers);
    RUN_TEST_CASE(Calculator, SaturatesWhenTheResultOverflows);
}
