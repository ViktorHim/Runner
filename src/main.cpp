#include "SDL2/SDL.h"

int main() {
    // Инициализация SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    // Создание окна
    SDL_Window* window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Ожидание несколько секунд (в данном случае, 5 секунд)
    SDL_Delay(5000);

    // Освобождение ресурсов и завершение программы
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}