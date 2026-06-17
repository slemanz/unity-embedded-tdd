#include "unity_fixture.h"
#include "packet.h"

TEST_GROUP(Packet);

TEST_SETUP(Packet)
{
}

TEST_TEAR_DOWN(Packet)
{
}

TEST(Packet, LabelMatchesAsAString)
{
    TEST_ASSERT_EQUAL_STRING("data", Packet_Label(1));

    /* STRING_LEN compares only the first n characters: "pin" against "ping". */
    TEST_ASSERT_EQUAL_STRING_LEN("pinned", Packet_Label(0), 3);
}

TEST(Packet, LabelReturnsAStableAddress)
{
    /* The label is a static literal, so the same id yields the same pointer. */
    TEST_ASSERT_EQUAL_PTR(Packet_Label(1), Packet_Label(1));
}

TEST(Packet, HeaderHasTheExpectedBytes)
{
    uint8_t header[4];
    const uint8_t expected[4] = { 0xAA, 0x07, 0x01, 0x02 };

    Packet_BuildHeader(header, 0x07, 0x0102);

    /* MEMORY does a raw byte-for-byte comparison of the two regions. */
    TEST_ASSERT_EQUAL_MEMORY(expected, header, sizeof(expected));
}

TEST(Packet, HeaderMatchesElementByElement)
{
    uint8_t header[4];
    const uint8_t expected[4] = { 0xAA, 0x07, 0x01, 0x02 };

    Packet_BuildHeader(header, 0x07, 0x0102);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, header, 4);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, header, 4);
}

TEST_GROUP_RUNNER(Packet)
{
    RUN_TEST_CASE(Packet, LabelMatchesAsAString);
    RUN_TEST_CASE(Packet, LabelReturnsAStableAddress);
    RUN_TEST_CASE(Packet, HeaderHasTheExpectedBytes);
    RUN_TEST_CASE(Packet, HeaderMatchesElementByElement);
}
