#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H
#include "State.h"
#include "Button.h"

class MenuWindow
{
private:
    SDL_Renderer* renderer;
    State * state;
    TTF_Font *font;
    Button* playButton;
    Button* quitButton;
public:
    void update();
    void render();
    MenuWindow(SDL_Renderer * renderer, State * state, TTF_Font *font);
    ~MenuWindow();
};
#endif