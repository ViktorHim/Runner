#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include "EndWindow.h"
#include "State.h"
#include "EnemyComponent.h"
#include "UIPanel.h"
#include "Button.h"
#include "Player.h"
#include "Enemy.h"
#include "Tilemap.h"
#include "ScreenSize.h"
#include <string>

class GameWindow
{
private:
    SDL_Renderer* renderer;//окно рендера
    State * state;// состояние приложения
    TTF_Font *font;//шрифт

    SDL_Texture * background;// Задний фон

    SDL_Texture * finishLine;// финишная черта
    SDL_Rect finishRect;
    int finishX;
    
    EndWindow * endWindow; // окно завершения игры
    
    Button* backButton; // кнопка выхода в меню
    UIPanel * panel; // левая панель с информацией
    Player * player; // Игрок
    Tilemap * tilemap; // Игровая карта
    SDL_Rect camera; // Прямоугольник камеры

    EnemyComponent * enemyComponent;// Система врагов
public:
    void update(Uint32 currentTime);
    void updateCamera(); // обновление позиции камеры
    void render(); // отрисовка компонентов окна
    GameWindow(SDL_Renderer * renderer, State * state, TTF_Font *font, int level);
};
#endif