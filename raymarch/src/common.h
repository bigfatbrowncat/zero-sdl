#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <bgfx/bgfx.h>
#include <bgfx/bgfxplatform.h>
#include <bx/uint32_t.h>

#include <bx/timer.h>
#include <bx/fpumath.h>

#define LOG_GOOD(format, ...) { /*printf("%s (%s)", __FILE__, __LINE__);*/ printf(format "\n", ## __VA_ARGS__); fflush(stdout); }
#define LOG_BAD(format, ...) { /*printf("%s (%s)", __FILE__, __LINE__);*/ fprintf(stderr, format "\n", ## __VA_ARGS__); fflush(stderr); }

#endif