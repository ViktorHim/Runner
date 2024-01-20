#include "GameWindow.h"
#include "ScreenSize.h"
GameWindow::GameWindow(SDL_Renderer *renderer, State *state, TTF_Font *font)
{
    this->font = font;
    this->renderer = renderer;
    this->state = state;

    player = new Player(renderer, Vector2D(50, 50));

    SDL_Rect backRect = {0, 50, 200, 40};
    backRect.x = WIDTH  - backRect.w - 50;
    backButton = new Button(renderer, backRect, font, "Back");
}
void GameWindow::update(Uint32 currentTime)
{
    player->update(currentTime);
          SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        updateKeyboardInput(&event);
        switch (event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if (event.button.button != SDL_BUTTON_LEFT)
                    break;
                if (backButton->isClicked())
                    state->setState(State::MENU);
                break;
            case SDL_QUIT:
                state->setState(State::QUIT);
                break;
        }
    }
}

void GameWindow::updateKeyboardInput(SDL_Event * event)
{
    if (event->type == SDL_KEYDOWN) 
    {
        switch (event->key.keysym.sym)
        {
            case SDLK_LEFT:
                    player->moveX(-10);
                    player->setAnimation(Player::AnimationsState::WALK);
                    player->flip(-1);
                break;
            case SDLK_RIGHT:
                    player->moveX(10);
                    player->setAnimation(Player::AnimationsState::WALK);
                    player->flip(1);
                break;
        }
    }
    else if(event->type == SDL_KEYUP)
    {
         player->setAnimation(Player::AnimationsState::IDLE);
    }
}

void GameWindow::render()
{
      SDL_RenderClear(renderer);

    backButton->render();
    player->render();

    SDL_RenderPresent(renderer);
}

