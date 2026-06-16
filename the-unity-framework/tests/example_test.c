#include "unity_fixture.h"
#include "example.h"

TEST_GROUP(Example);

TEST_SETUP(Example)
{
}

TEST_TEAR_DOWN(Example)
{
}

TEST(Example, AddsTwoNumbers)
{
    TEST_ASSERT_EQUAL_UINT8(5, Example_Add(2, 3));
}

TEST(Example, AddsZero)
{
    TEST_ASSERT_EQUAL_UINT8(7, Example_Add(7, 0));
}

TEST_GROUP_RUNNER(Example)
{
    RUN_TEST_CASE(Example, AddsTwoNumbers);
    RUN_TEST_CASE(Example, AddsZero);
}
