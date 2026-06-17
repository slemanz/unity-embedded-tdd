#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

/* Writes a 4-byte header (start, id, length high, length low) into dst. */
void Packet_BuildHeader(uint8_t *dst, uint8_t id, uint16_t length);

/* Returns the static label for a packet id, or "unknown" for an unknown id. */
const char *Packet_Label(uint8_t id);

#endif /* PACKET_H */
