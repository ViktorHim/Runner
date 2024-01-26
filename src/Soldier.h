#ifndef SOLDIER_H
#define SOLDIER_H

#include "BasicEnemy.h"
#include "Timer.h"

#define SOLDIER_SIZE 48 * 3

#define SOLDIER_IDLE 0
#define SOLDIER_WALK 1

#define SOLDIER_IDLE_FRAMES 5
#define SOLDIER_WALK_FRAMES 6

#define SOLDIER_DEFAULT_SPEED 5
class Soldier : public BasicEnemy
{
private:
    enum SoldierState
    {
        ATTACK,
        GUARD,
    };

    int direction;
    int startPos;
    int guardDist;
    int dist;
    int visibilityRadius;

    Timer * shootTimer;

    SoldierState state;

    void initAnimation() override;
public:
    ShootComponent * shootComponent;

    Soldier(SDL_Renderer * renderer, Vector2D position, Player * target);
    void update() override;
    void render(int x, int y) override;
    void attack();
    void guard();

    void setGuardDist(int len);
};
#endif