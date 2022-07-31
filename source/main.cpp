#include <SDL.h>
#include <cstdio>

int main(int, char**)
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS)) {
        std::puts(SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("fructose", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 270, 0);
    if (window == nullptr) {
        std::puts(SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::puts(SDL_GetError());
        return -1;
    }

    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
