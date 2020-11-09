#include "renderer.h"

 Renderer::Renderer(SDL_Renderer *r) {
    rend = r;
    TTF_Init();
}

void Renderer::useFont(const std::string& fileLocation, int size) {
    font = TTF_OpenFont(fileLocation.c_str(), size);
}

void Renderer::drawText(const std::string& text, int x, int y, int w, int h, int a, int r, int g, int b) {
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), SDL_Color { (uint8_t) r, (uint8_t) g, (uint8_t) b, (uint8_t) a } );
    std::cout << SDL_GetError() << std::endl;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
    std::cout << SDL_GetError() << std::endl;
    auto textureDestRect = SDL_Rect {x, y, w, h};
    SDL_RenderCopy(rend, tex, nullptr, &textureDestRect);
    std::cout << SDL_GetError() << std::endl;
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);
}

void Renderer::drawRect(int x, int y, int w, int h, int a, int r, int g, int b) {
    SDL_Rect rect = SDL_Rect {x, y, w, h};
    SDL_SetRenderDrawColor(rend, r, g, b, a);
    SDL_RenderDrawRect(rend, &rect);
}

void Renderer::fillRect(int x, int y, int w, int h, int a, int r, int g, int b) {
    SDL_Rect rect = SDL_Rect {x, y, w, h};
    SDL_SetRenderDrawColor(rend, r, g, b, a);
    SDL_RenderFillRect(rend, &rect);
}

void Renderer::kill() {
    TTF_CloseFont(font);
    TTF_Quit();
}