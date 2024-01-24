#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H
#include "Timer.h"
#include <iostream>
class HealthComponent
{
private:
    int health;
    Timer * cooldownTimer;
public:
    bool isAlive();
    int getHealth();
    void getDamage(int damage);
    HealthComponent(int cooldown, int health);
    ~HealthComponent();
};
#endif