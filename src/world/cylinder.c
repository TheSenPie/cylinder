#include "cylinder.h"
#include "../util/fmath.h"

// N = number of sectors
// S = number of stacks
void cylinder_init (struct Cylinder *self, f32 radius, f32 height, size_t N, size_t S) {
    self->N = N;
    self->S = S;
    self->side_vertices_size = (N+1) * (S+1) * 9;
    self->side_indices_size = S * (N + 1) * 2 + 2 * (S - 1); // take into account degenrate points
    self->vertices = malloc(self->side_vertices_size * sizeof(f32));
    self->indices = malloc(self->side_indices_size * sizeof(int));

    // init the vertices
    int s, n, i;
    i = 0;
    for (s = 0; s <= S; s++) {
        for (n = N; n >= 0; n -= 1) {
            f32 x, y, z;
            x = sin((float) n / (float) N * TAU);
            y = (float) (s / (float) S - 0.5f);
            z = cos((float) n / (float) N * TAU);

            f32 r, g, b;
            r = sin(((float) n / (float) N + 0) * TAU);
            g = sin(((float) n / (float) N + 0.33) * TAU);
            b = sin(((float) n / (float) N + 0.66) * TAU);

            f32 n_x, n_y, n_z;
            n_x = x;
            n_y = 0;
            n_z = z;

            self->vertices[i] = radius * x;
            self->vertices[i + 1] = height * y;
            self->vertices[i + 2] = radius * z;
            self->vertices[i + 3] = n_x;
            self->vertices[i + 4] = n_y;
            self->vertices[i + 5] = n_z;
            self->vertices[i + 6] = r;
            self->vertices[i + 7] = g;
            self->vertices[i + 8] = b;

            printf("%f, %f, %f, %f, %f, %f, %f, %f, %f\n", self->vertices[i], self->vertices[i + 1], self->vertices[i + 2], self->vertices[i + 3], self->vertices[i + 4], self->vertices[i + 5], self->vertices[i + 6], self->vertices[i + 7], self->vertices[i + 8]);

            i += 9;
        }
    }

    // init the indices
    i = 0;
    for (s = 0; s < S; s++) {
        for (n = 0; n <= N; n++) {
            // quad
            self->indices[i]         = s * (N + 1) + n;
            self->indices[i + 1]     = (s + 1) * (N + 1) + n;

            // printf(", %d, %d", self->indices[i], self->indices[i + 1]);
            i += 2;
        }
        if (s + 1 < S) {
            // printf("generated degenerate\n");
            // add indices for degenrate triangles
            self->indices[i] = (s + 1) * (N + 1) + (N - 1) + 1;
            self->indices[i + 1] = (s + 1) * (N + 1);
            // printf(", %d, %d\n", self->indices[i], self->indices[i + 1]);
            i += 2;
        }
    }
}