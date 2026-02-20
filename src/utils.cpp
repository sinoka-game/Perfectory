#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.h"

SDL_Texture *LoadImage(SDL_Renderer *renderer, const char *path) {
    SDL_Texture *grass_image = IMG_LoadTexture(renderer, path);
    if (grass_image == nullptr) {
        std::cerr << "IMG_LoadTexture error: " << IMG_GetError() << "\n";
        return nullptr;
    }
    return grass_image;
}

void SetColor(SDL_Renderer* renderer, SDL_Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}
