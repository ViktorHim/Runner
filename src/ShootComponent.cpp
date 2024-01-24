#include "ShootComponent.h"

ShootComponent::ShootComponent(SDL_Renderer * renderer, SDL_Rect *fireOrigin, SDL_RendererFlip *flip)
{
    this->renderer = renderer;
    this->fireOrigin = fireOrigin;
    this->flip = flip;
}

void ShootComponent::setMap(Tilemap *map)
{
    this->map = map;
}

void ShootComponent::shoot()
{
    bullets.push(new Bullet(renderer, Vector2D(fireOrigin->x, fireOrigin->y), *flip));
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
            if(!map->isEmpty(row, col))
            {
                bullet->destroy();
                return;
            }
        }
    }
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