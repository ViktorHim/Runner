#include "BasicEnemy.h"

void BasicEnemy::setFlip(int dir)
{
    if(dir > 0)
    {
        enemyFlip = SDL_RendererFlip::SDL_FLIP_NONE;
    }
    else
    {
        enemyFlip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
    }
}

SDL_Rect BasicEnemy::getHitbox()
{
    return hitboxComponent->getHitbox();;
}

BasicEnemy::BasicEnemy(SDL_Renderer *renderer, Vector2D position, Player *target)
{
    this->renderer = renderer;
    this->target = target;
    enemyFlip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
}

void BasicEnemy::render(int x, int y)
{
    SDL_Rect cameraPos = {rect.x - x, rect.y - y, rect.w, rect.h};
    SDL_RenderCopyEx(renderer, animationComponent->getCurrentFrame(), NULL, &cameraPos, 0, NULL, enemyFlip);
    hitboxComponent->render(x,y);
}

void BasicEnemy::move(int x, int y)
{
    rect.x += x;
    rect.y += y;
}

int BasicEnemy::getScore()
{
    return score;
}