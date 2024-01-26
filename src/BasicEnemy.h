#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H

#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "HealthComponent.h"
#include "Player.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "Timer.h"
#include <iostream>

class BasicEnemy
{
protected:
    AnimationComponent * animationComponent;
    HitboxComponent * hitboxComponent;

    SDL_RendererFlip enemyFlip;
    SDL_Renderer * renderer;
    Player * target;
    SDL_Rect rect;
    int damage;
    int score;

    virtual void initAnimation() = 0;
public:
    BasicEnemy(SDL_Renderer * renderer, Vector2D position, Player * target);

    HealthComponent * healthComponent;

    virtual void update() = 0;
    virtual void render(int x, int y);
    virtual void move(int x, int y);

    int getScore();

    void setFlip(int dir);

    SDL_Rect getHitbox();
};
#endif