#include "input.h"
#include <iostream>

void Input::update() {
    SDL_Event event;
    SDL_PumpEvents();
    for(int i = 0; i < 128; ++i) {
        keysPressed[i] = false;
    }
    while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYUP) == 1) {
        keysPressed[event.key.keysym.sym] = event.key.state == SDL_PRESSED && !keys[event.key.keysym.sym];
        keys[event.key.keysym.sym] = event.key.state == SDL_PRESSED;
    }
}