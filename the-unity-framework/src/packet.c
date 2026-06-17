#include "packet.h"

void Packet_BuildHeader(uint8_t *dst, uint8_t id, uint16_t length)
{
    dst[0] = 0xAA; /* start byte */
    dst[1] = id;
    dst[2] = (uint8_t)(length >> 8);
    dst[3] = (uint8_t)(length & 0xFFu);
}

const char *Packet_Label(uint8_t id)
{
    switch (id)
    {
        case 0:
            return "ping";
        case 1:
            return "data";
        default:
            return "unknown";
    }
}
