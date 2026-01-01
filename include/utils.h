#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* PER_LoadImage(SDL_Renderer *renderer, const char *path);

#endif