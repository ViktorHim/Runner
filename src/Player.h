#ifndef PLAYER_H
#define PLAYER_H



#define PLAYER_SCALE 3
#define PLAYER_SIZE 64

#define IDLE 0
#define WALK 1
#define SIT 2

#define IDLE_FRAMES 4
#define WALK_FRAMES 8
#define SIT_FRAMES 1

#include "ScreenSize.h"
#include "ShootComponent.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "Tilemap.h"
#include "Timer.h"
#include <iostream>
class Player
{
public:
    enum AnimationsState
    {
        KEK
        // IDLE,
        // WALK,
        // SIT
    };
private:
    Tilemap * map;
    SDL_Rect rect;
    SDL_Rect hitbox;
    SDL_Renderer * renderer;
    SDL_RendererFlip playerFlip;
    bool isJump;
    bool onGround;
    bool isSit;

    double fallSpeed;
    double gravity;
    double maxFallSpeed;

    int jumpHeight;
    double jumpSpeed;
    double startHeight;

    Timer * shootTimer;

    AnimationComponent * animationComponent;
    
    void initAnimation();
    bool inMapBounce(int x);
    bool checkCollision(int x, int y);

    void jump();//прыжок
    void applyGravity();// падение и обновление прыжка
    void moveX(int dx); // перемещение игрока по оси X
    void flip(int dir);// Разворот текстурки взаисимости от направления движения
    void setAnimation(AnimationsState state); // переключение анимаций
public:
    HealthComponent * healthComponent;
    ShootComponent * shootComponent;

    int getPosX();
    int getPosY();
    Vector2D getCenter();
    SDL_Rect * getRect();
    int getDir();
    void update(Uint32 currentTime);
    void updateHitbox();
    void render(int x, int y);
    Player(SDL_Renderer * renderer, Vector2D position, Tilemap * map);
    ~Player();
};
#endif