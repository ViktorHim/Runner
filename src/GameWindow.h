#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include "State.h"
#include "Button.h"
#include "Player.h"
#include "Tilemap.h"
#include "ScreenSize.h"
class GameWindow
{
private:
    SDL_Renderer* renderer;
    State * state;
    TTF_Font *font;

    SDL_Texture * background;
    Button* backButton;
    Player * player;
    Tilemap * tilemap;
    SDL_Rect camera;
public:
    void update(Uint32 currentTime);
    void updateCamera();
    void updateKeyboardInput(SDL_Event * event);
    void render();
    GameWindow(SDL_Renderer * renderer, State * state, TTF_Font *font);
    ~GameWindow();
};
#endif