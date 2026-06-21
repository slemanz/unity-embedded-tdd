#include "unity.h"
#include <stdint.h>
#include <string.h>
#include <math.h>

#define DEMO_ENABLE_FAILS           0

void setUp(void){}
void tearDown(void){}

// 1 Boolean and pointer validations
void test_bool_ptr_should_pass(void){
    int x = 123;
    TEST_ASSERT(1);
    TEST_ASSERT_TRUE(2 == 2);
    TEST_ASSERT_FALSE(0);
    TEST_ASSERT_UNLESS(0);      // alias for asserting false
    TEST_ASSERT_NULL(NULL);
    TEST_ASSERT_NOT_NULL(&x);
}

#if DEMO_ENABLE_FAILS
void test_bool_ptr_should_fail(void){
    int x = 0;
    TEST_ASSERT_TRUE(0);
    TEST_ASSERT_FALSE(1);
    TEST_ASSERT_NULL(&x);
    TEST_ASSERT_NOT_NULL(NULL);
}
#endif


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_bool_ptr_should_pass);

#if DEMO_ENABLE_FAILS
    RUN_TEST(test_bool_ptr_should_fail);
#endif

    return UNITY_END();
}
