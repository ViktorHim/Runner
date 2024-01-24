#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "Timer.h"

#define EMEMY_BULLET "sprites/bullets/red.png"
#define PLAYER_BULLET "sprites/bullets/blue.png"
#define DEFAULT_VELOCITY 30
#define BULLET_SCALE 1

class Bullet
{
private:
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    SDL_Rect rect;
    SDL_RendererFlip bulletFlip;
    int velocity;

    Timer * lifeTimer; //таймер времени жизни пули
    bool isEnd;
public:
    void update();
    void destroy();
    bool isDestroied();
    void render(int x, int y);
    SDL_Rect getRect();
    Bullet(SDL_Renderer * renderer, Vector2D pos, SDL_RendererFlip flip);
};

#endif