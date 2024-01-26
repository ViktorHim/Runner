#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(SDL_Renderer * renderer, Player * target, Tilemap * map, int level)
{
    this->renderer = renderer;
    this->target = target;
    this->score = 0;


    switch (level)
    {
    case 1:
            enemies.push(new Skull(renderer, Vector2D(700, 100), target));
            enemies.push(new Skull(renderer, Vector2D(1500, 150), target));
            enemies.push(new Skull(renderer, Vector2D(2100, 200), target));
        break;
    case 2:
        /* code */
        break;
    case 3:
            enemies.push(new Skull(renderer, Vector2D(4800, 300), target));
            enemies.push(new Skull(renderer, Vector2D(5100, 550), target));
            enemies.push(new Skull(renderer, Vector2D(5400, 300), target));

            Soldier * sol = new Soldier(renderer, Vector2D(960, 670 - SOLDIER_SIZE), target);
            sol->shootComponent->setMap(map);
            sol->setGuardDist(450);
            enemies.push(sol);
            sol = new Soldier(renderer, Vector2D(1700, 590 - SOLDIER_SIZE), target);
            sol->shootComponent->setMap(map);
            sol->setGuardDist(350);
            enemies.push(sol);
        break;
    }

}

void EnemyComponent::update()
{
    BasicEnemy * enemy;
    for(int i = 0; i < enemies.size(); i++)
    {
        enemy = enemies.front();
        enemies.pop();

        if(enemy->healthComponent->isAlive())
        {
            enemy->update();
            if(target->shootComponent->isCollision(enemy->getHitbox()))
            {
                enemy->healthComponent->getDamage(1);
            }
            if(!enemy->healthComponent->isAlive())
            {
                score += enemy->getScore();
            }

            enemies.push(enemy);
        }
    }
}

int EnemyComponent::getscore()
{
    return score;
}

void EnemyComponent::render(int x, int y)
{
    BasicEnemy * enemy;
    for(int i = 0; i < enemies.size(); i++)
    {
        enemy = enemies.front();
        enemies.pop();

        if(enemy->healthComponent->isAlive())
        {
            enemy->render(x, y);

            enemies.push(enemy);
        }
    }
}
