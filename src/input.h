#pragma once

#include <SDL2/SDL.h>

class Input {
    private:
        bool keys[128] = { false };
        bool keysPressed[128] = { false };
    public:
        void update();
        inline bool isDown(SDL_Keycode kc) { return keys[kc]; }
        inline bool isPressed(SDL_Keycode kc) { return keysPressed[kc]; }
};