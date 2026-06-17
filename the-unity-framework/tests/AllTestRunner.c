#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(Registry);
    RUN_TEST_GROUP(GpioReg);
    RUN_TEST_GROUP(Sensor);
    RUN_TEST_GROUP(Packet);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
