#include "Timer.h"

Timer::Timer(int delay)
{
    this->delay = delay;
    lastResetTime = SDL_GetTicks();
}

bool Timer::shouldTrigger()
{
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - lastResetTime;
    
    if (elapsedTime >= static_cast<Uint32>(delay)) {
            lastResetTime = currentTime;
            return true;
    } else {
        return false;
    }
}