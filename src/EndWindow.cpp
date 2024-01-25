#include "EndWindow.h"

EndWindow::EndWindow(SDL_Renderer *renderer, State *state, TTF_Font *font)
{
    this->font = font;
    this->renderer = renderer;
    this->state = state;

    SDL_Rect restart = {0, 400, 200, 70};
    restart.x = WIDTH / 2 - restart.w/2;
    restartButton = new Button(renderer, restart, font, "Заново");

    SDL_Rect back = {0, 500, 200, 70};
    back.x = WIDTH / 2 - back.w / 2;
    backButton = new Button(renderer, back, font, "В меню");

    scoreRect = {0, 250, 0, 0};
    textRect = {0, 100, 0, 0};
}

void EndWindow::update(int score, bool win)
{
    this->win = win;
    std::string scoreText = "Очки: " + std::to_string(score);
    SDL_Surface *scoreSurface = TTF_RenderUTF8_Blended(font, scoreText.c_str(), {255, 255, 255, 0});
    scoreRect.h = scoreSurface ->h;
    scoreRect.w = scoreSurface ->w;
    scoreRect.x = WIDTH / 2 - scoreRect.w / 2;
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    std::string winText ;
    if(win)
    {
        winText = "Вы победили!";
    }
    else
    {
        winText = "Вы проиграли!";
    }
    SDL_Surface * textSurface = TTF_RenderUTF8_Blended(font, winText.c_str(), {255, 255, 255, 0});
    textRect.h = textSurface->h;
    textRect.w = textSurface->w;
    textRect.x = WIDTH / 2 - textRect.w / 2;
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(scoreSurface);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if (event.button.button != SDL_BUTTON_LEFT)
                    break;
                if (restartButton->isClicked())
                    state->setState(State::RESTART);
                if (backButton->isClicked())
                    state->setState(State::MENU);
                break;
            case SDL_QUIT:
                state->setState(State::QUIT);
                break;
        }
    }
}

void EndWindow::render()
{
    backButton->render();
    
    if(!win)
    {
        restartButton->render();
    }
    //SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    //SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}
