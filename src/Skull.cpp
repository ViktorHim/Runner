#include "Skull.h"

void Skull::initAnimation()
{
    animationComponent = new AnimationComponent(renderer);
    animationComponent->addAnimation(ENEMY_IDLE, ENEMY_IDLE_FRAMES, "sprites/enemy1/");
}

Skull::Skull(SDL_Renderer *renderer, Vector2D position, Player *target) :BasicEnemy(renderer, position, target)
{
    //this->renderer = renderer;
    this->rect = {position.x, position.y, ENEMY_SIZE, ENEMY_SIZE};
    //this->target = target;
    //enemyFlip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
    attackRadius = 50;
    visibilityRadius = 500;
    dist = 300;
    damage = 2;
    state = NONE;
    score = 100;

    hitboxComponent = new HitboxComponent(renderer, &rect, 0 , 0);
    healthComponent = new HealthComponent(0, 5);
    initAnimation();
}

void Skull::update()
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

void Skull::attack()
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

void Skull::deffence()
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

bool Skull::inVisibility()
{
   return dist < visibilityRadius;
}