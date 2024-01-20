#ifndef PLAYER_H
#define PLAYER_H

#define IDLE_FRAMES 4
#define WALK_FRAMES 8

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include <iostream>
#include <vector>
#include <map>
class Player
{
public:
    enum AnimationsState
    {
        IDLE,
        WALK
    };
private:
    SDL_Rect rect;
    std::map<AnimationsState, std::vector<SDL_Texture*>> animations;

    SDL_Renderer * renderer;
    SDL_RendererFlip playerFlip;
    Vector2D position;
    AnimationsState currentAnimationState;
    std::vector<SDL_Texture*> * currentAnimation;
    int currentFrame;

    Uint32 lastFrameSwitchTime;
    Uint32 frameSwitchDelay;
    
    void initAnimation();
public:


    void flip(int dir);
    void setAnimation(AnimationsState state);
    void update(Uint32 currentTime);
    void render();
    void moveX(int x);
    Player(SDL_Renderer * renderer, Vector2D position);
    ~Player();
};
#endif