#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include <iostream>
class HitboxComponent
{
private:
    SDL_Rect hitbox;
    SDL_Rect * target;
    SDL_Renderer * renderer;
    int offsetX;
    int offsetY;
public:
    void update();
    void render(int x, int y);
    SDL_Rect getHitbox();
    HitboxComponent(SDL_Renderer * renderer, SDL_Rect * target, int offsetX, int offsetY);
    ~HitboxComponent();
};
#endif