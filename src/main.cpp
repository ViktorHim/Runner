#include "Game.h"
#include "ScreenSize.h"
#include <cstdlib>
#include <ctime>

int WinMain() {
    std::srand(std::time(nullptr));
    setlocale(LC_ALL, "Russian");
    Vector2D resolution = Vector2D(WIDTH, HEIGHT);
    Game game = Game(resolution);
    game.start();
    int a = 5;

    return 0;
}
