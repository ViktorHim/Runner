#include "UIPanel.h"

UIPanel::UIPanel(SDL_Renderer * renderer, TTF_Font *font, int level)
{
    this->renderer = renderer;
    this->font = font;

    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, "Очки: 0", {255, 255, 255, 0}); // инициализация счета игры
    textRect.h = textSurface->h;
    textRect.w = textSurface->w;
    textRect.x = 50;
    textRect.y = 100;
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    textSurface = TTF_RenderUTF8_Blended(font, "Жизни: 5", {255, 255, 255, 0}); //инициализация здоровья игрока
    healthRect.h = textSurface->h;
    healthRect.w = textSurface->w;
    healthRect.x = 50;
    healthRect.y = 150;
    healthTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    std::string levelText = "Уровень: " + std::to_string(level); // инициализация уровня
    textSurface = TTF_RenderUTF8_Blended(font, levelText.c_str(), {255, 255, 255, 0});
    levelRect.h = textSurface->h;
    levelRect.w = textSurface->w;
    levelRect.x = 50;
   levelRect.y = 50;
    levelTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
}

void UIPanel::update(int score, int health)
{
    std::string scoreText = "Очки: " + std::to_string(score);
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, scoreText.c_str(), {255, 255, 255, 0});
    textRect.h = textSurface->h;
    textRect.w = textSurface->w;
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    std::string healthText = "Жизни: " + std::to_string(health);
    textSurface = TTF_RenderUTF8_Blended(font, healthText.c_str(), {255, 255, 255, 0});
    healthRect.h = textSurface->h;
    healthRect.w = textSurface->w;
    healthTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
}

void UIPanel::render()
{
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderCopy(renderer, healthTexture, NULL, &healthRect);
    SDL_RenderCopy(renderer, levelTexture, NULL, &levelRect);
}
