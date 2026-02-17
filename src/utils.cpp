#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.h"

SDL_Texture* PER_LoadImage(SDL_Renderer *renderer, const char *path) {
    SDL_Texture *grass_image = IMG_LoadTexture(renderer, path);
    if (!grass_image) {
        printf("IMG_LoadTexture error: %s\n", IMG_GetError());
        return NULL;
    }
    return grass_image;
}