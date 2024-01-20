#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include "State.h"
#include "Button.h"
#include "Player.h"
class GameWindow
{
private:
    SDL_Renderer* renderer;
    State * state;
    TTF_Font *font;
    Button* backButton;

    Player * player;
public:
    void update(Uint32 currentTime);
    void updateKeyboardInput(SDL_Event * event);
    void render();
    GameWindow(SDL_Renderer * renderer, State * state, TTF_Font *font);
    ~GameWindow();
};
#endif