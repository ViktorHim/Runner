#ifndef UI_PANEL_H
#define UI_PANEL_H

#include "Button.h"
#include "ScreenSize.h"
#include <string>

class UIPanel
{
private:
    SDL_Texture * textTexture;
    SDL_Rect textRect;

    SDL_Texture * healthTexture;
    SDL_Rect healthRect;

    SDL_Texture * levelTexture;
    SDL_Rect levelRect;

    SDL_Renderer * renderer;
    TTF_Font *font;
public:
    UIPanel(SDL_Renderer * renderer, TTF_Font *font, int level);
    void update(int score, int health);
    void render();
};
#endif