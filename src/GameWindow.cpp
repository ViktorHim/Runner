#include "GameWindow.h"
#include "ScreenSize.h"
GameWindow::GameWindow(SDL_Renderer *renderer, State *state, TTF_Font *font)
{
    this->font = font;
    this->renderer = renderer;
    this->state = state;
    camera = {0, 0, WIDTH, HEIGHT};

    tilemap = new Tilemap(renderer);
    player = new Player(renderer, Vector2D(50, 320), tilemap);

    SDL_Surface * surface = IMG_Load("sprites/BG.png");
    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect backRect = {0, 50, 200, 40};
    backRect.x = WIDTH  - backRect.w - 50;
    backButton = new Button(renderer, backRect, font, "Back");
}
void GameWindow::update(Uint32 currentTime)
{
    SDL_Delay(25);
    updateCamera();
    player->update(currentTime);
          SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        //updateKeyboardInput(&event);
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

void GameWindow::updateCamera()
{
    camera.x = ( player->getPosX() + PLAYER_SIZE * PLAYER_SCALE / 2) - WIDTH / 2;
    //camera.y = ( player->getPosY() + PLAYER_SIZE * PLAYER_SCALE / 2) - HEIGHT / 2;

    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > tilemap->getSize().x * TILE_SIZE - WIDTH) {
        camera.x = tilemap->getSize().x * TILE_SIZE - WIDTH;
    }
    // if (camera.x > tilemap->getSize().y * TILE_SIZE - HEIGHT) {
    //     camera.y = tilemap->getSize().y * TILE_SIZE - HEIGHT;
    // }
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
            case SDLK_SPACE:
                    player->jump();
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
    SDL_RenderCopy(renderer, background, NULL, NULL);
    tilemap->render(camera.x, camera.y);
    backButton->render();
    player->render(camera.x, camera.y);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}