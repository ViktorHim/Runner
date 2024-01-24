#ifndef ENEMY_H
#define ENEMY_H

#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "HealthComponent.h"
#include "Player.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "Timer.h"
#include <iostream>

#define ENEMY_SIZE 120

#define ENEMY_IDLE 0
#define ENEMY_IDLE_FRAMES 16

#define ENEMY_DEFAULT_SPEED 5


class Enemy
{
public:
    enum EnemyState
    {
        ATTACK,
        DEFFENCE,
        NONE
    };
private:
    AnimationComponent * animationComponent;
    HitboxComponent * hitboxComponent;

    SDL_RendererFlip enemyFlip;
    SDL_Renderer * renderer;
    Player * target;
    SDL_Rect rect;
    int attackRadius;
    int visibilityRadius;
    EnemyState state;
    int dist;
    int damage;

    void initAnimation();
public:
    HealthComponent * healthComponent;


    Enemy(SDL_Renderer * renderer, Vector2D position, Player * target);
    void update();
    void attack();
    void deffence();
    bool inVisibility();
    void setFlip(int dir);
    void render(int x, int y);
    void move(int x, int y);

    SDL_Rect getHitbox();
};
#endif