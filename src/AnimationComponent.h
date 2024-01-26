#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "Timer.h"
#include <iostream>
#include <map>
#include <vector>
class AnimationComponent
{
private:
     std::map<int, std::vector<SDL_Texture*>> animations;
     int currentAnimation;
     int currentFrame;
     Timer * switchFrames;
     SDL_Renderer * renderer;
public:
    AnimationComponent(SDL_Renderer * renderer);
    void addAnimation(int key, int frames, std::string path);
    void setAnimation(int key);
    void setDelay(int delay);
    SDL_Texture* getCurrentFrame();
    ~AnimationComponent();
};

#endif