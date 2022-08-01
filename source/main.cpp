#include <algorithm>
#include <SDL.h>

bool intersects(SDL_FPoint o, SDL_FPoint d, SDL_FRect r)
{
    float tx1 = (r.x - o.x) / d.x;
    float ty1 = (r.y - o.y) / d.y;

    float tx2 = (r.x + r.w - o.x) / d.x;
    float ty2 = (r.y + r.h - o.y) / d.y;

    float tmin = std::max(std::min(tx1, tx2), std::min(ty1, ty2));
    float tmax = std::min(std::max(tx1, tx2), std::max(ty1, ty2));

    return tmin >= 0 && tmin <= 1 && tmax >= tmin;
}

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
