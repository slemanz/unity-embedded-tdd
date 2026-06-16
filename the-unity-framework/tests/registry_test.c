#include "unity_fixture.h"
#include "registry.h"

TEST_GROUP(Registry);

TEST_SETUP(Registry)
{
}

TEST_TEAR_DOWN(Registry)
{
}

TEST(Registry, ReportsAKnownId)
{
    /* TEST_ASSERT is the base check, TEST_ASSERT_TRUE is its readable alias. */
    TEST_ASSERT(Registry_IsKnown(0));
    TEST_ASSERT_TRUE(Registry_IsKnown(2));
}

TEST(Registry, ReportsAnUnknownId)
{
    /* TEST_ASSERT_UNLESS inverts the condition, just like asserting false. */
    TEST_ASSERT_FALSE(Registry_IsKnown(99));
    TEST_ASSERT_UNLESS(Registry_IsKnown(99));
}

TEST(Registry, KnownIdReturnsAName)
{
    TEST_ASSERT_NOT_NULL(Registry_NameOf(1));
}

TEST(Registry, UnknownIdReturnsNoName)
{
    TEST_ASSERT_NULL(Registry_NameOf(99));
}

TEST_GROUP_RUNNER(Registry)
{
    RUN_TEST_CASE(Registry, ReportsAKnownId);
    RUN_TEST_CASE(Registry, ReportsAnUnknownId);
    RUN_TEST_CASE(Registry, KnownIdReturnsAName);
    RUN_TEST_CASE(Registry, UnknownIdReturnsNoName);
}
