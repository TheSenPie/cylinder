#include "cylinder.h"

// N = number of sectors
// S = number of stacks
void cylinder_init (struct Cylinder *self, f32 radius, f32 height, size_t N, size_t S) {
    self->N = N;
    self->S = S;
    self->vertices_size = (N+1) * (S+1) * 9;
    self->indices_size = 6 * N * S + 2 * (S - 1); // take into account degenrate points
    self->vertices = malloc(self->vertices_size * sizeof(f32));
    self->indices = malloc(self->indices_size * sizeof(int));

    // init the vertices
    size_t s, n, i;
    i = 0;
    for (s = 0; s <= S; s++) {
        for (n = 0; n <= N; n++) {
            f32 x, y, z;
            x = n * (M_PI * radius) / N;
            y = s * (height) / S;
            z = 0;

            f32 r, g, b;
            r = 1;
            g = 0;
            b = 0;

            f32 n_x, n_y, n_z;
            n_x = 0;
            n_y = 0;
            n_z = -1;

            self->vertices[i] = x;
            self->vertices[i] = y;
            self->vertices[i] = z;
            self->vertices[i] = r;
            self->vertices[i] = g;
            self->vertices[i] = b;
            self->vertices[i] = n_x;
            self->vertices[i] = n_y;
            self->vertices[i] = n_z;
            i += 9;
        }
    }

    // init the indices
    i = 0;
    for (s = 0; s < S; s++) {
        for (n = 0; n < N; n++) {
            // first triangle
            self->indices[i]         = s * (N + 1) + n;
            self->indices[i + 1]     = (s + 1) * (N + 1) + n;
            self->indices[i + 2]     = s * (N + 1) + n + 1; 

            // second triangle
            self->indices[i + 3]     = (s + 1) * (N + 1) + n;
            self->indices[i + 4]     = s * (N + 1) + n + 1; 
            self->indices[i + 5]     = (s + 1) * (N + 1) + n + 1;

            printf(", %d, %d, %d, %d, %d, %d", self->indices[i], self->indices[i + 1], self->indices[i + 2], self->indices[i + 3], self->indices[i + 4], self->indices[i + 5]);
            i += 6;
        }
        if (s + 1 < S) {
            // printf("generated degenerate\n");
            // add indices for degenrate triangles
            self->indices[i] = (s + 1) * (N + 1) + (N - 1) + 1;
            self->indices[i + 1] = (s + 1) * (N + 1);
            printf(", %d, %d\n", self->indices[i], self->indices[i + 1]);
            i += 2;
        }
    }
}