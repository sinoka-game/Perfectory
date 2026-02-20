#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct SDL_Resources {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

template <size_t Width, size_t Height>
using MapData = std::array<std::array<int, Height>, Width>;

struct PerVector2 {
    int x, y;

    PerVector2 operator+(const PerVector2& other) const {
        return {x + other.x, y + other.y};
    }
};


SDL_Texture* LoadImage(SDL_Renderer *renderer, const char *path);
void SetColor(SDL_Renderer* renderer, SDL_Color c);
PerVector2 GetSize(SDL_Texture *texture);

#endif