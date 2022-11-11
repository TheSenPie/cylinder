#include "renderer.h"

void renderer_init(struct Renderer *self) {
    // *self = (struct Renderer) {0};
    // self->camera_type = CAMERA_PERSPECTIVE;
    // self->current_shader = SHADER_NONE;

    // self->shaders[SHADER_BASIC_COLOR] = shader_create(
    //     "res/shaders/basic_color.vs", "res/shaders/basic_color.fs",
    //     1, (struct VertexAttr[]) {
    //         { .index = 0, .name = "position" }
    //     });

    // self->vao = vao_create();
    // self->vbo = vbo_create(GL_ARRAY_BUFFER, true);
    // self->ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, true);

    // perspective_camera_init(&self->perspective_camera, radians(75.0f));
    // ortho_camera_init(
    //     &self->ortho_camera, GLMS_VEC2_ZERO,
    //     (vec2s) {{ state.window->size.x, state.window->size.y }});
}

void renderer_destroy(struct Renderer *self) {
    // for (size_t i = 0; i <= SHADERS_LAST; i++) {
    //     shader_destroy(self->shaders[i]);
    // }

    // blockatlas_destroy(&self->block_atlas);
    // vao_destroy(self->vao);
    // vbo_destroy(self->vbo);
    // vbo_destroy(self->ibo);
}

void renderer_update(struct Renderer *self) {
    // blockatlas_update(&self->blocsk_atlas);
}

void renderer_prepare(struct Renderer *self, enum RenderPass pass) {
    // switch (pass) {
    //     case PASS_2D:
    //         ortho_camera_init(
    //             &self->ortho_camera, GLMS_VEC2_ZERO,
    //             (vec2s) {{ state.window->size.x, state.window->size.y }});
    //         glClear(GL_DEPTH_BUFFER_BIT);
    //         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //         glDisable(GL_DEPTH_TEST);
    //         glDisable(GL_CULL_FACE);
    //         glEnable(GL_BLEND);
    //         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //         break;
    //     case PASS_3D:
    //         glClearColor(
    //             self->clear_color.x, self->clear_color.y,
    //             self->clear_color.z, self->clear_color.w);
    //         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //         glPolygonMode(GL_FRONT_AND_BACK, self->flags.wireframe ? GL_LINE : GL_FILL);
    //         glEnable(GL_DEPTH_TEST);
    //         glDepthFunc(GL_LESS);
    //         glEnable(GL_CULL_FACE);
    //         glCullFace(GL_BACK);
    //         glEnable(GL_BLEND);
    //         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //         break;
    // }
}

void renderer_set_camera(struct Renderer *self, enum CameraType type) {
    self->camera_type = type;
}

void renderer_push_camera(struct Renderer *self) {
    assert(self->camera_stack.size + 1 < CAMERA_STACK_MAX);
    self->camera_stack.array[self->camera_stack.size++] = self->camera_type;
}

void renderer_pop_camera(struct Renderer *self) {
    assert(self->camera_stack.size != 0);
    self->camera_type = self->camera_stack.array[--self->camera_stack.size];
}

void renderer_set_view_proj(struct Renderer *self) {
    struct ViewProj view_proj;

    switch (self->camera_type) {
        case CAMERA_PERSPECTIVE:
            view_proj = self->perspective_camera.view_proj;
            break;
        case CAMERA_ORTHO:
            view_proj = self->ortho_camera.view_proj;
            break;
    }

    shader_uniform_view_proj(self->shader, view_proj);
}

void renderer_use_shader(struct Renderer *self, enum ShaderType shader) {
    if (shader == self->current_shader) {
        return;
    }

    self->current_shader = shader;
    self->shader = self->shaders[shader];
    shader_bind(self->shader);
}

void renderer_quad_color(
    struct Renderer *self, vec2s size,
    vec4s color, mat4s model) {
    renderer_use_shader(self, SHADER_BASIC_COLOR);
    renderer_set_view_proj(self);
    shader_uniform_mat4(self->shader, "m", model);
    shader_uniform_vec4(self->shader, "color", color);

    vbo_buffer(self->vbo, (f32[]) {
        0, 0, 0,
        0, size.y, 0,
        size.x, size.y, 0,
        size.x, 0, 0,
    }, 0, (4 * 3) * sizeof(f32));

    vbo_buffer(self->ibo, (u32[]) {
        3, 0, 1, 3, 1, 2
    }, 0, 6 * sizeof(u32));

    vao_attr(self->vao, self->vbo, 0, 3, GL_FLOAT, 0, 0);

    vao_bind(self->vao);
    vbo_bind(self->ibo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) 0);
}
