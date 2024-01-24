#include "HealthComponent.h"

bool HealthComponent::isAlive()
{
    return health > 0;
}

int HealthComponent::getHealth()
{
    return health;
}

void HealthComponent::getDamage(int damage)
{
    if(cooldownTimer->shouldTrigger())
    {
        health = std::max(health - damage, 0);
        //std::cout << health << std::endl;
    }
}

HealthComponent::HealthComponent(int cooldown, int health)
{
    cooldownTimer = new Timer(cooldown);
    this->health = health;
}