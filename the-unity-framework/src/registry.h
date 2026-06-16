#ifndef REGISTRY_H
#define REGISTRY_H

#include <stdbool.h>
#include <stdint.h>

/* Looks up the name of a state by id, returning NULL when the id is unknown. */
const char *Registry_NameOf(uint8_t id);

/* Reports whether an id maps to a known state. */
bool Registry_IsKnown(uint8_t id);

#endif /* REGISTRY_H */
