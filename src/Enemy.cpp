#include "Enemy.h"

void Enemy::initAnimation()
{
    animationComponent = new AnimationComponent(renderer);
    animationComponent->addAnimation(ENEMY_IDLE, ENEMY_IDLE_FRAMES, "sprites/enemy1/");
}

Enemy::Enemy(SDL_Renderer *renderer, Vector2D position, Player *target)
{
    this->renderer = renderer;
    this->rect = {position.x, position.y, ENEMY_SIZE, ENEMY_SIZE};
    this->target = target;
    enemyFlip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
    attackRadius = 50;
    visibilityRadius = 600;
    dist = 300;
    damage = 1;
    state = NONE;


    hitboxComponent = new HitboxComponent(renderer, &rect, 0 , 0);
    healthComponent = new HealthComponent(0, 5);
    initAnimation();
}

void Enemy::update()
{
    hitboxComponent->update();
    dist = Vector2D::calculateDistance(Vector2D(rect.x, rect.y), target->getCenter());

    switch (state)
    {
    case NONE:
        if(dist < visibilityRadius)
        {
            state = ATTACK;
        }
        break;
    case ATTACK:
        attack();
        break;
    case DEFFENCE:
        deffence();
        break;
    default:
        break;
    }
}

void Enemy::attack()
{
    Vector2D targetPos = target->getCenter();
    double dx = ENEMY_DEFAULT_SPEED * (targetPos.x - rect.x) / dist;
    double dy = ENEMY_DEFAULT_SPEED * (targetPos.y - rect.y) / dist;
    setFlip(dx);
    move(dx, dy);

    if(dist < attackRadius)
    {
        target->healthComponent->getDamage(damage);
        state = DEFFENCE;
        return;
    }

    //if(!inVisibility()) state = NONE;
}

void Enemy::deffence()
{
    Vector2D targetPos = target->getCenter();
    double dx = 0.5 * ENEMY_DEFAULT_SPEED * (targetPos.x - rect.x) / dist;
    double dy = 0.5 * ENEMY_DEFAULT_SPEED * (targetPos.y - 320 - rect.y)/ dist;
    setFlip(dx);

    move(dx, dy);

    if(dist > visibilityRadius / 3)
    {
        state = ATTACK;
        return;
    }
}

bool Enemy::inVisibility()
{
   return dist < visibilityRadius;
}

void Enemy::setFlip(int dir)
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

void Enemy::render(int x, int y)
{
    SDL_Rect cameraPos = {rect.x - x, rect.y - y, rect.w, rect.h};
    SDL_RenderCopyEx(renderer, animationComponent->getCurrentFrame(), NULL, &cameraPos, 0, NULL, enemyFlip);
    hitboxComponent->render(x,y);
}

void Enemy::move(int x, int y)
{
    rect.x += x;
    rect.y += y;
}

SDL_Rect Enemy::getHitbox()
{
    return hitboxComponent->getHitbox();
}
