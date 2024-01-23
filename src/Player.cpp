#include "Player.h"
Player::Player(SDL_Renderer *renderer, Vector2D position, Tilemap * map)
{
    this->renderer = renderer;
    this->map = map;

    playerFlip = SDL_FLIP_NONE;
    currentAnimationState = IDLE;
    currentFrame = 0;
    lastFrameSwitchTime = 0;
    frameSwitchDelay = 100;

    initAnimation();
    currentAnimation = &animations[IDLE];

    rect.h = PLAYER_SIZE * PLAYER_SCALE;
    rect.w = PLAYER_SIZE * (PLAYER_SCALE);
    rect.x = position.x;
    rect.y = position.y;

    hitbox.h = PLAYER_SIZE * (PLAYER_SCALE-1);
    hitbox.w = PLAYER_SIZE * (PLAYER_SCALE - 1);
    hitbox.x = rect.x + (rect.w - hitbox.w) / 2;
    hitbox.y = rect.y + (rect.h - hitbox.h) / 2 + 35;

    fallSpeed = 5;
    gravity = 0.25;
    maxFallSpeed = 20;
    jumpHeight = 250;
    onGround = true;
    isJump = false;
    isSit = false;
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

    SDL_Surface * surface = IMG_Load("sprites/sit/1.png");
    if (!surface) {
        std::cout << "sprites/sit/1.png" << " error" << std::endl;
    }
    animations[SIT].push_back(SDL_CreateTextureFromSurface(renderer, surface));
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
    if (currentTime - lastFrameSwitchTime >= frameSwitchDelay)
        {
            lastFrameSwitchTime = currentTime;
            currentFrame = (currentFrame + 1) % animations[currentAnimationState].size();
        }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(!isSit)
    {
        if(state[SDL_SCANCODE_LEFT])
        {
            moveX(-10);
            setAnimation(AnimationsState::WALK);
            flip(-1);
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            moveX(10);
            setAnimation(AnimationsState::WALK);
            flip(1);
        }
        if(!state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_LSHIFT])
        {
            setAnimation(AnimationsState::IDLE);
        }
        if(state[SDL_SCANCODE_SPACE])
        {
            jump();
        }
    }
    if(state[SDL_SCANCODE_LSHIFT] && onGround)
    {
        isSit = true;
        setAnimation(AnimationsState::SIT);
    }
    else
    {
        isSit = false;
    }

    applyGravity();
    updateHitbox();
}

void Player::updateHitbox()
{
    if(isSit)
    {
        hitbox.h = PLAYER_SIZE * (PLAYER_SCALE-1)/2;
        hitbox.x = rect.x + (rect.w - hitbox.w) / 2;
        hitbox.y = rect.y + (rect.h) / 2 + 35;
    }
    else
    {
        hitbox.h = PLAYER_SIZE * (PLAYER_SCALE-1);
        hitbox.x = rect.x + (rect.w - hitbox.w) / 2;
        hitbox.y = rect.y + (rect.h - hitbox.h) / 2 + 35;
    }
}

void Player::render(int x, int y)
{    
    SDL_Rect cameraPos = {rect.x - x, rect.y - y, rect.w, rect.h};
    SDL_Rect hitboxRect = {hitbox.x- x, hitbox.y - y, hitbox.w, hitbox.h};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &hitboxRect);
    SDL_RenderCopyEx(renderer, currentAnimation->at(currentFrame), NULL, &cameraPos, 0, NULL, playerFlip);
}

int Player::getPosX()
{
    return rect.x;
}



int Player::getPosY()
{
    return rect.y;
}

void Player::applyGravity()
{
    if(isJump)
    {
        jumpSpeed = std::max(jumpSpeed - gravity, 1.0);

        if(startHeight - jumpHeight < hitbox.y)
        {
            rect.y -= jumpSpeed;
        }
        else
        {
            isJump = false;
        }
    }
    else
    {
        
        fallSpeed = std::min(fallSpeed + gravity * 2, maxFallSpeed);

        int newY = hitbox.y + (int)fallSpeed;

        if(!checkCollision(hitbox.x, newY))
        {
            rect.y += (int)fallSpeed;
            onGround = false;
        } 
        else
        {
            fallSpeed = 5;
            onGround = true;
        }
    }
}

void Player::jump()
{
    if(onGround && !isJump)
    {
        isJump = true;
        onGround = false;
        startHeight = hitbox.y;
        jumpSpeed = 15;
    }

}

void Player::moveX(int dx)
{
    int newX = hitbox.x + dx;
    if(!inMapBounce(newX)) return;

    if(!checkCollision(newX, hitbox.y)) rect.x += dx;
}

bool Player::inMapBounce(int x)
{
    return x >= 0 && x + hitbox.w <= map->getSize().x * TILE_SIZE;
}

bool Player::checkCollision(int x, int y)
{

    int tileX = x / TILE_SIZE;
    int tileY = y / TILE_SIZE;

    int tileRight = (x + hitbox.w) / TILE_SIZE;
    int tileBottom = (y + hitbox.h) / TILE_SIZE;

    for (int row = tileY; row <= tileBottom; ++row) 
    {
        for (int col = tileX; col <= tileRight; ++col)
        {
            if(!map->isEmpty(row, col))
            {
                return true;
            }
        }
    }

    return false;
}


