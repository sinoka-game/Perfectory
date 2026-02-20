#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* LoadImage(SDL_Renderer *renderer, const char *path);
void SetColor(SDL_Renderer* renderer, SDL_Color c);

struct SDL_Resources {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

SDL_Color sky = {113, 199, 245, 255};


template <size_t Width, size_t Height>
using MapData = std::array<std::array<int, Height>, Width>;

#endif