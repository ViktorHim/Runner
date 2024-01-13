#include "Game.h"


Game::Game(Vector2D resolution)
{
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // Создание окна
    window = SDL_CreateWindow("Runner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution.x, resolution.y, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

     // Создание рендерера
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
     SDL_RenderClear(renderer);

    // Добавьте здесь свой код для рендеринга объектов и других действий

    // Отображение на экране
    SDL_RenderPresent(renderer);
}

void Game::start()
{
    SDL_Event event;

    while (!isEnd) {
        // Обработка событий
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isEnd = true;
            }
        }

        // Обновление и отрисовка

        // Ваш код обновления и отрисовки будет здесь
    }
}