#ifndef CYLINDER
#define CYLINDER
#include "../util/types.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"

#include <cglm/struct.h>

#pragma GCC diagnostic pop

struct Cylinder {
    vec3s postion;
    int S; // number of stacks
    int N; // number of sectors
    float *vertices;
    int *indices;
    size_t vertices_size;
    size_t indices_size;
};

void cylinder_init (struct Cylinder *self, f32 radius, f32 height, size_t N, size_t S);
#endif