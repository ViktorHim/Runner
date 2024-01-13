#include "Game.h"


Game::Game(Vector2D resolution)
{
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // Создание окна
    window = SDL_CreateWindow("Runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.x, resolution.y, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

     // Создание рендерера
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

Game::~Game()
{
    // Очистка ресурсов и завершение работы SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::update() {
    
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 239, 125, 20, 0);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // Добавьте здесь свой код для рендеринга объектов и других действий
    SDL_Rect rect = {0, 0, 100, 100};
    // Отображение на экране
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void Game::start()
{
    SDL_Event event;
    while (!isEnd) {
        // Обработка событий
        // while (SDL_PollEvent(&event)) {
        //     if (event.type == SDL_QUIT) {
        //         isEnd = true;
        //     }
        // }
        update();
        render();
    }
}