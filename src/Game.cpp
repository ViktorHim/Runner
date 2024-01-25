#include "Game.h"


Game::Game(Vector2D resolution)
{

    // Инициализация SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

     if (TTF_Init() < 0)
    {
        std::cout << "TTF_Init() Error" << std::endl;
    }

    font = TTF_OpenFont("pixelcyr_normal.ttf", 32);
    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        std::cout << "TTF_OpenFont() Error: font is not open" << std::endl;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        // Обработка ошибки
    }

    // Создание окна
    window = SDL_CreateWindow("Runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.x, resolution.y, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

     // Создание рендерера
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout <<"SDL_CreateRenderer Error" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    state.setState(State::MENU);
    game = nullptr;
    menu = new MenuWindow(renderer, &state, font);
    select = new SelectWindow(renderer, &state, font);
}

Game::~Game()
{
    // Очистка ресурсов и завершение работы SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::start()
{

    while (!isEnd) { // главный цикл игры
        Uint32 currentTime = SDL_GetTicks();
        switch (state.getState())// Проверка состояния игры
        {
            case State::MENU: 
            {
                game = nullptr;
                menu->update();
                menu->render();
            } break;
            case State::SELECT:
            {
                select->update();
                select->render();
            } break;
            case State::GAME:
            {
                if(game == nullptr) game = new GameWindow(renderer, &state, font, select->getLevel());
                game->update(currentTime);
                game->render();
            } break;
            case State::RESTART:
            {
                game = nullptr;
                state.setState(State::GAME);
                // if(game == nullptr) game = new GameWindow(renderer, &state, font, select->getLevel());
                // game->update(currentTime);
                // game->render();
            } break;
            case State::QUIT:
            {
                isEnd = true;
            } break;
        }
    }
}