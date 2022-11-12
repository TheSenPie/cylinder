#include "gfx/window.h"
#include "gfx/gfx.h"

#include "state.h"

// global state
struct State state;

void init() {
	state.window = &window;
	renderer_init(&state.renderer);
	mouse_set_grabbed(true);
}

void destroy() {
	renderer_destroy(&state.renderer);
}

void tick() {
	state.ticks++;
}

void update() {
	if (state.window->mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down) {
		state.renderer.perspective_camera.theta -= state.window->mouse.delta.x * 0.01f;
		state.renderer.perspective_camera.fa += state.window->mouse.delta.y * 0.01f;
		state.renderer.perspective_camera.fa = clamp(state.renderer.perspective_camera.fa, F32_EPSILON, PI - F32_EPSILON);

		perspective_camera_look_at(&state.renderer.perspective_camera, (vec3s) {{0.0f, 0.0f, 0.0f, 0.0f}});
	}
	
    // wireframe toggle (T)
    if (state.window->keyboard.keys[GLFW_KEY_T].pressed) {
        state.renderer.flags.wireframe = !state.renderer.flags.wireframe;
    }

    // mouse toggle (ESC)
    if (state.window->keyboard.keys[GLFW_KEY_ESCAPE].pressed) {
        mouse_set_grabbed(!mouse_get_grabbed());
    }
}

void render() {
	renderer_prepare(&state.renderer);
	mat4s model = GLMS_MAT4_IDENTITY;
	// model = glms_translate_z(model, 2);
	// model = glms_rotate_x(model, state.ticks / 100.0);
	// model = glms_rotate_y(model, state.ticks / 100.0);
	// renderer_quad_color(&state.renderer, (vec2s){{1.0f, 1.0f}} ,(vec4s){{1.0f, 0.0f, 0.0f, 1.0f}}, model);
    renderer_cube_color(&state.renderer, model);
}

int main(int argc, char *argv[]) {
	window_create(init, destroy, tick, update, render);
	window_loop();
	return 0;
}
