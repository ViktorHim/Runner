#include "Tile.h"

bool Tile::isEmpty()
{
    bool f =  sourceRect.w == 0;
    // sourceRect.w = 16;
    // sourceRect.h = 16;
    return f;
}

void Tile::render(int x, int y)
{
    SDL_Rect cameraRect = {rect.x - x, rect.y - y, rect.w, rect.h};
    SDL_RenderCopy(renderer, texture, &sourceRect, &cameraRect);
}

Tile::Tile()
{
}

Tile::Tile(SDL_Renderer *renderer, SDL_Rect posRect, SDL_Rect sourceRect, SDL_Texture *texture)
{
    this->renderer = renderer;
    this->rect = posRect;
    this->sourceRect = sourceRect;
    this->texture = texture;
}

Tile::~Tile()
{
}
