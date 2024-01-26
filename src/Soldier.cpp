#include "Soldier.h"

void Soldier::initAnimation()
{
    animationComponent = new AnimationComponent(renderer);
    animationComponent->setDelay(150);
    animationComponent->addAnimation(SOLDIER_IDLE, SOLDIER_IDLE_FRAMES, "sprites/soldier/idle/");
    animationComponent->addAnimation(SOLDIER_WALK, SOLDIER_WALK_FRAMES, "sprites/soldier/walk/");
}

Soldier::Soldier(SDL_Renderer *renderer, Vector2D position, Player *target) : BasicEnemy(renderer, position, target)
{
    this->rect = {position.x, position.y, SOLDIER_SIZE, SOLDIER_SIZE};

    damage = 1;
    startPos = position.x;
    direction = 1;
    guardDist = 500;
    visibilityRadius = 300;
    dist = 300;
    shootTimer = new Timer(1200);
    score = 200;

    hitboxComponent = new HitboxComponent(renderer, &rect, 0 , 0);
    healthComponent = new HealthComponent(0, 10);
    shootComponent = new ShootComponent(renderer, &rect, &enemyFlip, Bullet::BulletType::ENEMY);

    initAnimation();
}

void Soldier::update()
{
    hitboxComponent->update();
    setFlip(direction);
    dist = Vector2D::calculateDistance(Vector2D(rect.x, rect.y), target->getCenter());

    if(dist < visibilityRadius)
    {
        attack();
    }
    else
    {
        guard();
    }
    shootComponent->update();
}

void Soldier::render(int x, int y)
{
    BasicEnemy::render(x, y);
    shootComponent->render(x, y);
}

void Soldier::attack()
{
    animationComponent->setAnimation(SOLDIER_IDLE);
    direction = target->getPosX() - rect.x > 0 ? 1 : -1;
    if(shootTimer->shouldTrigger())
    {
        shootComponent->shoot(0, -15);
    }

    if(shootComponent->isCollision(target->getHitbox()))
    {
        target->healthComponent->getDamage(damage);
    }
}

void Soldier::guard()
{
    animationComponent->setAnimation(SOLDIER_WALK);
    if(rect.x < startPos || rect.x > startPos + guardDist)
    {
        direction *= -1;
    }
    
    move(SOLDIER_DEFAULT_SPEED * direction, 0);
}

void Soldier::setGuardDist(int len)
{
    guardDist = len;
}
