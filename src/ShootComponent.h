#ifndef SHOOT_COMPONENT_H
#define SHOOT_COMPONENT_H
#include "Bullet.h"
#include "ScreenSize.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "Tilemap.h"
#include "Bullet.h"
#include <iostream>
#include <queue>
class ShootComponent
{
private:
    std::queue<Bullet *> bullets;
    SDL_Renderer * renderer;
    SDL_Rect * fireOrigin;
    SDL_RendererFlip * flip;
    Tilemap * map;
public:
    ShootComponent(SDL_Renderer * renderer, SDL_Rect * fireOrigin, SDL_RendererFlip * flip);
    void setMap(Tilemap * map);
    void shoot();
    void update();
    void updateCollision(Bullet * bullet);
    void render(int x, int y);
};
#endif
