#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include <iostream>

class Tile
{
private:
    SDL_Rect rect;
    SDL_Rect sourceRect;
    SDL_Renderer * renderer;
    SDL_Texture* texture;
public:
    bool isEmpty();
    void render(int x, int y);
    Tile();
    Tile(SDL_Renderer *renderer, SDL_Rect posRect, SDL_Rect sourceRect, SDL_Texture *texture = nullptr);
    ~Tile();
};
#endif