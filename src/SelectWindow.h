#ifndef SELECT_WINDOW_H
#define SELECT_WINDOW_H
#include "State.h"
#include "Button.h"
#include "ScreenSize.h"
class SelectWindow
{
private:
    SDL_Renderer* renderer;
    State * state;
    TTF_Font *font;

    Button* levelButtons[3]; // массив кнопок уровней

    int level;
public:
    SelectWindow(SDL_Renderer * renderer, State * state, TTF_Font *font);
    void update();
    void render();
    int getLevel();
};
#endif