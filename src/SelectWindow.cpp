#include "SelectWindow.h"

SelectWindow::SelectWindow(SDL_Renderer *renderer, State *state, TTF_Font *font)
{
    this->font = font;
    this->renderer = renderer;
    this->state = state;
    level =0;

    SDL_Rect first = {0, 250, 200, 70};
    first.x = WIDTH / 2 - first.w * 2;
    levelButtons[0] = new Button(renderer, first, font, "Level 1");

    SDL_Rect second = {0, 250, 200, 70};
    second.x = WIDTH / 2 - second.w / 2;
    levelButtons[1] = new Button(renderer, second, font, "Level 2");

    SDL_Rect third = {0, 250, 200, 70};
    third.x = WIDTH / 2 + third.w;
    levelButtons[2] = new Button(renderer, third, font, "Level 3");
}

void SelectWindow::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if (event.button.button != SDL_BUTTON_LEFT)
                    break;
                if (levelButtons[0]->isClicked())
                {
                    level = 1;
                    state->setState(State::GAME);
                }
                if (levelButtons[1]->isClicked())
                {
                    state->setState(State::GAME);
                    level = 2;
                }
                if (levelButtons[2]->isClicked())
                {
                    state->setState(State::GAME);
                    level = 3;
                }
                break;
            case SDL_QUIT:
                state->setState(State::QUIT);
                break;
        }
    }
}

void SelectWindow::render()
{
    SDL_RenderClear(renderer);

    levelButtons[0]->render();
    levelButtons[1]->render();
    levelButtons[2]->render();

    SDL_RenderPresent(renderer);
}

int SelectWindow::getLevel()
{
    return level;
}
