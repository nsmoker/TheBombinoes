#include <iostream>
#include <string>
#include "grid.h"
#include "renderer.h"
#include "constants.h"
#include "input.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* rend;

    window = SDL_CreateWindow("The Bombinoes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);

    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Grid grid;
    Renderer renderer(rend);
    renderer.useFont("../assets/m5x7.ttf", 16);
    Input input;

    SDL_Event event;
    bool done = false;

    while(!done) {
        input.update();
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                done = true;
            }
        }
        int dx = 0;
        int dy = 0;
        bool cw = input.isPressed(SDLK_e);
        if(input.isPressed(SDLK_a)) {
            dx -= 1;
        }
        if(input.isPressed(SDLK_d)) {
            dx += 1;
        }
        if(input.isPressed(SDLK_s)) {
            dy -= 1;
        }
        renderer.clear();

        grid.update(dx, dy, cw, false);

        grid.render(renderer);

        renderer.draw();
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    renderer.kill();
    atexit(SDL_Quit);
}
