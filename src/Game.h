#include "SDL2/SDL.h"
#include "Vector2D.h"

#ifndef GAME_H
#define GAME_H
class Game
{
private:
    bool isEnd;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void update();
    void render();
public:
    void start();
    Game(Vector2D resolution);
    ~Game();
};
#endif
