#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils.h"

#define SCREEN_WIDTH   960
#define SCREEN_HEIGHT  640
#define TILE_SIZE      32
#define TITLE          "Perfectory aersion 1.0"

#define MAP_WIDTH   (SCREEN_WIDTH / TILE_SIZE)
#define MAP_HEIGHT  (SCREEN_HEIGHT / TILE_SIZE)

int main() {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int running = 1;
    SDL_Rect dst;

    // Map Init
    int ground_map[MAP_WIDTH][MAP_HEIGHT];

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            ground_map[x][y] = 1;
        }
    }

    
    // Init
    SDL_SetHint("SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR", "0");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 1;
	}

    // Load image
    SDL_Texture *grass_image = PER_LoadImage(renderer, "assets/grass.png");
    SDL_Texture *bnf_image = PER_LoadImage(renderer, "assets/bnf.png");

    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;

                default:
                    break;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 113, 199, 245, 255);
        SDL_RenderClear(renderer);

        for (int x = 0; x < MAP_WIDTH; x++) {
            for (int y = 0; y < MAP_HEIGHT; y++) {
                dst.x = x * TILE_SIZE;
                dst.y = y * TILE_SIZE;
                dst.w = TILE_SIZE;
                dst.h = TILE_SIZE;
                
                switch (ground_map[x][y])
                {
                case 0: 
                    break;
                case 1:
                    SDL_RenderCopy(renderer, grass_image, NULL, &dst);
                    break;
                default:
                    SDL_RenderCopy(renderer, bnf_image, NULL, &dst);
                    break;
                }
            }
        }
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    IMG_Quit();
    SDL_Quit();

    return 0;
}
