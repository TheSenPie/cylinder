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
    renderer_quad_color(&state.renderer, (vec2s){{1.0, 1.0}}, (vec4s){{1.0, 0.0, 0.0, 1.0f}}, GLMS_MAT4_IDENTITY);
}

int main(int argc, char *argv[]) {
	window_create(init, destroy, tick, update, render);
	window_loop();
	return 0;
}
