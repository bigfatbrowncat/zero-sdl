#include "common.h"
#include "drawing.h"
#include "logo.h"

uint32_t reset = BGFX_RESET_VSYNC;
uint32_t debug = BGFX_DEBUG_TEXT;

void drawing_initialize(SDL_Window* window) {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	bgfx::sdlSetWindow(window);
	bgfx::renderFrame();

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);
}

void drawing_frame(SDL_Window* window) {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	bgfx::reset(width, height, reset);

	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, width, height);

	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::touch(0);

	// Use debug font to print information about this example.
	bgfx::dbgTextClear();
	bgfx::dbgTextImage(bx::uint16_max(width/2/8, 20)-20
					 , bx::uint16_max(height/2/16, 6)-6
					 , 40
					 , 12
					 , s_logo
					 , 160
					 );
	bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/00-helloworld");
	bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Initialization and debug text.");

	// Advance to next frame. Rendering thread will be kicked to
	// process submitted rendering primitives.
	bgfx::frame();
}

void drawing_finalize(SDL_Window* window) {
}