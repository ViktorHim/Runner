#include "HitboxComponent.h"

void HitboxComponent::update()
{
    hitbox.x = target->x + (target->w - hitbox.w) / 2 + offsetX;
    hitbox.y = target->y + (target->h - hitbox.h) / 2 + offsetY;
}

void HitboxComponent::render(int x, int y)
{
    SDL_Rect hitboxRect = {hitbox.x- x, hitbox.y - y, hitbox.w, hitbox.h};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &hitboxRect);
}

SDL_Rect HitboxComponent::getHitbox()
{
    return hitbox;
}

HitboxComponent::HitboxComponent(SDL_Renderer * renderer, SDL_Rect * target, int offsetX, int offsetY)
{
    this->renderer = renderer;
    this->target = target;
    hitbox.h = target->h / 2;
    hitbox.w = target->w / 2;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}