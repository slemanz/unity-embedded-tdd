#include "mock_gpio.h"
#include "unity.h"
#include <string.h>

/*
 * The mock keeps an ordered list of expectations. Each *_Expect call appends one
 * entry; each real GPIO_Write/GPIO_Read consumes the next entry and asserts it
 * matches. Reading a value back (GPIO_Read) is stored alongside the expectation
 * so the mock can return what the test asked for.
 */

typedef enum
{
    CALL_WRITE,
    CALL_READ
} CallKind;

typedef struct
{
    CallKind  kind;
    uint8_t   pin;
    GpioState state;   /* write: the expected state; read: the value to return */
} Expectation;

#define MAX_EXPECTATIONS 16

static Expectation expectations[MAX_EXPECTATIONS];
static int         expected_count;   /* how many expectations were programmed */
static int         consumed_count;   /* how many real calls have arrived      */

void mock_gpio_Init(void)
{
    memset(expectations, 0, sizeof(expectations));
    expected_count = 0;
    consumed_count = 0;
}

void mock_gpio_Verify(void)
{
    if (consumed_count != expected_count)
    {
        TEST_FAIL_MESSAGE("mock_gpio: not every expected GPIO call happened");
    }
}

void mock_gpio_Destroy(void)
{
    mock_gpio_Init();
}

static Expectation *record(CallKind kind, uint8_t pin, GpioState state)
{
    TEST_ASSERT_MESSAGE(expected_count < MAX_EXPECTATIONS,
                        "mock_gpio: too many expectations, raise MAX_EXPECTATIONS");
    Expectation *e = &expectations[expected_count++];
    e->kind  = kind;
    e->pin   = pin;
    e->state = state;
    return e;
}

void GPIO_Write_Expect(uint8_t pin, GpioState state)
{
    record(CALL_WRITE, pin, state);
}

void GPIO_Read_ExpectAndReturn(uint8_t pin, GpioState value_to_return)
{
    record(CALL_READ, pin, value_to_return);
}

static Expectation *next_call(CallKind kind, const char *name)
{
    if (consumed_count >= expected_count)
    {
        TEST_FAIL_MESSAGE(name);   /* an unexpected call arrived */
    }
    Expectation *e = &expectations[consumed_count++];
    TEST_ASSERT_EQUAL_MESSAGE(kind, e->kind, name);
    return e;
}

/* The mocked contract. These definitions replace the real gpio.c at link time. */

void GPIO_Write(uint8_t pin, GpioState state)
{
    Expectation *e = next_call(CALL_WRITE, "mock_gpio: unexpected GPIO_Write");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(e->pin, pin, "mock_gpio: GPIO_Write wrong pin");
    TEST_ASSERT_EQUAL_MESSAGE(e->state, state, "mock_gpio: GPIO_Write wrong state");
}

GpioState GPIO_Read(uint8_t pin)
{
    Expectation *e = next_call(CALL_READ, "mock_gpio: unexpected GPIO_Read");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(e->pin, pin, "mock_gpio: GPIO_Read wrong pin");
    return e->state;
}
