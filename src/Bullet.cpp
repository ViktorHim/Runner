#include "Bullet.h"

Bullet::Bullet(SDL_Renderer * renderer, Vector2D pos, SDL_RendererFlip flip)
{
    this->renderer = renderer;
    if(flip == SDL_FLIP_NONE)
    {
        this->velocity = DEFAULT_VELOCITY;
    }
    else
    {
        this->velocity = - DEFAULT_VELOCITY;
    }
    bulletFlip = flip;

    SDL_Surface * surface = IMG_Load(PLAYER_BULLET);

    rect.x = pos.x;
    rect.y = pos.y;
    rect.h = surface->h * BULLET_SCALE;
    rect.w = surface->w * BULLET_SCALE;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    lifeTimer = new Timer(3000);
}

void Bullet::update()
{
    if(lifeTimer->shouldTrigger()) isEnd = true;

    if(!isEnd)
    {
        rect.x += velocity;
    }
}

void Bullet::destroy()
{
    isEnd = true;
}

bool Bullet::isDestroied()
{
    return isEnd;
}

void Bullet::render(int x, int y)
{
    SDL_Rect cameraRect = {rect.x - x, rect.y - y, rect.w, rect.h};
    SDL_RenderCopyEx(renderer, texture, NULL, &cameraRect, 0, NULL, bulletFlip);
}

SDL_Rect Bullet::getRect()
{
    return rect;
}
