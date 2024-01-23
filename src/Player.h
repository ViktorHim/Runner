#ifndef PLAYER_H
#define PLAYER_H

#define IDLE_FRAMES 4
#define WALK_FRAMES 8

#define PLAYER_SCALE 3
#define PLAYER_SIZE 64

#include "ScreenSize.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "Tilemap.h"
#include <iostream>
#include <vector>
#include <map>
class Player
{
public:
    enum AnimationsState
    {
        IDLE,
        WALK,
        SIT
    };
private:
    Tilemap * map;
    std::map<AnimationsState, std::vector<SDL_Texture*>> animations;
    SDL_Rect rect;
    SDL_Rect hitbox;
    SDL_Renderer * renderer;
    SDL_RendererFlip playerFlip;
    AnimationsState currentAnimationState;
    std::vector<SDL_Texture*> * currentAnimation;
    int currentFrame;
    bool isJump;
    bool onGround;
    bool isSit;

    double fallSpeed;
    double gravity;
    double maxFallSpeed;

    int jumpHeight;
    double jumpSpeed;
    double startHeight;

    Uint32 lastFrameSwitchTime;
    Uint32 frameSwitchDelay;
    
    void initAnimation();
    bool inMapBounce(int x);
    bool checkCollision(int x, int y);

    void jump();//прыжок
    void applyGravity();// падение и обновление прыжка
    void moveX(int dx); // перемещение игрока по оси X
    void flip(int dir);// Разворот текстурки взаисимости от направления движения
    void setAnimation(AnimationsState state); // переключение анимаций
public:
    int getPosX();
    int getPosY();
    void update(Uint32 currentTime);
    void updateHitbox();
    void render(int x, int y);
    Player(SDL_Renderer * renderer, Vector2D position, Tilemap * map);
    ~Player();
};
#endif