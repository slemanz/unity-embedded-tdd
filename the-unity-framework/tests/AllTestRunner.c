#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(Registry);
    RUN_TEST_GROUP(GpioReg);
    RUN_TEST_GROUP(Sensor);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
