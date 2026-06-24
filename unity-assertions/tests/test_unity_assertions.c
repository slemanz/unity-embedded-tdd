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

// 7) Pointers, strings, and raw memory
void test_ptr_string_memory_should_pass(void)
{
    int x;
    int* p = &x;
    TEST_ASSERT_EQUAL_PTR(&x, p);

    TEST_ASSERT_EQUAL_STRING("embedded", "embedded");
    TEST_ASSERT_EQUAL_STRING_LEN("firmwareX", "firmwareY", 8); // first 8 match "firmware"

    uint8_t exp[4] = {1, 2, 3, 4};
    uint8_t act[4] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_MEMORY(exp, act, sizeof exp);
}

#if DEMO_ENABLE_FAILS
void test_ptr_string_memory_should_fail(void)
{
    int a, b;
    TEST_ASSERT_EQUAL_PTR(&a, &b);

    TEST_ASSERT_EQUAL_STRING("abc", "abd");

    uint8_t exp[3] = {1, 2, 3};
    uint8_t act[3] = {1, 2, 4};
    TEST_ASSERT_EQUAL_MEMORY(exp, act, sizeof exp);
}
#endif

// 8) array equality assertions
void test_array_equality_should_pass(void)
{
    int16_t ei[3] = {-1, 2, -3};
    int16_t ai[3] = {-1, 2, -3};
    TEST_ASSERT_EQUAL_INT16_ARRAY(ei, ai, 3);

    uint8_t eu[4] = {1, 2, 3, 4};
    uint8_t au[4] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(eu, au, 4);

    const char* es[2] = {"OK", "OK"};
    const char* as[2] = {"OK", "OK"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(es, as, 2);

    int x = 1, y = 2;
    void* ep[2] = {&x, &y};
    void* ap[2] = {&x, &y};
    TEST_ASSERT_EQUAL_PTR_ARRAY(ep, ap, 2);

    uint8_t emem[2][3] = {{1, 2, 3}, {4, 5, 6}};
    uint8_t amem[2][3] = {{1, 2, 3}, {4, 5, 6}};
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(emem, amem, 3, 2);   // element size 3, count 2
}

#if DEMO_ENABLE_FAILS
void test_array_equality_should_fail(void)
{
    uint8_t e[3] = {1, 2, 3};
    uint8_t a[3] = {1, 2, 99};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(e, a, 3);
}
#endif

// 9) Arrays compared to a single value
struct Pair {uint8_t a, b;};

void test_each_equal_should_pass(void)
{
    uint16_t arr_u16[4] = {7, 7, 7, 7};
    TEST_ASSERT_EACH_EQUAL_UINT16(7, arr_u16, 4);

    const char* sarr[3] = {"OK", "OK", "OK"};
    TEST_ASSERT_EACH_EQUAL_STRING("OK", sarr, 3);

    struct Pair expected = {1, 2};
    struct Pair parr[2] = {{1, 2}, {1, 2}};
    TEST_ASSERT_EACH_EQUAL_MEMORY(&expected, parr, sizeof(struct Pair), 2);
}

#if DEMO_ENABLE_FAILS
void test_each_equal_should_fail(void)
{
    uint16_t arr_u16[3] = {7, 7, 8};
    TEST_ASSERT_EACH_EQUAL_UINT16(7, arr_u16, 3);
}
#endif

// 10) Floating point assertions
void test_float_should_pass(void)
{
    TEST_ASSERT_EQUAL_FLOAT(1.5f, 1.5f);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 3.14f, 3.145f);

    float farr[3] = {2.0f, 2.0f, 2.0f};
    TEST_ASSERT_EACH_EQUAL_FLOAT(2.0f, farr, 3);

    TEST_ASSERT_FLOAT_IS_INF(INFINITY);
    TEST_ASSERT_FLOAT_IS_NAN(NAN);
    TEST_ASSERT_FLOAT_IS_DETERMINATE(0.0f);

    TEST_ASSERT_FLOAT_IS_NOT_INF(1.0f);
    TEST_ASSERT_FLOAT_IS_NOT_NEG_INF(1.0f);
    TEST_ASSERT_FLOAT_IS_NOT_NAN(1.0f);
}

#if DEMO_ENABLE_FAILS
void test_float_should_fail(void)
{
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, 1.01f); // outside tolerance
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
    RUN_TEST(test_ptr_string_memory_should_pass);
    RUN_TEST(test_array_equality_should_pass);
    RUN_TEST(test_each_equal_should_pass);
    RUN_TEST(test_float_should_pass);

#if DEMO_ENABLE_FAILS
    RUN_TEST(test_bool_ptr_should_fail);
    RUN_TEST(test_integer_equality_should_fail);
    RUN_TEST(test_hex_equality_should_fail);
    RUN_TEST(test_bitmask_and_bit_level_should_fail);
    RUN_TEST(test_relational_should_fail);
    RUN_TEST(test_within_delta_should_fail);
    RUN_TEST(test_ptr_string_memory_should_fail);
    RUN_TEST(test_array_equality_should_fail);
    RUN_TEST(test_each_equal_should_fail);
    RUN_TEST(test_float_should_fail);
#endif

    return UNITY_END();
}
