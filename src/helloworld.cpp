#include "common.h"
#include "event_handler.h"
#include "drawing.h"
#include "logo.h"

#define ERROR_SDL_INIT			1
#define ERROR_CREATE_WINDOW		2
#define ERROR_GET_CONTEXT		3

int eventFilter(void* window, const SDL_Event *event)
{
	if (event->type == SDL_WINDOWEVENT &&
		event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		draw((SDL_Window*)window);
	}
	return 1;
}

int main(int _argc, char** _argv)
{
	LOG_GOOD("Initializing SDL");
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
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

	initDrawing(window);

	SDL_SetEventFilter((SDL_EventFilter)eventFilter, window);

	LOG_GOOD("Starting event processing");
	while (processEvents() != erExit)
	{
		draw(window);
	}

	LOG_GOOD("Destroying the window");
	SDL_DestroyWindow(window);
	LOG_GOOD("Quitting SDL");
	SDL_Quit();

	return 0;
}
