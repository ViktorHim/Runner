#include "ShootComponent.h"

ShootComponent::ShootComponent(SDL_Renderer * renderer, SDL_Rect * fireOrigin, SDL_RendererFlip * flip, Bullet::BulletType type)
{
    this->type = type;
    this->renderer = renderer;
    this->fireOrigin = fireOrigin;
    this->flip = flip;
}

void ShootComponent::setMap(Tilemap *map)
{
    this->map = map;
}

void ShootComponent::shoot(int offsetX, int offsetY)
{
    bullets.push(new Bullet(renderer, Vector2D(fireOrigin->x + fireOrigin->w / 2 + offsetX,
                                            fireOrigin->y + fireOrigin->h / 2 + offsetY), *flip, type));
}

void ShootComponent::update()
{
    Bullet * bullet;
    for(int i = 0; i < bullets.size(); i++)
    {
        bullet = bullets.front();
        bullets.pop();

        if(!bullet->isDestroied())
        {
            bullet->update();
            updateCollision(bullet);

            bullets.push(bullet);
        }
    }
}

void ShootComponent::updateCollision(Bullet *bullet)
{
    if(map == nullptr) return;

    SDL_Rect bulletRect = bullet->getRect();\

    int tileX = bulletRect.x / TILE_SIZE;
    int tileY = bulletRect.y / TILE_SIZE;

    int tileRight = (bulletRect.x + bulletRect.w) / TILE_SIZE;
    int tileBottom = (bulletRect.y + bulletRect.h) / TILE_SIZE;

    for (int row = tileY; row <= tileBottom; ++row) 
    {
        for (int col = tileX; col <= tileRight; ++col)
        {
            if(row < map->getSize().y && col < map->getSize().x && !map->isEmpty(row, col))
            {
                bullet->destroy();
                return;
            }
        }
    }
}

bool ShootComponent::isCollision(SDL_Rect rect)
{
    Bullet * bullet;
    for(int i = 0; i < bullets.size(); i++)
    {
        bullet = bullets.front();
        bullets.pop();
        SDL_Rect bulletRect = bullet->getRect();
        if(!bullet->isDestroied())
        {
            bool overlapX = (rect.x < bulletRect.x + bulletRect.w) && (rect.x + rect.w > bulletRect.x);

            // Проверка по осям Y
            bool overlapY = (rect.y < bulletRect.y + bulletRect.h) && (rect.y + rect.h > bulletRect.y);

            // Если есть пересечение по обеим осям, прямоугольники пересекаются
            if(overlapX && overlapY)
            {
                return true;
            } 

            bullets.push(bullet);
        }
    }

    return false;
}

void ShootComponent::render(int x, int y)
{
    Bullet * bullet;
    for(int i = 0; i < bullets.size(); i++)
    {
        bullet = bullets.front();
        bullets.pop();

        bullet->render(x, y);

        bullets.push(bullet);
    }
}