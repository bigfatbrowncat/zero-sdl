#ifndef RENDERER_H
#define RENDERER_H

struct RenderingThreadInitData {
	SDL_Window* window;
	SDL_GLContext context;
	RenderingThreadInitData(SDL_Window* window, SDL_GLContext context): window(window), context(context) {}
};

void doFinishRendering();
bool isRenderingFinished();

int renderingThreadFunction(void *param);

#endif