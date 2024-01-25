#include "Player.h"
Player::Player(SDL_Renderer *renderer, Vector2D position, Tilemap * map)
{
    this->renderer = renderer;
    this->map = map;

    playerFlip = SDL_FLIP_NONE;
    shootTimer = new Timer(250);

    initAnimation();

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

    shootComponent = new ShootComponent(renderer, &hitbox, &playerFlip);
    shootComponent->setMap(map);
    healthComponent = new HealthComponent(1000, 5);
}

SDL_Rect *Player::getRect()
{
    return &rect;
}

void Player::initAnimation()
{
    animationComponent = new AnimationComponent(renderer);

    animationComponent->addAnimation(IDLE, IDLE_FRAMES, "sprites/idle/");
    animationComponent->addAnimation(WALK, WALK_FRAMES, "sprites/walk/");
    animationComponent->addAnimation(SIT, SIT_FRAMES, "sprites/sit/");
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

void Player::update(Uint32 currentTime)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    Uint32 buttonState = SDL_GetMouseState(NULL, NULL);
    if(!isSit)
    {
        if(state[SDL_SCANCODE_A])
        {
            moveX(-10);
            animationComponent->setAnimation(WALK);
            flip(-1);
        }
        if (state[SDL_SCANCODE_D])
        {
            moveX(10);
            animationComponent->setAnimation(WALK);
            flip(1);
        }
        if(!state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_S])
        {
            animationComponent->setAnimation(IDLE);
        }
        if(state[SDL_SCANCODE_SPACE])
        {
            jump();
        }
    }
    if (buttonState & SDL_BUTTON(SDL_BUTTON_LEFT)) 
    {
        if(shootTimer->shouldTrigger())
        {
           shootComponent->shoot();
        }
    }
    // if(state[SDL_SCANCODE_F])
    // {
    //     if(shootTimer->shouldTrigger())
    //     {
    //         shootComponent->shoot();
    //     }
    // }
    if((state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_S] ) && onGround)
    {
        isSit = true;
        animationComponent->setAnimation(SIT);
    }
    else
    {
        isSit = false;
    }

    shootComponent->update();
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
    SDL_RenderCopyEx(renderer, animationComponent->getCurrentFrame(), NULL, &cameraPos, 0, NULL, playerFlip);

    shootComponent->render(x, y);
}

Vector2D Player::getCenter()
{
    return Vector2D(hitbox.x, hitbox.y);
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
            if(row < map->getSize().y && col < map->getSize().x && !map->isEmpty(row, col))
            {
                return true;
            }
        }
    }

    return false;
}