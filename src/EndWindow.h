#ifndef END_WINDOW_H
#define END_WINDOW_H
#include "State.h"
#include "Button.h"
#include "ScreenSize.h"
#include <string>
class EndWindow
{
private:
    SDL_Renderer* renderer;
    State * state;
    TTF_Font *font;

    SDL_Texture * textTexture;
    SDL_Rect textRect;

    SDL_Texture * scoreTexture;
    SDL_Rect scoreRect;

    Button* backButton;
    Button* restartButton;

    bool win;
public:
    EndWindow(SDL_Renderer * renderer, State * state, TTF_Font *font);
    void update(int score, bool win);
    void render();
};
#endif