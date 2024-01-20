#include "Button.h"

void Button::render()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer,textTexture, NULL, &textRect);
}

bool Button::isClicked()
{
     SDL_Point mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    return (mousePosition.x > rect.x) && (mousePosition.x < (rect.w + rect.x)) && (mousePosition.y > rect.y) && (mousePosition.y < (rect.h + rect.y));
}

Button::Button(SDL_Renderer *renderer, SDL_Rect rect, TTF_Font *font, std::string text)
{
    this->renderer = renderer;
    this->rect = rect;
    this->font = font;
    this->text = text;

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255, 0});
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    textRect.h = textSurface->h;
    textRect.w = textSurface->w;
    textRect.x = rect.x + (rect.w - textRect.w) / 2;
    textRect.y = rect.y + (rect.h - textRect.h) / 2;

    SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 28, 255, 3));  // Заполнение красным цветом
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

Button::~Button()
{
}
