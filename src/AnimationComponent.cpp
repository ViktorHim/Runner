#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    switchFrames = new Timer(100);
    currentAnimation = 0;
    currentFrame = 0;
}

void AnimationComponent::addAnimation(int key, int frames, std::string path)
{
    for(int i = 0; i < frames; i++)
    {
        char filename[30];
        sprintf(filename, "%s%d.png", path.c_str(), i + 1);
        std::cout << filename << std::endl;
        SDL_Surface* surface = IMG_Load(filename);

        if (!surface) {
            std::cout << filename << " error" << std::endl;
        }

        animations[key].push_back(SDL_CreateTextureFromSurface(renderer, surface));
        SDL_FreeSurface(surface);
    }
}

void AnimationComponent::setAnimation(int key)
{
    if(currentAnimation != key)
    {
        currentAnimation = key;
        currentFrame = 0;
    }
}

void AnimationComponent::setDelay(int delay)
{
    switchFrames = new Timer(delay);
}

SDL_Texture *AnimationComponent::getCurrentFrame()
{
    if (switchFrames->shouldTrigger())
    {
        currentFrame = (currentFrame + 1) % animations[currentAnimation].size();
    }

    return animations[currentAnimation][currentFrame];
}