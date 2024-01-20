#include "MenuWindow.h"
#include "ScreenSize.h"

MenuWindow::MenuWindow(SDL_Renderer * renderer, State * state, TTF_Font *font)
{
    this->font = font;
    this->renderer = renderer;
    this->state = state;

    SDL_Rect playRect = {0, 250, 300, 100};
    playRect.x = WIDTH / 2 - playRect.w / 2;
    playButton = new Button(renderer, playRect, font, "Play");

    SDL_Rect quitRect = {0, 400, 300, 100};
    quitRect.x = WIDTH / 2 - quitRect.w / 2;
    quitButton = new Button(renderer, quitRect, font, "Quit");
}


MenuWindow::~MenuWindow()
{

}

void MenuWindow::update()
{
        SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if (event.button.button != SDL_BUTTON_LEFT)
                    break;
                if (playButton->isClicked())
                    state->setState(State::GAME);
                if (quitButton->isClicked())
                    state->setState(State::QUIT);
                break;
            case SDL_QUIT:
                state->setState(State::QUIT);
                break;
        }
    }
}

void MenuWindow::render()
{
    SDL_RenderClear(renderer);

    playButton->render();
    quitButton->render();

    SDL_RenderPresent(renderer);
}