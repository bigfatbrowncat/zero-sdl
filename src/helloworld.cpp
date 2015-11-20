#include "common.h"
#include "controller.h"
#include "renderer.h"

#define ERROR_SDL_INIT			1
#define ERROR_CREATE_WINDOW		2
#define ERROR_GET_CONTEXT		3

int main(int _argc, char** _argv)
{
	LOG_GOOD("Initializing SDL");
	if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
		LOG_BAD("SDL initialization failed: %s", SDL_GetError());
		exit(ERROR_SDL_INIT);
	}
	
	LOG_GOOD("Creating SDL Window");
	int width = 800;
	int height = 600;
	SDL_Window* window = SDL_CreateWindow("bgfx with SDL2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	
	if (window == NULL) {
		LOG_BAD("Can't create a window: %s", SDL_GetError());
		exit(ERROR_CREATE_WINDOW);
	}
	
	LOG_GOOD("Starting rendering thread");
	RenderingThreadInitData data(window, NULL);
	SDL_Thread *thread = SDL_CreateThread(renderingThreadFunction, "Rendering thread", &data);

	LOG_GOOD("Starting event processing");
	while (processEvents() != erExit)
	{
		// Do nothing here
	}

	LOG_GOOD("Event processing finished");
	doFinishRendering();

	// Waiting for the render thread to stop
	while (!isRenderingFinished()) { usleep(1); }

	LOG_GOOD("Destroying the window");
	SDL_DestroyWindow(window);
	LOG_GOOD("Quitting SDL");
	SDL_Quit();

	return 0;
}
