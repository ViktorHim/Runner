#ifndef ENEMY_H
#define ENEMY_H

#include "BasicEnemy.h"

#define ENEMY_SIZE 120

#define ENEMY_IDLE 0
#define ENEMY_IDLE_FRAMES 16

#define ENEMY_DEFAULT_SPEED 5


class Skull : public BasicEnemy
{
public:
    enum EnemyState
    {
        ATTACK,
        DEFFENCE,
        NONE
    };
private:
    int attackRadius;
    int visibilityRadius;
    EnemyState state;
    int dist;

    void initAnimation() override;
public:

    Skull(SDL_Renderer * renderer, Vector2D position, Player * target);
    void update() override;
    void attack();
    void deffence();
    bool inVisibility();
};
#endif