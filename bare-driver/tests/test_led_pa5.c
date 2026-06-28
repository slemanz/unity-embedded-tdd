#include "unity.h"              /* Unity API*/
#include "led_pa5.h"            /* prototypes: led_init/on/off/toggle */
#include "fake_stm32f4xx.h"     /* exposes RCC_, GPIOA_ globals and RCC/GPIOA macros */
#include <string.h>             /* memset */


#ifndef BIT
#define BIT(n)  (1u << (n))     /* Helper for bit assertion */
#endif 

void setUp(void)
{
    memset(&RCC_, 0, sizeof(RCC_));     /* clear RCC fake state */
    memset(&GPIOA_, 0, sizeof(GPIOA_)); /* clear GPIO fake state */
}

void tearDown(void)
{

}

/* 1) Init should enable clock, set PA5 output no pulls, and start OFF */
void test_led_init_enables_gpioa_and_configures_pa5_output_start_off(void)
{
    led_init();     // act
    TEST_ASSERT_BIT_HIGH(0, RCC->AHB1ENR);

    const uint32_t moder_mask   = (0x3u << (5u * 2));   /* MODER[11:10] */
    const uint32_t moder_out    = (0x1 << (5u * 2));    /* 01b output */
    TEST_ASSERT_BITS(moder_mask, moder_out, GPIOA->MODER);

    TEST_ASSERT_BIT_LOW(5, GPIOA->OTYPER);              /* push-pull */

    const uint32_t ospeed_mask  = (0x3u << (5u * 2));   /* OSPEED[11:10] */
    const uint32_t ospeed_med   = (0x1 << (5u * 2));    /* 01b medium speed */
    TEST_ASSERT_BITS(ospeed_mask, ospeed_med, GPIOA->OSPEED);

    const uint32_t pupd_mask    = (0x3u << (5u * 2));   /* PUPDR[11:10] */
    const uint32_t pupd_none    = (0x0 << (5u * 2));    /* 00b no pull */
    TEST_ASSERT_BITS(pupd_mask, pupd_none, GPIOA->PUPDR);

    TEST_ASSERT_BIT_LOW(5, GPIOA->ODR);                 /* LED starts OFF */
    TEST_ASSERT_BIT_HIGH(5u + 16u, GPIOA->BSRR);        /* BR5 reset bit set */
}

/* 2) led_on must only use BSRR set halfword */
void test_led_on_sets_bsrr_set_bit_only(void)
{
    led_init();
    GPIOA->BSRR = 0u;                                   /* Clear observable write */
    uint32_t before_odr = GPIOA->ODR;                   /* snapshot ODR */
    led_on();                                           /* act */
    TEST_ASSERT_BITS_HIGH(BIT(5), GPIOA->BSRR);         /* set halfword written */
    TEST_ASSERT_EQUAL_HEX32(before_odr, GPIOA->ODR);    /* ODR untouched */
}

/* 3) led_off must only use BSRR reset halfword */
void test_led_off_sets_bsrr_reset_bit_only(void)
{
    led_init();                                         
    GPIOA->BSRR = 0u;                                   /* clear observable write */
    uint32_t before_odr = GPIOA->ODR;                   /* snapshot ODR */
    led_off();                                          /* act */
    TEST_ASSERT_BITS_HIGH(BIT(5 + 16u), GPIOA->BSRR);   /* reset halfword written */
    TEST_ASSERT_EQUAL_HEX32(before_odr, GPIOA->ODR);    /* ODR untouched */
}

/* 4) toggle chooses set or reset based on ODR bit */
void test_led_toggle_uses_odr_to_choose_set_or_reset(void)
{
    led_init();

    GPIOA->ODR |= BIT(5u);                             /* pretend LED high */
    GPIOA->BSRR = 0u;
    led_toggle();
    TEST_ASSERT_BITS_HIGH(BIT(5u + 16u), GPIOA->BSRR);  /* choose reset */

    GPIOA->ODR &= ~BIT(5u);                             /* pretend LED low */
    GPIOA->BSRR = 0u;
    led_toggle();
    TEST_ASSERT_BITS_HIGH(BIT(5u), GPIOA->BSRR);        /* chose set*/
}

/* 5) Init must not disturb unrelated PA pins */
void test_led_init_does_not_touch_other_pins(void)
{
    GPIOA->MODER |= (0x3u << (0u * 2u));                /* seed PA0 = 11b (analog) */
    uint32_t before_pa0_moder = GPIOA->MODER & (0x3u << (0u * 2u));
    led_init();
    uint32_t after_pa0_moder = GPIOA->MODER & (0x3u << (0u*2u));
    TEST_ASSERT_EQUAL_HEX32(before_pa0_moder, after_pa0_moder); /* unchanged */
}

/* 6) Calling init twice should be idempotent on visible fields */
void test_led_init_is_idempotent(void)
{
    led_init();

    uint32_t m1 = GPIOA->MODER;
    uint32_t p1 = GPIOA->PUPDR;
    uint32_t t1 = GPIOA->OTYPER;
    uint32_t s1 = GPIOA->OSPEED;

    led_init();
    TEST_ASSERT_EQUAL_HEX32(m1, GPIOA->MODER);
    TEST_ASSERT_EQUAL_HEX32(p1, GPIOA->PUPDR);
    TEST_ASSERT_EQUAL_HEX32(t1, GPIOA->OTYPER);
    TEST_ASSERT_EQUAL_HEX32(s1, GPIOA->OSPEED);
}