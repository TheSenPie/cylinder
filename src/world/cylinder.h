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
    
    size_t side_vertices_size;
    size_t side_indices_size;
    size_t top_vertices_size;
    size_t top_indices_size;
    size_t bottom_vertices_size;
    size_t bottom_indices_size;

    float *vertices;
    int *indices;
};

void cylinder_init (struct Cylinder *self, f32 radius, f32 height, size_t N, size_t S);
#endif