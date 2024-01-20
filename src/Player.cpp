#include "Player.h"
Player::Player(SDL_Renderer *renderer, Vector2D position)
{
    this->renderer = renderer;
    this->position = position;

    playerFlip = SDL_FLIP_NONE;
    currentAnimationState = IDLE;
    currentFrame = 0;
    lastFrameSwitchTime = 0;
    frameSwitchDelay = 100;

    initAnimation();
    currentAnimation = &animations[IDLE];

    rect.h = 64 * 3;
    rect.w = 64 * 3;
    rect.x = position.x;
    rect.y = position.y;
}


void Player::initAnimation()
{
    for(int i = 0; i < IDLE_FRAMES; i++)
    {
        char filename[30];
        sprintf(filename, "sprites/idle/%d.png", i + 1);
        SDL_Surface* surface = IMG_Load(filename);

        if (!surface) {
            std::cout << filename << " error" << std::endl;
        }

        animations[IDLE].push_back(SDL_CreateTextureFromSurface(renderer, surface));
        SDL_FreeSurface(surface);
    }

     for(int i = 0; i < WALK_FRAMES; i++)
    {
        char filename[30];
        sprintf(filename, "sprites/walk/%d.png", i + 1);
        SDL_Surface* surface = IMG_Load(filename);

        if (!surface) {
            std::cout << filename << " error" << std::endl;
        }

        animations[WALK].push_back(SDL_CreateTextureFromSurface(renderer, surface));
        SDL_FreeSurface(surface);
    }
}

void Player::flip(int dir)
{   
    if(dir == 1)
    {
        playerFlip = SDL_FLIP_NONE;
    }
    else
    {
        playerFlip = SDL_FLIP_HORIZONTAL;
    }
}

void Player::setAnimation(AnimationsState state)
{
    if(currentAnimationState != state)
    {
        currentAnimationState = state;
        currentAnimation = &animations[state];
        currentFrame = 0;
    }

}

void Player::update(Uint32 currentTime)
{
    if (currentTime - lastFrameSwitchTime >= frameSwitchDelay) {
            lastFrameSwitchTime = currentTime;
            currentFrame = (currentFrame + 1) % animations[currentAnimationState].size();
        }
}

void Player::render()
{    
    SDL_RenderCopyEx(renderer, currentAnimation->at(currentFrame), NULL, &rect, 0, NULL, playerFlip);
}

void Player::moveX(int x)
{
    rect.x += x;
}


