#ifndef ENEMY_COMPONENT_H
#define ENEMY_COMPONENT_H
#include "SDL2/SDL.h"
#include "Tilemap.h"
#include "BasicEnemy.h"
#include "Skull.h"
#include "Soldier.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include <iostream>
#include <queue>
#include <typeinfo>
class EnemyComponent
{
private:
    std::queue <BasicEnemy*> enemies;
    SDL_Renderer * renderer;
    Player * target;
    int score;
public:
    EnemyComponent(SDL_Renderer * renderer, Player * target, Tilemap * map, int level);
    void update();
    int getscore();
    void render(int x, int y);
};
#endif