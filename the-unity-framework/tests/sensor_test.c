#include "unity_fixture.h"
#include "sensor.h"

static const uint16_t samples[] = { 1980, 2010, 2000, 2030, 1990 };

TEST_GROUP(Sensor);

TEST_SETUP(Sensor)
{
}

TEST_TEAR_DOWN(Sensor)
{
}

TEST(Sensor, AverageStaysBetweenTheRails)
{
    uint16_t avg = Sensor_Average(samples, 5); /* 2002 */

    /* Relational: the threshold comes first, the actual reading second. */
    TEST_ASSERT_GREATER_THAN_UINT16(1800, avg);
    TEST_ASSERT_LESS_THAN_UINT16(2200, avg);
}

TEST(Sensor, AverageStaysCloseToTheTarget)
{
    uint16_t avg = Sensor_Average(samples, 5); /* 2002 */

    /* Range: avg must be within +/- 50 of the 2000 target. */
    TEST_ASSERT_UINT16_WITHIN(50, 2000, avg);
}

TEST_GROUP_RUNNER(Sensor)
{
    RUN_TEST_CASE(Sensor, AverageStaysBetweenTheRails);
    RUN_TEST_CASE(Sensor, AverageStaysCloseToTheTarget);
}
