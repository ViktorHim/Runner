#ifndef ENEMY_COMPONENT_H
#define ENEMY_COMPONENT_H
#include "SDL2/SDL.h"
#include "Enemy.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include <iostream>
#include <queue>
class EnemyComponent
{
private:
    std::queue <Enemy*> enemies;
    SDL_Renderer * renderer;
    Player * target;
    int score;
public:
    EnemyComponent(SDL_Renderer * renderer, Player * target);
    void update();
    int getscore();
    void render(int x, int y);
};
#endif