#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "State.h"
#include "GameWindow.h"
#include "MenuWindow.h"
#include "SelectWindow.h"

//Рекорды
//Минибосс
//Враги
//Экран завершения
//Подпись

class Game
{
private:
    bool isEnd;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State state;
    TTF_Font *font;

    GameWindow* game;
    SelectWindow* select;
    MenuWindow* menu;
public:
    void start();
    Game(Vector2D resolution);
    ~Game();
};
#endif
