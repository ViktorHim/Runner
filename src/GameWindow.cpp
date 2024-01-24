#include "GameWindow.h"
#include "ScreenSize.h"
GameWindow::GameWindow(SDL_Renderer *renderer, State *state, TTF_Font *font, int level)
{
    this->font = font;
    this->renderer = renderer;
    this->state = state;

    camera = {0, 0, WIDTH, HEIGHT};

    switch (level)
    {
        case 1:tilemap = new Tilemap(renderer);
        break;
        case 2:tilemap = new Tilemap(renderer,"levels/Level2.txt");
        break;
        case 3:tilemap = new Tilemap(renderer,"levels/Level3.txt");
        break;
    }
    
    player = new Player(renderer, Vector2D(50, 320), tilemap);
    enemyComponent = new EnemyComponent(renderer, player);
    panel = new UIPanel(renderer, font, 1);

    SDL_Surface * surface = IMG_Load("sprites/BG.png");
    background = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("sprites/finish.png");
    finishLine = SDL_CreateTextureFromSurface(renderer, surface);
    finishX = tilemap->getSize().x * TILE_SIZE - 300;
    finishRect = {finishX, 0, surface->w, surface->h};
    SDL_FreeSurface(surface);

    SDL_Rect backRect = {0, 50, 200, 40};
    backRect.x = WIDTH  - backRect.w - 50;
    backButton = new Button(renderer, backRect, font, "Back");
}

void GameWindow::update(Uint32 currentTime)
{
    if(!player->healthComponent->isAlive()) state->setState(State::MENU);
    if(player->getPosX() > finishX) state->setState(State::MENU);

    SDL_Delay(25);
    updateCamera();

    player->update(currentTime);
    enemyComponent->update();
    panel->update(enemyComponent->getscore(),
    player->healthComponent->getHealth());

    SDL_Event event;
    while (SDL_PollEvent(&event)) // обработка событий
    {
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

    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > tilemap->getSize().x * TILE_SIZE - WIDTH) {
        camera.x = tilemap->getSize().x * TILE_SIZE - WIDTH;
    }
}

void GameWindow::render()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, NULL, NULL);

    SDL_Rect finishCamera = {finishRect.x - camera.x, finishRect.y - camera.y, finishRect.w, finishRect.h};
    SDL_RenderCopy(renderer, finishLine, NULL, &finishCamera);

    panel->render();
    tilemap->render(camera.x, camera.y);
    backButton->render();
    player->render(camera.x, camera.y);
    enemyComponent->render(camera.x, camera.y);

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}