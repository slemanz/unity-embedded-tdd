#include "unity.h"
#include <stdint.h>
#include <string.h>
#include <math.h>

#ifndef DEMO_ENABLE_FAILS
#define DEMO_ENABLE_FAILS           0
#endif

void setUp(void){}
void tearDown(void){}

// 1) Boolean and pointer validations
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

// 2) Integer equality assertions
void test_integer_equality_should_pass(void){
    TEST_ASSERT_EQUAL(7, 7);
    TEST_ASSERT_EQUAL_INT(-42, -42);                // alias of TEST

    TEST_ASSERT_EQUAL_INT8((int8_t)-5, (int8_t)-5);
    TEST_ASSERT_EQUAL_INT16((int16_t)-1234, (int16_t)-1234);
    TEST_ASSERT_EQUAL_INT32(-123456, -123456);

    TEST_ASSERT_EQUAL_UINT(42u, 42u);
    TEST_ASSERT_EQUAL_UINT8((uint8_t)200, (uint8_t)200);
    TEST_ASSERT_EQUAL_UINT16((uint16_t)65500, (uint16_t)65500);
    TEST_ASSERT_EQUAL_UINT32((uint32_t)0xDEADBEEF, (uint32_t)0xDEADBEEF);
}

#if DEMO_ENABLE_FAILS
void test_integer_equality_should_fail(void){
    TEST_ASSERT_EQUAL_INT(10, 11);
    TEST_ASSERT_EQUAL_UINT8((uint8_t)1, (uint8_t)2);
}
#endif

// 3) Hexadecimal equality assertions
void test_hex_equality_should_pass(void){
    TEST_ASSERT_EQUAL_HEX8(0xAB, 0xAB);
    TEST_ASSERT_EQUAL_HEX16(0xBEEF, 0xBEEF);
    TEST_ASSERT_EQUAL_HEX32(0xA5A5C3C3, 0xA5A5C3C3);
}

#if DEMO_ENABLE_FAILS
void test_hex_equality_should_fail(void){
    TEST_ASSERT_EQUAL_HEX8(0xAA, 0xAB);
}
#endif

// 4) Bitmask and bit-level assertions
void test_bitmask_and_bit_level_should_pass(void)
{
    uint8_t actual = 0xA0;                  // 1010 0000
    TEST_ASSERT_BITS(0xF0, 0xA0, actual);   // only upper nibble compared
    TEST_ASSERT_BITS_HIGH(0xA0, actual);    // bits 7 and 5 high
    TEST_ASSERT_BITS_LOW(0x0A, actual);     // lower nibble low
    TEST_ASSERT_BIT_HIGH(7, actual);
    TEST_ASSERT_BIT_LOW(0, actual);
}

#if DEMO_ENABLE_FAILS
void test_bitmask_and_bit_level_should_fail(void){
    uint8_t actual = 0x20;                  // 0010 0000
    TEST_ASSERT_BITS(0xF0, 0xA0, actual);   // expected upper nibble A, actual is 2
    TEST_ASSERT_BIT_LOW(5, actual);         // bit 5 isactually high
}
#endif

// 5) Relational comparisons
void test_relational_should_pass(void)
{
    TEST_ASSERT_GREATER_THAN(10, 11);       // actual > threshold
    TEST_ASSERT_LESS_THAN(10, 9);           // actual > threshold
}

#if DEMO_ENABLE_FAILS
void test_relational_should_fail(void)
{
    TEST_ASSERT_GREATER_THAN(10, 11);       // equal is not greater
    TEST_ASSERT_LESS_THAN(10, 10);          // equal is not less
}
#endif

// 6) Integer range checks (within delta)
void test_within_delta_should_pass(void)
{
    TEST_ASSERT_INT_WITHIN(2, 100, 101);    // |101 - 100| <= 2
    TEST_ASSERT_UINT_WITHIN(1, 5u, 6u);     // |6 - 5| <= 1
}

#if DEMO_ENABLE_FAILS
void test_within_delta_should_fail(void)
{
    TEST_ASSERT_INT_WITHIN(1, 100, 103);    // delta too large
}
#endif


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_bool_ptr_should_pass);
    RUN_TEST(test_integer_equality_should_pass);
    RUN_TEST(test_hex_equality_should_pass);
    RUN_TEST(test_bitmask_and_bit_level_should_pass);
    RUN_TEST(test_relational_should_pass);
    RUN_TEST(test_within_delta_should_pass);

#if DEMO_ENABLE_FAILS
    RUN_TEST(test_bool_ptr_should_fail);
    RUN_TEST(test_integer_equality_should_fail);
    RUN_TEST(test_hex_equality_should_fail);
    RUN_TEST(test_bitmask_and_bit_level_should_fail);
    RUN_TEST(test_relational_should_fail);
    RUN_TEST(test_within_delta_should_fail);
#endif

    return UNITY_END();
}
