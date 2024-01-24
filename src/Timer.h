#ifndef TIMER_H
#define TIMER_H
#include "SDL2/SDL.h"
class Timer
{
private:
    Uint32 lastResetTime;
    int delay;

public:
    Timer(int delay);
    bool shouldTrigger();
};
#endif