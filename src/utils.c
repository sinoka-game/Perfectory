#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.h"

SDL_Surface* load_image(char path[255]) {
    SDL_Surface* image = IMG_Load(path);
    if (image == NULL) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        return NULL;
    }
    return image;
}