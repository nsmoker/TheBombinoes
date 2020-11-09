#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Renderer {
private:
    SDL_Renderer* rend;
    TTF_Font* font;
public:
    Renderer(SDL_Renderer* r);
    void clear();
    void useFont(const std::string& fileLocation, int size);
    void drawText(const std::string& text, int x, int y, int w, int h, int a, int r, int g, int b);
    void drawRect(int x, int y, int w, int h, int a, int r, int g, int b);
    void fillRect(int x, int y, int w, int h, int a, int r, int g, int b);
    inline void draw() { SDL_RenderPresent(rend); }
    void kill();
};