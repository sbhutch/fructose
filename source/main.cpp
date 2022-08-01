#include <SDL.h>
#include <algorithm>
#include <array>

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

void draw_scene(SDL_Renderer* renderer)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    SDL_FPoint a { 240, 135 };
    SDL_FPoint b { static_cast<float>(x), static_cast<float>(y) };
    SDL_FPoint d { b.x - a.x, b.y - a.y };

    std::array rs = {
        SDL_FRect { 40.0f, 40.0f, 400.0f, 20.0f },
        SDL_FRect { 100.0f, 80.0f, 20.0f, 120.0f },
        SDL_FRect { 360.0f, 80.0f, 20.0f, 120.0f },
        SDL_FRect { 220.0f, 180.0f, 40.0f, 40.0f },
    };

    for (auto r : rs) {
        if (intersects(a, d, r)) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }
        SDL_RenderDrawRectF(renderer, &r);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLineF(renderer, a.x, a.y, b.x, b.y);
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
        draw_scene(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
