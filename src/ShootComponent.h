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
    Bullet::BulletType type;
public:
    ShootComponent(SDL_Renderer * renderer, SDL_Rect * fireOrigin, SDL_RendererFlip * flip, Bullet::BulletType type);
    void setMap(Tilemap * map);
    void shoot(int offsetX, int offsetY);
    void update();
    void updateCollision(Bullet * bullet);
    bool isCollision(SDL_Rect rect);
    void render(int x, int y);
};
#endif
