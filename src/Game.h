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

//Экран завершения

//Враги

//Минибосс

//Рекорды

//Подпись

class Game
{
private:
    bool isEnd; // флаг окончания игры
    SDL_Window* window; // окно игры
    SDL_Renderer* renderer; // рендер
    State state; // Состояние игры
    TTF_Font *font; // шрифт для текста

    GameWindow* game; // окно с геймплеем
    SelectWindow* select;// окно выбора уровня
    MenuWindow* menu; // окно меню
public:
    void start();
    Game(Vector2D resolution);
    ~Game();
};
#endif
