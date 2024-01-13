#ifndef BUTTON_H
#define BUTTON_H
#include "SDL2/SDL.h"
#include "Vector2D.h"
class Button
{
private:
    SDL_Color color;
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Renderer * renderer;

    bool isClicked;

public:
    void render();
    void update(Vector2D mousePos);
    Button(SDL_Renderer * renderer);
    ~Button();
};
#endif