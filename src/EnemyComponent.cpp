#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(SDL_Renderer * renderer, Player * target)
{
    this->renderer = renderer;
    this->target = target;
    this->score = 0;

    enemies.push(new Enemy(renderer, Vector2D(700, 100), target));
    enemies.push(new Enemy(renderer, Vector2D(1300, 150), target));
    enemies.push(new Enemy(renderer, Vector2D(1900, 200), target));
}

void EnemyComponent::update()
{
    Enemy * enemy;
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
                score += 100;
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
    Enemy * enemy;
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
