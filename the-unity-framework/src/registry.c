#include "registry.h"
#include <stddef.h>

static const char *const names[] = {
    "idle",
    "armed",
    "running",
};

const char *Registry_NameOf(uint8_t id)
{
    if (id >= sizeof(names) / sizeof(names[0]))
        return NULL;

    return names[id];
}

bool Registry_IsKnown(uint8_t id)
{
    return Registry_NameOf(id) != NULL;
}
