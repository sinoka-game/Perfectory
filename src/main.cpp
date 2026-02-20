#include <string_view>
#include <array>
#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.h"

constexpr int  SCREEN_WIDTH      = 960;
constexpr int  SCREEN_HEIGHT     = 640;
constexpr int  TILE_SIZE         = 32;
constexpr std::string_view TITLE = "Perfectory aersion 1.0";

constexpr int MAP_WIDTH  = (SCREEN_WIDTH / TILE_SIZE);
constexpr int MAP_HEIGHT = (SCREEN_HEIGHT / TILE_SIZE);

SDL_Color sky = {113, 199, 245, 255}; // NOLINT

namespace {
    SDL_Resources Init() {
        SDL_Resources res{nullptr, nullptr};

        SDL_SetHint("SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR", "0");

        // SDL Init

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
            return res; 
        }

        // SDL_image Init

        const int IMG_FLAGS = IMG_INIT_PNG;
        if ((IMG_Init(IMG_FLAGS) & IMG_FLAGS) == 0) {
            std::cerr << "SDL_image Error: " << IMG_GetError() << "\n";
            return res;
        }

        // Create Window and Renderer

        res.window = SDL_CreateWindow(TITLE.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0); // NOLINT
        if (res.window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
            return res;
        }

        res.renderer = SDL_CreateRenderer(res.window, -1, SDL_RENDERER_ACCELERATED);
        if (res.renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
            return res;
        }

        return res;
    }

    int GetTile(MapData<MAP_WIDTH, MAP_HEIGHT>& map, int x, int y) {
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
            return map[x][y]; // NOLINT
        }
            
        return 0;
    }
}

int main() {
    bool running = true;
    SDL_Rect dst;

    // Map Init
    MapData<MAP_WIDTH, MAP_HEIGHT> ground_map;

    for (auto& row : ground_map) {
        row.fill(1); // fill 1 all tiles
    }
    
    // Init
    const SDL_Resources RES = Init();

    if (RES.window == nullptr || RES.renderer == nullptr) {
        SDL_DestroyRenderer(RES.renderer); 
        SDL_DestroyWindow(RES.window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Load image
    SDL_Texture *grass_image = LoadImage(RES.renderer, "assets/grass.png");
    SDL_Texture *bnf_image = LoadImage(RES.renderer, "assets/bnf.png");

    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event) == 1)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;

                default:
                    break;
            }
        }
        
        SetColor(RES.renderer, sky);
        SDL_RenderClear(RES.renderer);

        for (int x = 0; x < MAP_WIDTH; x++) {
            for (int y = 0; y < MAP_HEIGHT; y++) {
                dst.x = x * TILE_SIZE;
                dst.y = y * TILE_SIZE;
                dst.w = TILE_SIZE;
                dst.h = TILE_SIZE;
                
                switch (GetTile(ground_map, x, y)) {
                    case 0: 
                        break;
                    case 1:
                        SDL_RenderCopy(RES.renderer, grass_image, nullptr, &dst);
                        break;
                    default:
                        SDL_RenderCopy(RES.renderer, bnf_image, nullptr, &dst);
                        break;
                }
            }
        }
        
        SDL_RenderPresent(RES.renderer);
    }

    SDL_DestroyRenderer(RES.renderer);
    SDL_DestroyWindow(RES.window);
    
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
