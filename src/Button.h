#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
class Button
{
private:
    TTF_Font *font;
    SDL_Color color;
    SDL_Rect rect;
    SDL_Rect textRect;
    SDL_Texture* texture;
    SDL_Texture *textTexture;
    SDL_Renderer * renderer;
    std::string text;
public:
    void render();
    bool isClicked();
    Button(SDL_Renderer * renderer, SDL_Rect rect, TTF_Font *font, std::string text);
    ~Button();
};
#endif