#include "cube.h"
#include "light.h"

struct World {
    struct Cube cube;
    struct Light light;
};

void world_init (struct World *self);